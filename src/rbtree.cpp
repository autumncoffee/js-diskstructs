#include "rbtree.hpp"
#include "utils.hpp"

#include <ac-library/containers/rbtree/persistent.hpp>
#include <cstdint>

namespace NACJSDiskStructs {
    using namespace NAC;

    Napi::Value RBTreeOpen(const Napi::CallbackInfo& info) {
        auto out = new TPersistentRBTree(info[0].As<Napi::String>());
        out->FindRoot();
        return Napi::Number::New(info.Env(), (uintptr_t)out);
    }

    Napi::Value RBTreeOpenRW(const Napi::CallbackInfo& info) {
        auto out = new TPersistentRBTree(info[0].As<Napi::String>(), TFile::ACCESS_RDWR);
        out->FindRoot();
        return Napi::Number::New(info.Env(), (uintptr_t)out);
    }

    Napi::Value RBTreeNew(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentRBTree(info[0].As<Napi::String>(), TFile::ACCESS_CREATE));
    }

    Napi::Value RBTreeDelete(const Napi::CallbackInfo& info) {
        delete (TPersistentRBTree*)AsPtr(info[0]);

        return info.Env().Undefined();
    }

    Napi::Value RBTreeInsert(const Napi::CallbackInfo& info) {
        auto key = info[1].As<Napi::Buffer<uint8_t>>();
        auto value = info[2].As<Napi::Buffer<uint8_t>>();

        ((TPersistentRBTree*)AsPtr(info[0]))->Insert(
            TBlob(key.Length(), (const char*)key.Data()),
            TBlob(value.Length(), (const char*)value.Data())
        );

        return info.Env().Undefined();
    }

    Napi::Value RBTreeGet(const Napi::CallbackInfo& info) {
        auto key = info[1].As<Napi::Buffer<uint8_t>>();

        if (auto value = ((TPersistentRBTree*)AsPtr(info[0]))->Get(TBlob(key.Length(), (const char*)key.Data()))) {
            return Napi::Buffer<uint8_t>::Copy(info.Env(), (uint8_t*)value.Data(), value.Size());
        }

        return info.Env().Undefined();
    }

    Napi::Value RBTreeGetAll(const Napi::CallbackInfo& info) {
        auto prefix = info[1].As<Napi::Buffer<uint8_t>>();

        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentRBTree::TIterator(((TPersistentRBTree*)AsPtr(info[0]))->GetAll(TBlob(prefix.Length(), (const char*)prefix.Data()))));
    }

    Napi::Value RBTreeIteratorDelete(const Napi::CallbackInfo& info) {
        delete (TPersistentRBTree::TIterator*)AsPtr(info[0]);

        return info.Env().Undefined();
    }

    Napi::Value RBTreeIteratorNext(const Napi::CallbackInfo& info) {
        auto env = info.Env();
        TBlob key;
        TBlob value;

        if (((TPersistentRBTree::TIterator*)AsPtr(info[0]))->Next(key, value)) {
            auto rv = Napi::Array::New(env, 2);

            rv.Set((int)0, Napi::Buffer<uint8_t>::Copy(env, (uint8_t*)key.Data(), key.Size()));
            rv.Set(1, Napi::Buffer<uint8_t>::Copy(env, (uint8_t*)value.Data(), value.Size()));

            return rv;
        }

        return env.Undefined();
    }
}
