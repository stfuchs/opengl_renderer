name="opengl_renderer"
workspace(name=name)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name="glm",
    url="https://github.com/g-truc/glm/archive/0.9.9.8.tar.gz",
    sha256="7d508ab72cb5d43227a3711420f06ff99b0a0cb63ee2f93631b162bfe1fe9592",
    build_file="@//:glm.BUILD",
    strip_prefix="glm-0.9.9.8")


new_local_repository(
    name="opengl",
    path="/usr/",
    build_file="opengl.BUILD")


new_local_repository(
    name="opencv",
    path="/usr/",
    build_file="opencv.BUILD")
