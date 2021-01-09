const {Heap} = require('../');
const {assert} = require('./utils');

function testHeapImpl(TestDir, nonExistentRecord, data) {
  const recordSize = data[0].length;

  for (let i of data) {
    assert(i.length == recordSize, 'All records must be of the same size');
  }

  const path = TestDir.file();

  function checkHeapRecordSize(heap) {
    assert(heap.recordSize() == recordSize, 'Record size must be the same');
  }

  function checkHeapContents(heap) {
    let ok = false;
    const prefixes = {};

    for (let i of data) {
      assert(Buffer.from(i).equals(heap.get(i)), 'Record must be the same');

      if (i.length < 2) {
        continue;
      }

      ok = true;

      for (let prefix of ['', i.split('').slice(0, i.length / 2).join('')]) {
        if (!(prefix in prefixes)) {
          prefixes[prefix] = {};
        }

        if (!(i in prefixes[prefix])) {
          prefixes[prefix][i] = 0;
        }

        prefixes[prefix][i] += 1;
      }
    }

    assert(ok, 'Must have records to check prefix search');
    assert(heap.get(nonExistentRecord) === undefined, 'Non-existent record must not be present');

    for (let prefix in prefixes) {
      const items = prefixes[prefix];

      for (let i of heap.getAll(prefix)) {
        assert(i in items, 'Record must be expected');

        items[i] -= 1;

        if (items[i] < 1) {
          delete items[i];
        }
      }

      assert(Object.keys(items).length == 0, 'No records are lost, no extra records');
    }
  }

  function createHeap() {
    const heap = new Heap(path, {recordSize});

    checkHeapRecordSize(heap);

    for (let i of data) {
      heap.insert(i);
    }

    heap.close();

    checkHeapContents(heap);

    heap.delete();
  }

  function readHeap() {
    const heap = new Heap(path);

    checkHeapRecordSize(heap);
    checkHeapContents(heap);
  }

  createHeap();
  readHeap();
}

function testHeap(TestDir) {
  testHeapImpl(
    TestDir,
    "qwer",
    [
      "abcd",
      "adbc",
      "zzzz",
      "\8\2\6\2",
      "abdc",
      "acdb",
    ],
  );

  testHeapImpl(
    TestDir,
    "\0\2\3",
    [
      "\0\0\1\2",
      "\1\6\7\8",
      "cccc",
      "\0\0\2\1",
    ],
  );
}

module.exports = {testHeap};
