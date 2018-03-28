import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)

p.start(0)

try:
        while True:
            print("black")
            p.ChangeDutyCycle(9.1)  # turn towards 90 degree
            time.sleep(5) # sleep 1 second

            print("yellow")
            p.ChangeDutyCycle(10.05)  # turn towards 0 degree
            time.sleep(5) # sleep 1 second

            print("red")
            p.ChangeDutyCycle(9.2)  # turn towards 90 degree
            time.sleep(5) # sleep 1 second

            print("cyan")
            p.ChangeDutyCycle(9.94)  # turn towards 0 degree
            time.sleep(5) # sleep 1 second

            print("green")
            p.ChangeDutyCycle(9.1)  # turn towards 90 degree
            time.sleep(5) # sleep 1 second
            print("mag")
            p.ChangeDutyCycle(9.75)  # turn towards 90 degree
            time.sleep(5) # sleep 1 second
            print("blue")
            p.ChangeDutyCycle(9.5)  # turn towards 90 degree
            time.sleep(5) # sleep 1 second
            #p.ChangeDutyCycle(12.5) # turn towards 180 degree
            #time.sleep(1) # sleep 1 second 
except KeyboardInterrupt:
    p.stop()
    GPIO.cleanup()

#9.94 cyan
#9.75 magenta
#9.2 red
#9.1 Black
#9.4 Green
#9.5 Blue
#10.05 Yellow

    
