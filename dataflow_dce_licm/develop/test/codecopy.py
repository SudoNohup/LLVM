# -*- coding:utf-8 -*-
import os
filenames = os.listdir(os.curdir)				# 获得当前目录中的内容
print (filenames)
for filename in filenames:
        if filename != "codecopy.py" and os.path.isfile(filename):
                f = open("test.txt","a")
                fr = open(filename,"r")
                f.write("\n\n\n")
                #f.write('\\\\')
                #f.write(filename)
                f.write("\n")
                f.write(fr.read())
