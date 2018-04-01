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
        "ELPP_DEFAULT_LOG_FILE=\"nul\""
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "conditions": [
        ['OS=="mac"', {
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
          },
        }],
        ['OS=="win"', {
          "defines": [
            "ELPP_DEFAULT_LOG_FILE=\"logs\\output.log\"",
          ],
        }],
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/"
      ],
    },
  ],
}
