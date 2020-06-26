name="opengl_renderer"
workspace(name=name)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

http_archive(
    name="glm",
    url="https://github.com/g-truc/glm/archive/0.9.9.8.tar.gz",
    sha256="7d508ab72cb5d43227a3711420f06ff99b0a0cb63ee2f93631b162bfe1fe9592",
    build_file="@//:glm.BUILD",
    strip_prefix="glm-0.9.9.8")

new_git_repository(
    name="stb",
    remote="git@github.com:nothings/stb.git",
    commit="f54acd4e13430c5122cab4ca657705c84aa61b08",
    shallow_since = "1580905940 -0800",
    build_file="@//:stb.BUILD")

new_local_repository(
    name="opengl",
    path="/usr/",
    build_file="@//:opengl.BUILD")
