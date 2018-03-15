import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)

##p.start(0)
##
##try:
##        while True:
##                print("starting")
##                p.ChangeDutyCycle(0)  # turn towards 90 degree
##                time.sleep(5) # sleep 1 second
##                p.ChangeDutyCycle(1)  # turn towards 0 degree
##                time.sleep(.1) # sleep 1 second
##                #p.ChangeDutyCycle(12.5) # turn towards 180 degree
##                #time.sleep(1) # sleep 1 second 
##except KeyboardInterrupt:
 ##        p.stop()
##        GPIO.cleanup()

p.start(0)

def change(k):
    p.ChangeDutyCycle(.5)
    time.sleep(k)
    p.ChangeDutyCycle(0)

try:
    while True:
        k = float(raw_input("enter time: "))
##        k = (1+(float(k)/360))/20
        change(k/360)
except KeyboardInterrupt:
    p.stop()
    GPIO.cleanup()
    exit
