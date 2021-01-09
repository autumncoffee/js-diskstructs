const {HashMap} = require('../');
const {assert} = require('./utils');

function testHashMapImpl(TestDir, nonExistentKey, data, moreData, keyType) {
  const path = TestDir.file();
  const bucketCount = data.length * 2 + moreData.length * 2;

  function checkHashMapContents(hm, obj) {
    for (let [key, value] of obj) {
      assert(Buffer.from(value).equals(hm.get(key)), `Value of ${key} must be the same`);
    }

    assert(hm.get(nonExistentKey) === undefined, 'Non-existent key must not be present');
  }

  function checkHashMapBucketCount(hm) {
    assert(hm.bucketCount() == bucketCount, 'Bucket count must be the same');
  }

  function createHashMap() {
    const hm = new HashMap(path, {keyType, bucketCount});

    checkHashMapBucketCount(hm);

    for (let [key, value] of data) {
      hm.set(key, value);
    }

    checkHashMapContents(hm, data);

    hm.close();

    checkHashMapContents(hm, data);

    hm.delete();
  }

  function updateHashMap() {
    const hm = new HashMap(path, {keyType, rw: true});

    checkHashMapBucketCount(hm);
    checkHashMapContents(hm, data);

    for (let [key, value] of moreData) {
      hm.set(key, value);
    }

    checkHashMapContents(hm, moreData);

    hm.close();

    checkHashMapContents(hm, data);
    checkHashMapContents(hm, moreData);

    hm.delete();
  }

  function readHashMap() {
    const hm = new HashMap(path, {keyType});

    checkHashMapBucketCount(hm);
    checkHashMapContents(hm, data);
    checkHashMapContents(hm, moreData);

    const all = {};

    for (let [key, value] of hm.items()) {
      if (keyType === Buffer) {
        key = key.toString();
      }

      all[key] = value.toString();
    }

    for (let obj of [data, moreData]) {
      for (let [key, value] of obj) {
        assert(all[key] === value, `Value of ${key} must be the same`);

        delete all[key];
      }
    }

    assert(Object.keys(all).length == 0, 'No keys are lost, no extra keys');
  }

  createHashMap();
  updateHashMap();
  readHashMap();
}

function testHashMap(TestDir) {
  testHashMapImpl(
    TestDir,
    1337,
    [
      [1, "value"],
      [2, "\0\1\2\3\0\4\5\6"],
      [3, "third value"],
    ],
    [
      [4, `Lorem ipsum dolor sit amet, consectetur adipiscing
elit, sed do eiusmod tempor incididunt ut labore et
dolore magna aliqua. Ut enim ad minim veniam, quis`],
      [5, `nostrud exercitation ullamco laboris nisi ut aliquip
ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore`],
    ],
  );

  testHashMapImpl(
    TestDir,
    "non-existent key",
    [
      ["first key", "value"],
      ["second key", "other value"],
      [`Lorem ipsum dolor sit amet, consectetur adipiscing
elit, sed do eiusmod tempor incididunt ut labore et
dolore magna aliqua. Ut enim ad minim veniam, quis`, "third value"],
    ],
    [
      ["\0\0\0\0\0\1\2\4", "\6\1\6\7\245\0\46"],
      ["key", `nostrud exercitation ullamco laboris nisi ut aliquip
ex ea commodo consequat. Duis aute irure dolor in
reprehenderit in voluptate velit esse cillum dolore`],
    ],
    Buffer,
  );
}

module.exports = {testHashMap};
