{
  "targets": [
    {
      "target_name": "node_libtiepie",
      "sources": [
        "src/libtiepie.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "libraries": ["-ltiepie"]
    }
  ]
}
