# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np
 
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 50
camera.hflip = True

rawCapture = PiRGBArray(camera, size=(640, 480))
 
# allow the camera to warmup
time.sleep(0.1)
 
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	# grab the raw NumPy array representing the image, then initialize the timestamp
	# and occupied/unoccupied text
    image = frame.array

    blur = cv2.blur(image, (3,3))

    #hsv to complicate things, or stick with BGR
    hsv = cv2.cvtColor(blur,cv2.COLOR_BGR2HSV)

    # define range of color in HSV
    lower = np.array([0,50,50])
    upper = np.array([12,255,255])
    
    lower_mag = np.array([140,207,202]) #Needs work
    upper_mag = np.array([167,255,255])
    lower_red = np.array([0,50,50]) # Needs Work
    upper_red = np.array([12,255,255])
    lower_green = np.array([50,100,50]) # OKish
    upper_green = np.array([76,255,180])
    lower_yellow = np.array([26,50,50]) # Good
    upper_yellow = np.array([49,255,255])
    lower_cyan = np.array([77,207,202]) # OKish
    upper_cyan = np.array([99,255,255])
    lower_blue = np.array([110,0,0]) # OKish
    Rupper_blue = np.array([130,255,255])

    # Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower, upper)

    # Bitwise-AND mask and original image
#    res = cv2.bitwise_and(frame,frame, mask= mask)

#    cv2.imshow("frame",frame)
    cv2.imshow("mask",mask)
#    cv2.imshow('res',res)
    rawCapture.truncate(0)
 
    k = cv2.waitKey(1) & 0xFF
    if k == ord("q"):
        break
    
cv2.destroyAllWindows()
    
