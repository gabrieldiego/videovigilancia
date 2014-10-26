gst-launch autovideosrc name="videosrc" ! tee name=muxtee ! queue2 ! theoraenc ! oggmux ! filesink location=test0.ogg muxtee. ! queue ! autovideosink
