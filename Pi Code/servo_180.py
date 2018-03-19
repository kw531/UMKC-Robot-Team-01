import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)

p.start(7.5)

while 1:
    print("5")
    p.ChangeDutyCycle(2.5) # Open hatch
    time.sleep(3)
    p.ChangeDutyCycle(7.5)
    print("10")
    time.sleep(3)
   # p.ChangeDutyCycle(10)  # Close hatch
   # time.sleep(13)
##print("2")
##p.ChangeDutyCycle(2)  # Close hatch
##time.sleep(1)
##print("5")
##p.ChangeDutyCycle(5)  # Close hatch
##time.sleep(1)
##print("10")
##p.ChangeDutyCycle(10)  # Close hatch
##time.sleep(1)

p.stop()
GPIO.cleanup()
