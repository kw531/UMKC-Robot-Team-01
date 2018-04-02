import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)

p.start(0)

try:
        while True:
                p.ChangeDutyCycle(7.5) # turn towards 180 degree
                time.sleep(5) # sleep 1 second
                
                print("open")
                a=9.55
                p.ChangeDutyCycle(a)  # turn towards 90 degree
                time.sleep(6) # sleep 1 second
##
##                print("yellow")
##                p.ChangeDutyCycle(9.33)  # turn towards 0 degree
##                time.sleep(5) # sleep 1 second
##                ##
##                print("red")  #or9.9
##                p.ChangeDutyCycle(9.8)  # turn towards 90 degree
##                time.sleep(5) # sleep 1 second
##                ##
##                print("cyan")
##                p.ChangeDutyCycle(9.20)  # turn towards 0 degree
##                time.sleep(5) # sleep 1 second
##                print("green")
##
##                p.ChangeDutyCycle(9.82)  # turn towards 90 degree
                        #or10.2 or 9
##                time.sleep(5) # sleep 1 second
##                print("mag")
                
##                p.ChangeDutyCycle(9.0)  # turn towards 90 degree
##                time.sleep(5) # sleep 1 second
##                print("blue")
                
##                p.ChangeDutyCycle(9.95)  # turn towards 90 degree
##                time.sleep(5) # sleep 1 second

                
##                p.ChangeDutyCycle(12.5) # turn towards 180 degree
##                print("reset")
##                
##                print("done")
except KeyboardInterrupt:
    p.stop()
    GPIO.cleanup()

#Collection Colors
#Black - 9.5
#Yellow - 9.33
#Cyan - 9.23
#Magenta - 9.0
#Red - 9.7
#Green - 9.8
#Blue - 9.94

#Dispensing Colors
#Black - 10.0
#Yellow - 9.85
#Cyan - 9.70
#Magenta - 9.57
#Red - 9.10
#Green - 9.25
#Blue - 9.4
