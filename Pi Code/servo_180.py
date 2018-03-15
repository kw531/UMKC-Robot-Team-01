import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)

p.start(.5)

p.ChangeDutyCycle(2) # Open hatch
time.sleep(5)
print("closing")
p.ChangeDutyCycle(.5)  # Close hatch
time.sleep(1) 

p.stop()
GPIO.cleanup()
