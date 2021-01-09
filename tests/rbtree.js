const {RBTree} = require('../');
const {assert} = require('./utils');

function testRBTreeImpl(TestDir, nonExistentKey, data, moreData) {
  const path = TestDir.file();

  function checkRBTreeContents(rbt, obj) {
    let ok = false;
    const prefixes = {};

    for (let [key, value] of obj) {
      assert(Buffer.from(value).equals(rbt.get(key)), `Value of ${key} must be the same`);

      if (key.length < 2) {
        continue;
      }

      ok = true;

      const prefix = key.split('').slice(0, key.length / 2).join('');

      if (!(prefix in prefixes)) {
        prefixes[prefix] = {};
      }

      prefixes[prefix][key] = value;
    }

    assert(ok, 'Must have keys to check prefix search');
    assert(rbt.get(nonExistentKey) === undefined, 'Non-existent key must not be present');

    for (let prefix in prefixes) {
      const items = prefixes[prefix];

      for (let [key, value] of rbt.getAll(prefix)) {
        key = key.toString();

        assert(value.toString() === items[key], `Value of ${key} must be the same`);

        delete items[key];
      }

      assert(Object.keys(items).length == 0, 'No keys are lost, no extra keys');
    }
  }

  function createRBTree() {
    const rbt = new RBTree(path, {create: true});

    for (let [key, value] of data) {
      rbt.insert(key, value);
    }

    checkRBTreeContents(rbt, data);

    rbt.delete();
  }

  function updateRBTree() {
    const rbt = new RBTree(path, {rw: true});

    checkRBTreeContents(rbt, data);

    for (let [key, value] of moreData) {
      rbt.insert(key, value);
    }

    checkRBTreeContents(rbt, moreData);
    checkRBTreeContents(rbt, data);

    rbt.delete();
  }

  function readRBTree() {
    const rbt = new RBTree(path);

    checkRBTreeContents(rbt, data);
    checkRBTreeContents(rbt, moreData);

    const all = {};

    for (let [key, value] of rbt.getAll('')) {
      all[key.toString()] = value.toString();
    }

    for (let obj of [data, moreData]) {
      for (let [key, value] of obj) {
        assert(all[key] === value, `Value of ${key} must be the same`);

        delete all[key];
      }
    }

    assert(Object.keys(all).length == 0, 'No keys are lost, no extra keys');
  }

  createRBTree();
  updateRBTree();
  readRBTree();
}

function testRBTree(TestDir) {
  testRBTreeImpl(
    TestDir,
    "qwer",
    [
      ["abcdasd", "value"],
      ["adbc", "other value"],
      ["zz\0zz", "third value"],
      ["\8\2\6\2", "\7\7\8\2\6\2"],
      ["abd--c", " "],
      ["cad", `Lorem ipsum dolor sit amet, consectetur adipiscing
elit, sed do eiusmod tempor incididunt ut labore et
dolore magna aliqua. Ut enim ad minim veniam, quis`],
    ],
    [
      ["\0\0\1\21233", `nostrud exercitation ullamco laboris nisi ut aliquip
ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore`],
      ["\1\6\7\8\2\5\222", "test"],
      ["\0\0\2\1\8\32", "hello!"],
    ],
  );
}

module.exports = {testRBTree};
