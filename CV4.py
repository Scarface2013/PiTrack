import serial
import sys
import cv2
from cv2 import *
import time
import numpy as np
import io
import math

# This is a list of BGR tuples of uppper-lower bounds for colors
low = [50,50,50]
up = [255,255,255]


sys.path.append('/usr/local/lib/python2.7/site-packages')

camera = VideoCapture(0)

#time.sleep(.1)

port = serial.Serial("/dev/ttyACM0", 9600)

camera.open(0)
def repeat():
	for x in range(0,6):
		ret, image = camera.read()

	# All facial recognition code goes here

	lower = np.array(low, dtype="uint8")
	upper = np.array(up, dtype="uint8")
	
	lCnt = 0;
	mCnt = 0;
	rCnt = 0;
	
	turnTo = 0

	mask = cv2.inRange(image, lower, upper)

	# Iterates over masked array to find IR
	y,x = np.nonzero(mask)
	turnTo = (math.ceil((np.sum(x)/x.shape)/(mask.shape[1]/3)) + 1) if x.size > 20 else 0

	# All serial communication code goes here
	port.write("q")
	if(turnTo == 0):
		print("No IR detected")
	elif(turnTo == 1):
		port.write("001")
		print("001")
	elif(turnTo == 2):
		port.write("002")
		print("002")
	elif(turnTo == 3):
		port.write("003")
		print("003")
while True:
	repeat()
