package(default_visibility=['//visibility:public'])

cc_library(
    name='opengl',
    hdrs=glob([
        'include/GL/*.h',
        'include/EGL/*.h']),
    srcs=glob([
        'lib/x86_64-linux-gnu/libGL.so',
        'lib/x86_64-linux-gnu/libEGL.so']),
    strip_include_prefix='include',
)
