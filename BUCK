load('//:subdir_glob.bzl', 'subdir_glob' )

cxx_library(
    name = 'store',
    header_namespace = 'store',
    exported_headers = subdir_glob([
        ('include', '**/*.hpp')
    ]),
    srcs = glob([
        'src/**/*.cpp',
    ]),
    visibility = [
        'PUBLIC',
    ],
)

cxx_binary(
    name = "example",
    deps = [
        ":store"
    ],
    linker_flags = [ "-v" ],
    srcs = glob([
        "example/**/*.cpp"
    ])
)