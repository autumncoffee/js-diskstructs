#include "heap.hpp"
#include "utils.hpp"

#include <ac-library/containers/persistent/binary_heap/binary_heap.hpp>
#include <cstdint>

namespace NACJSDiskStructs {
    using namespace NAC;

    Napi::Value HeapOpen(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentBinaryHeap(info[0].As<Napi::String>()));
    }

    Napi::Value HeapNew(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentBinaryHeap(info[0].As<Napi::String>(), info[1].As<Napi::Number>().Int64Value()));
    }

    Napi::Value HeapDelete(const Napi::CallbackInfo& info) {
        delete (TPersistentBinaryHeap*)AsPtr(info[0]);

        return info.Env().Undefined();
    }

    Napi::Value HeapInsert(const Napi::CallbackInfo& info) {
        auto value = info[1].As<Napi::Buffer<uint8_t>>();

        ((TPersistentBinaryHeap*)AsPtr(info[0]))->Insert((const char*)value.Data());

        return info.Env().Undefined();
    }

    Napi::Value HeapClose(const Napi::CallbackInfo& info) {
        ((TPersistentBinaryHeap*)AsPtr(info[0]))->Close();

        return info.Env().Undefined();
    }

    Napi::Value HeapRecordSize(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), ((TPersistentBinaryHeap*)AsPtr(info[0]))->RecordSize());
    }

    Napi::Value HeapGetAll(const Napi::CallbackInfo& info) {
        auto prefix = info[1].As<Napi::Buffer<uint8_t>>();

        return Napi::Number::New(info.Env(), (uintptr_t)new TPersistentBinaryHeap::TIterator(((TPersistentBinaryHeap*)AsPtr(info[0]))->GetAll(TBlob(prefix.Length(), (const char*)prefix.Data()))));
    }

    Napi::Value HeapIteratorDelete(const Napi::CallbackInfo& info) {
        delete (TPersistentBinaryHeap::TIterator*)AsPtr(info[0]);

        return info.Env().Undefined();
    }

    Napi::Value HeapIteratorNext(const Napi::CallbackInfo& info) {
        TBlob data;

        if (((TPersistentBinaryHeap::TIterator*)AsPtr(info[0]))->Next(data)) {
            return Napi::Buffer<uint8_t>::Copy(info.Env(), (uint8_t*)data.Data(), data.Size());
        }

        return info.Env().Undefined();
    }
}
