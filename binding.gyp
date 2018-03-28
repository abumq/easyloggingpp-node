{
  "targets": [
    {
      "target_name": "easyloggingpp",
      "sources": [
        "src/binding.cc",
        "deps/easylogging++.cc"
      ],
      "defines": [
        "ELPP_FEATURE_CRASH_LOG",
        "ELPP_DEFAULT_LOG_FILE=\"/dev/null\""
      ],
      "xcode_settings": {
        "OTHER_CFLAGS": [
          "-fexceptions",
          "-std=c++11",
          "-stdlib=libc++"
        ],
      },
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/"
      ],
    },
  ],
}
