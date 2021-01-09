#pragma once

#include <napi.h>

namespace NACJSDiskStructs {
    Napi::Value HeapOpen(const Napi::CallbackInfo& info);
    Napi::Value HeapNew(const Napi::CallbackInfo& info);

    Napi::Value HeapDelete(const Napi::CallbackInfo& info);

    Napi::Value HeapInsert(const Napi::CallbackInfo& info);
    Napi::Value HeapClose(const Napi::CallbackInfo& info);

    Napi::Value HeapRecordSize(const Napi::CallbackInfo& info);

    Napi::Value HeapGetAll(const Napi::CallbackInfo& info);
    Napi::Value HeapIteratorDelete(const Napi::CallbackInfo& info);

    Napi::Value HeapIteratorNext(const Napi::CallbackInfo& info);
}
