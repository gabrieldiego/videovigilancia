import subprocess

class VideoSink(object) :

    def __init__( self, w, h, filename="output.h265", fps=10) :
            self.size = w*h
            self.w = w
            self.h = h
#x265 --qp 27 --input-res 832x480 --fps 30 --frame-skip 0 --frames 30 --input /media/removable/Gabriel1TB/Sequences/832x480_f500_BasketballDrill.yuv -p ultrafast --bframes 0 --output test.h265
            cmdstring = ('x265','--qp','27','--input-res','%ix%i'%(w,h),'--fps','%i'%fps,'--frame-skip','0','--frames','30','--input','/dev/stdin','-p','ultrafast','--bframes','0','--output',filename)
            self.p = subprocess.Popen(cmdstring, stdin=subprocess.PIPE, shell=False)

    def run(self, image) :
#            assert image.shape == self.size
#            self.p.stdin.write(image.tostring())
             self.p.stdin.write(image)
    def close(self) :
            self.p.stdin.close()


w = 720
h = 480

import random

line = [random.randint(0,255) for r in xrange(w)]

img = []

for i in range(h):
     img.append(line)

imgstr = bytearray(sum(img,[]))

v = VideoSink(w,h)

for i in range(45):
    v.run(imgstr)
