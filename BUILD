package(default_visibility=['//visibility:public'])

cc_binary(
    name="example",
    includes=[
        "include/"],
    srcs=glob([
        "include/*.h",
        "include/*.hpp",
        "src/*.cpp"]),
    data=glob([
        "resources/**"]),
    deps=[
        "@glm//:glm",
        "@opengl//:opengl",
        "@stb//:stb"]
)
