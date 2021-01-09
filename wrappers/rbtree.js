const LIB = require('bindings')('ac_diskstructs');

function RBTreeIterator(ptr) {
    const self = this;

    self.delete = function() {
        LIB.RBTreeIteratorDelete(ptr);

        self.delete = function() {};
    };

    self[Symbol.iterator] = function*() {
        for (let item; (item = LIB.RBTreeIteratorNext(ptr)) !== undefined;) {
            yield item;
        }

        self.delete();
    };
}

function openImpl(path, rw, create) {
    if (create) {
        return LIB.RBTreeNew(path);
    }

    if (rw) {
        return LIB.RBTreeOpenRW(path);
    }

    return LIB.RBTreeOpen(path);
}

module.exports = function(path, {rw, create} = {}) {
    const self = this;
    const ptr = openImpl(path, rw, create);

    // Free memory
    self.delete = function() {
        LIB.RBTreeDelete(ptr);

        self.delete = function() {};
    };

    self.get = function(key) {
        return LIB.RBTreeGet(ptr, (Buffer.isBuffer(key) ? key : Buffer.from(key)));
    };

    self.insert = function(key, value) {
        LIB.RBTreeInsert(
            ptr,
            (Buffer.isBuffer(key) ? key : Buffer.from(key)),
            (Buffer.isBuffer(value) ? value : Buffer.from(value))
        );
    };

    self.getAll = function(prefix) {
        return new RBTreeIterator(LIB.RBTreeGetAll(ptr, (Buffer.isBuffer(prefix) ? prefix : Buffer.from(prefix))));
    };
};
