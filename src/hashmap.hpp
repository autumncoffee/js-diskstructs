#pragma once

#include <napi.h>

namespace NACJSDiskStructs {
    Napi::Value HashMapOpen(const Napi::CallbackInfo& info);
    Napi::Value HashMapOpenRW(const Napi::CallbackInfo& info);
    Napi::Value HashMapNew(const Napi::CallbackInfo& info);

    Napi::Value HashMapDelete(const Napi::CallbackInfo& info);

    Napi::Value HashMapInsert(const Napi::CallbackInfo& info);
    Napi::Value HashMapInsertInt(const Napi::CallbackInfo& info);
    Napi::Value HashMapClose(const Napi::CallbackInfo& info);

    Napi::Value HashMapBucketCount(const Napi::CallbackInfo& info);

    Napi::Value HashMapGet(const Napi::CallbackInfo& info);
    Napi::Value HashMapGetInt(const Napi::CallbackInfo& info);

    Napi::Value HashMapGetAll(const Napi::CallbackInfo& info);
    Napi::Value HashMapIteratorDelete(const Napi::CallbackInfo& info);

    Napi::Value HashMapIteratorNext(const Napi::CallbackInfo& info);
    Napi::Value HashMapIteratorNextInt(const Napi::CallbackInfo& info);
}
