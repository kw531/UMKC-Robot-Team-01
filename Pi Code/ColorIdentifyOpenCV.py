# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import RPi.GPIO as GPIO
import time
import cv2
import numpy as np

GPIO.setmode(GPIO.BOARD)
GPIO.setup(18, GPIO.IN) # Go Button
GPIO.setup(12, GPIO.OUT) # Main Servo

p = GPIO.PWM(12, 50) # Main Servo Setup
p.start(0)

def colorFound(code):
# Takes in a "binary" code and returns a color code
    print(code)
    print("")
    return{
        '100000':'r',
        '010000':'b',
        '001000':'g',
        '000100':'m',
        '000010':'y',
        '000001':'c'
        }.get(code, 'none')

def moveServo(color):
# Takes in a color code, this is were servo motion will come into play
    if color == 'r':
        print('red!!')
    elif color == 'b':
        print('blue!!')
    elif color == 'g':
        print('green!!')
    elif color == 'm':
        print('magenta!!')
    elif color == 'y':
        print('yellow!!')
    elif color == 'c':
        print('cyan!!')
    else:
        print('none!!')

    time.sleep(3)
    return 1

def binColors(R,B,G,M,Y,C):
# creates a "binary" code for the colors
# Takes in a color code that has been assigned True or False
# If true then that color gets assigned a 1
# If false that color is assigned a 0
    print("Bin Colors RGBMYC")
    print(R)
    print(B)
    print(G)
    print(M)
    print(Y)
    print(C)
    print("")
    d1=(1 if R==True else 0)
    d2=(1 if B==True else 0)
    d3=(1 if G==True else 0)
    d4=(1 if M==True else 0)
    d5=(1 if Y==True else 0)
    d6=(1 if C==True else 0)

    print("d values")
    print('r', d1)
    print('b',d2)
    print('g',d3)
    print('m',d4)
    print('y',d5)
    print('c',d6)
    print("")

    return(str(d1)+str(d2)+str(d3)+str(d4)+str(d5)+str(d6)) 

def colorCount(erode):
# returns T or F if that color is present in the camera capture
    cnt=sum(i>0 for i in erode)
    return(cnt.any()>0)

def erodeHSV(hsv, low, up):
# This creates a mask and then erodes the camera capture down to a specific color
# 8 iterations on the erode remove excess noise
    mask = cv2.inRange(hsv, np.array(low), np.array(up))
    kernel = np.ones((5,5), np.uint8)
    return(cv2.erode(mask, kernel, iterations=8))

def findColors(hsv):
# The upper and lower HSV values for each color
# Sends the camera capture off to be eroded

    magenta_lower=[150,50,5] #Good!
    magenta_upper=[177,255,255]

    red_lower=[0,50,50] #Good!
    red_upper=[12,255,255]

    green_lower=[50,50,50] #Good!
    green_upper=[76,255,180]

    yellow_lower=[26,50,50] #Good!
    yellow_upper=[49,255,255]

    cyan_lower=[77,50,50] #Good!
    cyan_upper=[105,255,255]

    blue_lower=[110,0,0] #Good!
    blue_upper=[130,255,255]

    # Gets a matrix of only that specific color
    r=colorCount(erodeHSV(hsv,red_lower,red_upper))
    b=colorCount(erodeHSV(hsv,blue_lower,blue_upper))
    g=colorCount(erodeHSV(hsv,green_lower,green_upper))
    m=colorCount(erodeHSV(hsv,magenta_lower,magenta_upper))
    y=colorCount(erodeHSV(hsv,yellow_lower,yellow_upper))
    c=colorCount(erodeHSV(hsv,cyan_lower,cyan_upper))

    print("")
    print("sending Values")
    print(r)
    print(b)
    print(g)
    print(m)
    print(y)
    print(c)
    print("")
    
   # This takes the color matrices, turns the into a binary string
   # then tells the moveServo which color to turn to
    moveServo(colorFound(binColors(r,b,g,m,y,c)))
    
#----------------------------------------MAIN-----------------------------------------------------    
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 50
camera.hflip = True

rawCapture = PiRGBArray(camera, size=(640, 480))
 
# allow the camera to warmup
time.sleep(0.1)

try: 
    # capture frames from the camera
    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
            # grab the raw NumPy array representing the image, then initialize the timestamp
            # and occupied/unoccupied text
        image = frame.array
        blur = cv2.blur(image, (3,3))
        hsv = cv2.cvtColor(blur,cv2.COLOR_BGR2HSV)
        if(GPIO.input(18)==GPIO.HIGH):
            findColors(hsv) # Takes the camera capture and moves the servo
        else:
            print "nope"
        rawCapture.truncate(0)
    
    cv2.destroyAllWindows()

except KeyboardInterrupt:
    p.stop()
    GPIO.cleanup()


    
