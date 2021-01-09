const LIB = require('bindings')('ac_diskstructs');

function HashMapIterator(ptr, keyType) {
    const self = this;
    const impl = ((keyType === Number) ? 'HashMapIteratorNextInt' : 'HashMapIteratorNext');

    self.delete = function() {
        LIB.HashMapIteratorDelete(ptr);

        self.delete = function() {};
    };

    self[Symbol.iterator] = function*() {
        for (let item; (item = LIB[impl](ptr)) !== undefined;) {
            yield item;
        }

        self.delete();
    };
}

function openImpl(path, rw, bucketCount) {
    if (bucketCount) {
        return LIB.HashMapNew(path, bucketCount);
    }

    if (rw) {
        return LIB.HashMapOpenRW(path);
    }

    return LIB.HashMapOpen(path);
}

module.exports = function(path, {keyType, rw, bucketCount} = {}) {
    if (keyType === undefined) {
        keyType = Number;

    } else if (keyType !== Buffer) {
        throw new Error('Supported key types are: Number (default), Buffer');
    }

    const self = this;
    const ptr = openImpl(path, rw, bucketCount);

    // Free memory
    self.delete = function() {
        LIB.HashMapDelete(ptr);

        self.delete = function() {};
    };

    // Finish write operations
    self.close = function() {
        LIB.HashMapClose(ptr);

        self.close = function() {};
    };

    self.get = function(key) {
        if ((typeof key).toLowerCase() == 'number') {
            return LIB.HashMapGetInt(ptr, key);

        } else {
            return LIB.HashMapGet(ptr, (Buffer.isBuffer(key) ? key : Buffer.from(key)));
        }
    };

    self.set = function(key, value) {
        value = (Buffer.isBuffer(value) ? value : Buffer.from(value));

        if ((typeof key).toLowerCase() == 'number') {
            return LIB.HashMapInsertInt(ptr, key, value);

        } else {
            return LIB.HashMapInsert(ptr, (Buffer.isBuffer(key) ? key : Buffer.from(key)), value);
        }
    };

    self.bucketCount = function() {
        return LIB.HashMapBucketCount(ptr);
    };

    self.items = function() {
        return new HashMapIterator(LIB.HashMapGetAll(ptr), keyType);
    };
};
