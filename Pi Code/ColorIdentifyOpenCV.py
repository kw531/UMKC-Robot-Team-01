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

    magenta_lower=[150,50,5] #good
    magenta_upper=[177,255,255]

    red_lower=[0,50,50] #good
    red_upper=[12,255,255]

    green_lower=[50,100,50] #ok
    green_upper=[76,255,180]

    yellow_lower=[26,50,50] #good
    yellow_upper=[49,255,255]

    cyan_lower=[77,207,202] #ok
    cyan_upper=[99,255,255]

    blue_lower=[110,0,0] #ok
    blue_upper=[130,255,255]

    lower = np.array(red_lower)
    upper = np.array(red_upper)

    # Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower, upper)
    kernel = np.ones((5,5), np.uint8)
    erode= cv2.erode(mask, kernel, iterations=2)

    #-----HERE IS WHERE I WANT SOME LOGIC DAMMIT------
        

# Bitwise-AND mask and original image
#    res = cv2.bitwise_and(frame,frame, mask= mask)

#    cv2.imshow("frame",frame)
    cv2.imshow("erode",erode)
#    cv2.imshow('res',res)
    rawCapture.truncate(0)
 
    k = cv2.waitKey(1) & 0xFF
    if k == ord("q"):
        break
    
cv2.destroyAllWindows()
    
