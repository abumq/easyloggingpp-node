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
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "conditions": [
        ['OS=="mac"', {
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
          },
        }],
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/"
      ],
    },
  ],
}
