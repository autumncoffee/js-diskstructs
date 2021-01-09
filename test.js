const {testHashMap} = require('./tests/hashmap');
const {testHeap} = require('./tests/heap');
const {testRBTree} = require('./tests/rbtree');

const fs = require('fs');
const os = require('os');
const path = require('path');

const TestDir = new function() {
  const root = fs.mkdtempSync(os.tmpdir() + path.sep);
  let counter = 0;

  this.file = function() {
    counter += 1;

    return path.join(root, '' + counter);
  };

  this.remove = function() {
    fs.rmdirSync(root, {recursive: true});
  };
};

function testAll() {
  testHashMap(TestDir);
  testHeap(TestDir);
  testRBTree(TestDir);
}

try {
  testAll();

} catch (e) {
  try {
    TestDir.remove();

  } catch {
  }

  throw e;
}

TestDir.remove();

console.log('OK');
