#include <napi.h>

#include "hashmap.hpp"
#include "heap.hpp"
#include "rbtree.hpp"

Napi::Object ACJSDiskStructsInit(Napi::Env env, Napi::Object exports) {
    // *** HashMap ***

    exports.Set("HashMapOpen", Napi::Function::New(env, NACJSDiskStructs::HashMapOpen));;
    exports.Set("HashMapOpenRW", Napi::Function::New(env, NACJSDiskStructs::HashMapOpenRW));;
    exports.Set("HashMapNew", Napi::Function::New(env, NACJSDiskStructs::HashMapNew));;

    exports.Set("HashMapDelete", Napi::Function::New(env, NACJSDiskStructs::HashMapDelete));;

    exports.Set("HashMapInsert", Napi::Function::New(env, NACJSDiskStructs::HashMapInsert));;
    exports.Set("HashMapInsertInt", Napi::Function::New(env, NACJSDiskStructs::HashMapInsertInt));;
    exports.Set("HashMapClose", Napi::Function::New(env, NACJSDiskStructs::HashMapClose));;

    exports.Set("HashMapBucketCount", Napi::Function::New(env, NACJSDiskStructs::HashMapBucketCount));;

    exports.Set("HashMapGet", Napi::Function::New(env, NACJSDiskStructs::HashMapGet));;
    exports.Set("HashMapGetInt", Napi::Function::New(env, NACJSDiskStructs::HashMapGetInt));;

    exports.Set("HashMapGetAll", Napi::Function::New(env, NACJSDiskStructs::HashMapGetAll));;
    exports.Set("HashMapIteratorDelete", Napi::Function::New(env, NACJSDiskStructs::HashMapIteratorDelete));;

    exports.Set("HashMapIteratorNext", Napi::Function::New(env, NACJSDiskStructs::HashMapIteratorNext));;
    exports.Set("HashMapIteratorNextInt", Napi::Function::New(env, NACJSDiskStructs::HashMapIteratorNextInt));;

    // *** Heap ***

    exports.Set("HeapOpen", Napi::Function::New(env, NACJSDiskStructs::HeapOpen));;
    exports.Set("HeapNew", Napi::Function::New(env, NACJSDiskStructs::HeapNew));;

    exports.Set("HeapDelete", Napi::Function::New(env, NACJSDiskStructs::HeapDelete));;

    exports.Set("HeapInsert", Napi::Function::New(env, NACJSDiskStructs::HeapInsert));;
    exports.Set("HeapClose", Napi::Function::New(env, NACJSDiskStructs::HeapClose));;

    exports.Set("HeapRecordSize", Napi::Function::New(env, NACJSDiskStructs::HeapRecordSize));;

    exports.Set("HeapGetAll", Napi::Function::New(env, NACJSDiskStructs::HeapGetAll));;
    exports.Set("HeapIteratorDelete", Napi::Function::New(env, NACJSDiskStructs::HeapIteratorDelete));;

    exports.Set("HeapIteratorNext", Napi::Function::New(env, NACJSDiskStructs::HeapIteratorNext));;

    // *** RBTree ***

    exports.Set("RBTreeOpen", Napi::Function::New(env, NACJSDiskStructs::RBTreeOpen));;
    exports.Set("RBTreeOpenRW", Napi::Function::New(env, NACJSDiskStructs::RBTreeOpenRW));;
    exports.Set("RBTreeNew", Napi::Function::New(env, NACJSDiskStructs::RBTreeNew));;

    exports.Set("RBTreeDelete", Napi::Function::New(env, NACJSDiskStructs::RBTreeDelete));;

    exports.Set("RBTreeInsert", Napi::Function::New(env, NACJSDiskStructs::RBTreeInsert));;

    exports.Set("RBTreeGet", Napi::Function::New(env, NACJSDiskStructs::RBTreeGet));;
    exports.Set("RBTreeGetAll", Napi::Function::New(env, NACJSDiskStructs::RBTreeGetAll));;
    exports.Set("RBTreeIteratorDelete", Napi::Function::New(env, NACJSDiskStructs::RBTreeIteratorDelete));;

    exports.Set("RBTreeIteratorNext", Napi::Function::New(env, NACJSDiskStructs::RBTreeIteratorNext));;

    return exports;
}

NODE_API_MODULE(ac_diskstructs, ACJSDiskStructsInit)
