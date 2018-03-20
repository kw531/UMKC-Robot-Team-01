import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(25, GPIO.IN) ##pin 22

while True:
    if GPIO.input(25):
        print("high/on")
    else:
        print("off")
