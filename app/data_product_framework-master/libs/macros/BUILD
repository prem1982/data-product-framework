# macros library

filegroup(
  name = "macros_headers",
  srcs = ["include/macros.hpp"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "macros",
  srcs = [":macros_headers"],
  linkstatic = 1,
  visibility = ["//visibility:public"],
)

