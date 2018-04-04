import RPi.GPIO as GPIO
import time

dispense = 0 # For tracking what has been dispensed or not

GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT) # Main Servo
GPIO.setup(16, GPIO.OUT) # Bottom Servo

p = GPIO.PWM(12, 50) # Main Servo Setup
p.start(0)
b = GPIO.PWM(16, 50) # Bottom Servo Setup
b.start(7.5)

def servoOp(position):
# Moves the servo to the position
    p.ChangeDutyCycle(position)  # turn towards 90 degree
    
def dispenseCoin():
# Move the coins to the slot, then dispense
    print ("dispenseCoin()")
#Dispensing Colors
#Black - 10.0
#Yellow - 9.85
#Cyan - 9.70
#Magenta - 9.57
#Red - 9.10
#Green - 9.25
#Blue - 9.4

    if dispense == 0: #red
        print("red dispense")
        pos=9.67
    elif dispense == 1: #green
        print("green dispense")
        pos=9.82
    elif dispense == 2: #blue
        print("blue dispense")
        pos=10.1
    elif dispense == 3: #gray/black
        print("black dispense")
        pos=9.55
    elif dispense == 4: #cyan
        print("cyan dispense")
        pos=9.25
    elif dispense == 5: #magenta
        print("mag dispense")
        pos=9.1
    elif dispense == 6: #yellow
        print("yellow dispense")
        pos=9.4
    else:
        pos=7.55

    servoOp(pos) # Position the coins
    time.sleep(2)
    moveBottomServo() #dispense the coins
    time.sleep(2)
    print "ET GO HOME"
    servoOp(7.55)
    time.sleep(3)
        
def moveBottomServo():
    b.ChangeDutyCycle(7.5)  # Open
    time.sleep(2)
    b.ChangeDutyCycle(10.5) # Close

    
count = 0
dispense=2

while count < 1:
    dispenseCoin()
    dispense=dispense+1
    count=count+1
    
p.stop()
b.stop()
GPIO.cleanup()
