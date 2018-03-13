import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(18, GPIO.OUT)

GPIO.setup(22, GPIO.OUT)

#trapped door
p = GPIO.PWM(18, 50)


p.start(2.5)

p.ChangeDutyCycle(10) # Open hatch
time.sleep(5) 
p.ChangeDutyCycle(2.5)  # Close hatch
time.sleep(1) 


#spining 360
q = GPIO.PWM(22, 50)

q.start(2.5)

q.ChangeDutyCycle(10) # Open hatch
time.sleep(5) 
q.ChangeDutyCycle(2.5)  # Close hatch
time.sleep(1) 


p.stop()
GPIO.cleanup()
