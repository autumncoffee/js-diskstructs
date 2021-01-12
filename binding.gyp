{
  "targets": [
    {
      "target_name": "ac_diskstructs",
      "sources": [
        "<!@(find src -type f -name '*.cpp')",
        "<!@(find `node -p \"require('path').relative('', require('ac-common').root)\"`/*.cpp -type f)",
        "<!@(find `node -p \"require('path').relative('', require('ac-common').root)\"`/utils/*.cpp -type f)",
        "<!@(find `node -p \"require('path').relative('', require('ac-library').root)\"`/containers/persistent/immutable_hashmap/*.cpp -type f)",
        "<!@(find `node -p \"require('path').relative('', require('ac-library').root)\"`/containers/persistent/binary_heap/*.cpp -type f)",
        "<!@(find `node -p \"require('path').relative('', require('ac-library').root)\"`/containers/rbtree/*.cpp -type f)",
        "contrib/absl/numeric/int128.cc",
        "<!@(node -p \"require('path').relative('', require('ac-library').root) + '/contrib/murmur/MurmurHash3.cpp'\")"
      ],
      "cflags!": [ "-fno-exceptions", "-fno-rtti" ],
      "cflags_cc!": [ "-fno-exceptions", "-fno-rtti" ],
      "cflags": [ "-std=c++17" ],
      "cflags_cc": [ "-std=c++17" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!@(node -p \"require('path').dirname(require('ac-common').root)\")",
        "<!@(node -p \"require('path').dirname(require('ac-library').root)\")",
        "contrib"
      ],
      "defines": [ "NAPI_CPP_EXCEPTIONS" ],
      "conditions": [
        ["OS==\"mac\"", {
          "cflags+": [ "-stdlib=libc++" ],
          "xcode_settings": {
            "OTHER_CPLUSPLUSFLAGS" : [ "-std=c++17", "-stdlib=libc++" ],
            "OTHER_LDFLAGS": [ "-stdlib=libc++" ],
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
            "CLANG_CXX_LANGUAGE_STANDARD":"c++17",
            "CLANG_CXX_LIBRARY": "libc++"
          }
        }]
      ]
    }
  ]
}
