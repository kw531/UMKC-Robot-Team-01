import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

GPIO.setup(18, GPIO.IN) ##pin 22

while True:
    if GPIO.input(18):
        print("high/on")
    else:
        print("off")
