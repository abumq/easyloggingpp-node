{
  "targets": [
    {
      "target_name": "easyloggingpp",
      "sources": [
        "src/binding.cc"
        "include/easylogging++.cc"
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
        "include"
      ],
    },
  ],
}
