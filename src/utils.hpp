#include <cstdint>
#include <napi.h>

namespace NACJSDiskStructs {
    template<typename T>
    uintptr_t AsPtr(const T& arg) {
        return arg.template As<Napi::Number>().Int64Value();
    }
}
