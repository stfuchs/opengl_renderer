package(default_visibility = ['//visibility:public'])

cc_library(
    name='opencv',
    srcs=glob([
                'lib/x86_64-linux-gnu/libopencv_core.so',
                'lib/x86_64-linux-gnu/libopencv_features2d.so',
                'lib/x86_64-linux-gnu/libopencv_imgproc.so',
                'lib/x86_64-linux-gnu/libopencv_imgcodecs.so',
                'lib/x86_64-linux-gnu/libopencv_video.so',
                'lib/x86_64-linux-gnu/libopencv_videoio.so',
                'lib/x86_64-linux-gnu/libopencv_highgui.so',
              ]),
    hdrs=glob([
                'include/opencv2/core/*.h',
                'include/opencv2/core/*.hpp',
                'include/opencv2/features2d/*.hpp',
                'include/opencv2/imageproc/*.h',
                'include/opencv2/imageproc/*.hpp',
                'include/opencv2/imagecodecs/*.h',
                'include/opencv2/imagecodecs.hpp',
                'include/opencv2/video/*.hpp',
                'include/highgui/highgui.hpp',
              ]),
    strip_include_prefix='include',
)
