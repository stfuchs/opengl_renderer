package(default_visibility=['//visibility:public'])

cc_binary(
    name="example",
    includes=[
        "include/"],
    srcs=glob([
        "include/*.h",
        "src/*.cpp"]),
    data=glob([
        "resources/**"]),
    deps=[
        "@glm//:glm",
        "@opencv//:opencv",
        "@opengl//:opengl"]
)
