gst-launch-0.10 oggmux name=mux ! filesink location=test0.ogg v4l2src device=/dev/video0 ! ffmpegcolorspace ! theoraenc ! queue ! mux.
