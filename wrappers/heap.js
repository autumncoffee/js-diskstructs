const LIB = require('bindings')('ac_diskstructs');

function HeapIterator(ptr) {
    const self = this;

    self.delete = function() {
        LIB.HeapIteratorDelete(ptr);

        self.delete = function() {};
    };

    self[Symbol.iterator] = function*() {
        for (let item; (item = LIB.HeapIteratorNext(ptr)) !== undefined;) {
            yield item;
        }

        self.delete();
    };
}

module.exports = function(path, {recordSize} = {}) {
    const self = this;
    const ptr = (recordSize ? LIB.HeapNew(path, recordSize) : LIB.HeapOpen(path));

    self.recordSize = function() {
        return LIB.HeapRecordSize(ptr);
    };

    // Free memory
    self.delete = function() {
        LIB.HeapDelete(ptr);

        self.delete = function() {};
    };

    // Finish write operations
    self.close = function() {
        LIB.HeapClose(ptr);

        self.close = function() {};
    };

    self.get = function(prefix) {
        const it = self.getAll(prefix);

        for (let rv of it) {
            it.delete();
            return rv;
        }

        return undefined;
    };

    self.insert = function(value) {
        LIB.HeapInsert(ptr, (Buffer.isBuffer(value) ? value : Buffer.from(value)));
    };

    self.getAll = function(prefix) {
        return new HeapIterator(LIB.HeapGetAll(ptr, (Buffer.isBuffer(prefix) ? prefix : Buffer.from(prefix))));
    };
};
