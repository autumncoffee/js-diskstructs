#pragma once

#include <napi.h>

namespace NACJSDiskStructs {
    Napi::Value RBTreeOpen(const Napi::CallbackInfo& info);
    Napi::Value RBTreeOpenRW(const Napi::CallbackInfo& info);
    Napi::Value RBTreeNew(const Napi::CallbackInfo& info);

    Napi::Value RBTreeDelete(const Napi::CallbackInfo& info);

    Napi::Value RBTreeInsert(const Napi::CallbackInfo& info);

    Napi::Value RBTreeGet(const Napi::CallbackInfo& info);
    Napi::Value RBTreeGetAll(const Napi::CallbackInfo& info);
    Napi::Value RBTreeIteratorDelete(const Napi::CallbackInfo& info);

    Napi::Value RBTreeIteratorNext(const Napi::CallbackInfo& info);
}
