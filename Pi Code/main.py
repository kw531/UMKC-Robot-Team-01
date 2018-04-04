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
GPIO.setup(16, GPIO.OUT) # Bottom Servo
GPIO.setup(15, GPIO.IN) # Dispense Signal from Arduino (High = Turn on bottom servo)
GPIO.setup(13, GPIO.IN) # Mode signal (Low = Collect High = Dispense)
GPIO.setup(40, GPIO.OUT) # Output to Arduino to Go

p = GPIO.PWM(12, 50) # Main Servo Setup
p.start(0)
b = GPIO.PWM(16, 50) # Bottom Servo Setup
b.start(7.5)

dispense = 0 # For tracking what has been dispensed or not

def colorFound(code):
    print code
# Takes in a "binary" code and returns a color code
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
#used from reset point of 7.5 duty cycle
#Collection Colors
#Black - 9.55
#Yellow - 9.33 g
#Cyan - 9.23  g
#Magenta - 9.08 g
#Red - 9.75 g
#Green - 9.8 g
#Blue - 9.2 g

    if color == 'r':
        position=9.75
        print('red!!')
    elif color == 'b':
        position=9.2
        print('blue!!')
    elif color == 'g':
        position=9.80
        print('green!!')
    elif color == 'm':
        position=9.08
        print('magenta!!')
    elif color == 'y':
        position=9.33
        print('yellow!!')
    elif color == 'c':
        position=9.23
        print('cyan!!')
    else:
        position=7.55
        print('none or black!!')

    servoOp(position) #Move to color
    time.sleep(4) #wait 5 seconds
    servoOp(7.55) #return to black
    return 1

def servoOp(position):
# Moves the servo to the position
    p.ChangeDutyCycle(position)  # turn towards 90 degree

def binColors(R,B,G,M,Y,C):
# creates a "binary" code for the colors
# Takes in a color code that has been assigned True or False
# If true then that color gets assigned a 1
# If false that color is assigned a 0

    d1=(1 if R==True else 0)
    d2=(1 if B==True else 0)
    d3=(1 if G==True else 0)
    d4=(1 if M==True else 0)
    d5=(1 if Y==True else 0)
    d6=(1 if C==True else 0)

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

    blue_lower=[110,25,25] #Good!
    blue_upper=[140,255,255]

    # Gets a matrix of only that specific color
    r=colorCount(erodeHSV(hsv,red_lower,red_upper))
    b=colorCount(erodeHSV(hsv,blue_lower,blue_upper))
    g=colorCount(erodeHSV(hsv,green_lower,green_upper))
    m=colorCount(erodeHSV(hsv,magenta_lower,magenta_upper))
    y=colorCount(erodeHSV(hsv,yellow_lower,yellow_upper))
    c=colorCount(erodeHSV(hsv,cyan_lower,cyan_upper))
    
   # This takes the color matrices, turns the into a binary string
   # then tells the moveServo which color to turn to
    moveServo(colorFound(binColors(r,b,g,m,y,c)))
    

def dispenseCoin():
# Move the coins to the slot, then dispense
    print ("dispenseCoin()")
#Dispensing Colors
#Black - 10.0
#Yellow - 9.85
#Cyan - 9.70
#Magenta - 9.57
#Red - 9.10
#Green - 9.25
#Blue - 9.4

    if dispense == 0: #red
        print("red dispense")
        pos=9.67
    elif dispense == 1: #green
        print("green dispense")
        pos=9.82
    elif dispense == 2: #blue
        print("blue dispense")
        pos=10.1
    elif dispense == 3: #gray/black
        print("black dispense")
        pos=9.55
    elif dispense == 4: #cyan
        print("cyan dispense")
        pos=9.25
    elif dispense == 5: #magenta
        print("mag dispense")
        pos=9.1
    elif dispense == 6: #yellow
        print("yellow dispense")
        pos=9.4
    else:
        pos=7.55

    servoOp(pos) # Position the coins
    time.sleep(2)
    moveBottomServo() #dispense the coins
    time.sleep(2)
    print "ET GO HOME"
    servoOp(7.55)
    time.sleep(3)
    
def moveBottomServo():
    b.ChangeDutyCycle(7.5)  # Open
    time.sleep(2)
    b.ChangeDutyCycle(10.5) # Close

        
#----------------------------------------MAIN-----------------------------------------------------    
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 50
camera.hflip = True

rawCapture = PiRGBArray(camera, size=(640, 480))
 
# allow the camera to warmup
time.sleep(0.1)
GPIO.output(40, GPIO.LOW)
try:
    while True:
        for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
            if(GPIO.input(13)==GPIO.LOW): #Collect Mode
                # capture frames from the camera
                # grab the raw NumPy array representing the image
                image = frame.array
                blur = cv2.blur(image, (3,3))
                hsv = cv2.cvtColor(blur,cv2.COLOR_BGR2HSV)
                if(GPIO.input(18)==GPIO.HIGH): #Go Button is pushed
                    GPIO.output(40, GPIO.HIGH) #Tell Arduino to start moving
                    findColors(hsv) # Takes the camera capture and moves the servo
                else:
                    print "nope"
            else: #GPIO 13 is HIGH - Dispense Mode
                print("Dispense~")
                if(GPIO.input(15) == GPIO.HIGH): # We have stopped on a color
                    dispenseCoin()
                    time.sleep(1)
                    dispense=dispense+1 #go to next color
                time.sleep(.1) #hang out here for a milisecond
            rawCapture.truncate(0)

except KeyboardInterrupt:
    p.stop()
    b.stop()
    GPIO.output(40, GPIO.LOW)
    GPIO.cleanup()


    
