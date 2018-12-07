source_dirs = [
    "src",
    "src/cpp11",
    "src/main.cpp"
]

cc_binary (
    name = "demo",
    srcs = [d+"/*.cpp" for d in source_dirs],
    deps = [
        '#glog',
    ]
)
