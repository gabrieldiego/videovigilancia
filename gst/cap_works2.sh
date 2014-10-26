gst-launch-0.10 -v -m v4l2src ! ffmpegcolorspace ! tee name=muxtee ! queue2 ! theoraenc ! oggmux ! filesink location=test0.ogg muxtee. ! queue ! xvimagesink
