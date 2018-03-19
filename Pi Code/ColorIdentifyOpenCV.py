# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np

def colorFound(code):
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
    print("Bin Colors")
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
    print(d1)
    print(d2)
    print(d3)
    print(d4)
    print(d5)
    print(d6)
    print("")

    return(str(d1)+str(d2)+str(d3)+str(d4)+str(d5)+str(d6))

def colorCount(erode):
    cnt=sum(i>0 for i in erode)
    return(cnt.any()>0)

def erodeHSV(hsv, low, up):
    mask = cv2.inRange(hsv, np.array(low), np.array(up))
    kernel = np.ones((5,5), np.uint8)
    return(cv2.erode(mask, kernel, iterations=8))

def findColors(hsv):
    # define range of color in HSV

    magenta_lower=[150,50,5] #Good!
    magenta_upper=[177,255,255]

    red_lower=[0,50,50] #Good!
    red_upper=[12,255,255]

    green_lower=[50,50,50] #Good!
    green_upper=[76,255,180]

    yellow_lower=[26,50,50] #Good!
    yellow_upper=[49,255,255]

    cyan_lower=[77,0,0] #Good!
    cyan_upper=[105,255,255]

    blue_lower=[110,0,0] #Good!
    blue_upper=[130,255,255]

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
    moveServo(colorFound(binColors(r,b,g,m,y,c)))
    
    
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
    hsv = cv2.cvtColor(blur,cv2.COLOR_BGR2HSV)

    findColors(hsv)

        #cv2.imshow("erode",erode)
    rawCapture.truncate(0)
 
    k = cv2.waitKey(1) & 0xFF
    if k == ord("q"):
        break
    
cv2.destroyAllWindows()


    
