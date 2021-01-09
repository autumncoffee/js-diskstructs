#include "hashmap.hpp"
#include "utils.hpp"

#include <ac-library/containers/persistent/immutable_hashmap/hashmap.hpp>
#include <cstdint>

namespace NACJSDiskStructs {
    using namespace NAC;

    Napi::Value HashMapOpen(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentImmutableHashMap(info[0].As<Napi::String>(), TPersistentImmutableHashMap::DefaultSeed));
    }

    Napi::Value HashMapOpenRW(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentImmutableHashMap(info[0].As<Napi::String>(), TPersistentImmutableHashMap::DefaultSeed, /* rw = */true));
    }

    Napi::Value HashMapNew(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentImmutableHashMap(info[0].As<Napi::String>(), info[1].As<Napi::Number>().Int64Value(), TPersistentImmutableHashMap::DefaultSeed));
    }

    Napi::Value HashMapDelete(const Napi::CallbackInfo& info) {
        delete (TPersistentImmutableHashMap*)AsPtr(info[0]);

        return info.Env().Undefined();
    }

    Napi::Value HashMapInsert(const Napi::CallbackInfo& info) {
        auto key = info[1].As<Napi::Buffer<uint8_t>>();
        auto value = info[2].As<Napi::Buffer<uint8_t>>();

        ((TPersistentImmutableHashMap*)AsPtr(info[0]))->Insert(
            TBlob(key.Length(), (const char*)key.Data()),
            TBlob(value.Length(), (const char*)value.Data())
        );

        return info.Env().Undefined();
    }

    Napi::Value HashMapInsertInt(const Napi::CallbackInfo& info) {
        auto value = info[2].As<Napi::Buffer<uint8_t>>();

        ((TPersistentImmutableHashMap*)AsPtr(info[0]))->Insert(
            (uint64_t)info[1].As<Napi::Number>().Int64Value(),
            TBlob(value.Length(), (const char*)value.Data())
        );

        return info.Env().Undefined();
    }

    Napi::Value HashMapClose(const Napi::CallbackInfo& info) {
        ((TPersistentImmutableHashMap*)AsPtr(info[0]))->Close();

        return info.Env().Undefined();
    }

    Napi::Value HashMapBucketCount(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), ((TPersistentImmutableHashMap*)AsPtr(info[0]))->BucketCount());
    }

    namespace {
        template<typename TEnv, typename TKey>
        Napi::Value HashMapGetImpl(TEnv&& env, uintptr_t ptr, TKey&& key) {
            auto data = ((TPersistentImmutableHashMap*)ptr)->Get(key);

            if (data) {
                return Napi::Buffer<uint8_t>::Copy(env, (uint8_t*)data.Data(), data.Size());
            }

            return env.Undefined();
        }
    }

    Napi::Value HashMapGet(const Napi::CallbackInfo& info) {
        auto key = info[1].As<Napi::Buffer<uint8_t>>();

        return HashMapGetImpl(info.Env(), AsPtr(info[0]), TBlob(key.Length(), (const char*)key.Data()));
    }

    Napi::Value HashMapGetInt(const Napi::CallbackInfo& info) {
        return HashMapGetImpl(info.Env(), AsPtr(info[0]), (uint64_t)info[1].As<Napi::Number>().Int64Value());
    }

    Napi::Value HashMapGetAll(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentImmutableHashMap::TIterator(((TPersistentImmutableHashMap*)AsPtr(info[0]))->GetAll()));
    }

    Napi::Value HashMapIteratorDelete(const Napi::CallbackInfo& info) {
        delete (TPersistentImmutableHashMap::TIterator*)AsPtr(info[0]);

        return info.Env().Undefined();
    }

    namespace {
        template<typename TEnv, typename TKey>
        Napi::Value HashMapIteratorNextImpl(TEnv&& env, uintptr_t ptr, TKey& key) {
            TBlob data;

            if (((TPersistentImmutableHashMap::TIterator*)ptr)->Next(key, data)) {
                return Napi::Buffer<uint8_t>::Copy(env, (uint8_t*)data.Data(), data.Size());
            }

            return env.Undefined();
        }
    }

    Napi::Value HashMapIteratorNext(const Napi::CallbackInfo& info) {
        TBlob key;
        auto env = info.Env();
        auto value = HashMapIteratorNextImpl(env, AsPtr(info[0]), key);

        if (value.IsUndefined()) {
            return value;
        }

        auto rv = Napi::Array::New(env, 2);

        rv.Set((int)0, Napi::Buffer<uint8_t>::Copy(env, (uint8_t*)key.Data(), key.Size()));
        rv.Set(1, value);

        return rv;
    }

    Napi::Value HashMapIteratorNextInt(const Napi::CallbackInfo& info) {
        uint64_t key;
        auto env = info.Env();
        auto value = HashMapIteratorNextImpl(env, AsPtr(info[0]), key);

        if (value.IsUndefined()) {
            return value;
        }

        auto rv = Napi::Array::New(env, 2);

        rv.Set((int)0, Napi::Number::New(env, key));
        rv.Set(1, value);

        return rv;
    }
}
