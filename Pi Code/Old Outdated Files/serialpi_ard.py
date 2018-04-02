import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

#received from arduino TX2
GPIO.setup(20, GPIO.IN)

if GPIO.input(20):
    print("rec from arduino tx2")


#time.sleep(1)

#tx from pi to arduino capture on rx2
GPIO.setup(21, GPIO.OUT)

try:
    while True:
        GPIO.output(21, GPIO.HIGH)
        #time.sleep(.1)


except KeyboardInterrupt:
    GPIO.cleanup()
    exit
