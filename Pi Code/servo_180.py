import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)
print ('start')
p.start(0)
print('next')

a=2.5
print a
p.ChangeDutyCycle(a) # Open hatch
time.sleep(3)

b=7
print b
p.ChangeDutyCycle(b)
time.sleep(3)

c=10.5
print c
p.ChangeDutyCycle(c)
time.sleep(3)

##
##d=7.5
##print d
##p.ChangeDutyCycle(d)
##time.sleep(3)


#360/2=180/7=25.7

p.stop()
GPIO.cleanup()
