import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(18, GPIO.IN)#, pull_up_down=GPIO.PUD_UP)



def interrupt_handler(channel):

    print("interrupt handler")

    if channel == 18:
        print("state reset by event on pin 8")




##GPIO.add_event_detect(18, GPIO.RISING,
##                      callback=interrupt_handler,
##                      bouncetime=200)


while (True):
    if(GPIO.input(18)==GPIO.HIGH):
        print "hello"
    else:
        print "nope"
    time.sleep(1)
