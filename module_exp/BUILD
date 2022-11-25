load("@rules_cc_module//cc_module:defs.bzl", "cc_module", "cc_module_binary")

cc_module(
    name="hello",
    src="hello.cc",
)

cc_module_binary(
    name = "exe",
    srcs = ["main.cc"],
    deps = [":hello",],
)
