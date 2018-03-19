import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(16, GPIO.OUT)

p = GPIO.PWM(16, 50)

p.start(7.5)


p.ChangeDutyCycle(2.5) # Open hatch
time.sleep(3)
p.ChangeDutyCycle(7.5)
time.sleep(3)

p.stop()
GPIO.cleanup()
