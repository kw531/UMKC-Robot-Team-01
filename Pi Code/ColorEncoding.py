import RPi.GPIO as GPIO
import time
import smbus

def getColor():
  data = bus.read_i2c_block_data(0x29, 0)
  clear = clear = data[1] << 8 | data[0]
  red = data[3] << 8 | data[2]
  green = data[5] << 8 | data[4]
  blue = data[7] << 8 | data[6]

    #Finds the ratios
  totalRGB=red+green+blue
  if totalRGB==0:
        totalRGB=1
  pR=float(red)/float(totalRGB)
  pG=float(green)/float(totalRGB)
  pB=float(blue)/float(totalRGB)
  #print pR
  #print pG
  #print pB

    #Prints color to screen
  if pR > .10 and pR <.2 and  pG>.3 and pG<.35 and pB>.39 and pB<.60:
      print "Blue\n"
      foundColor="blue"
  elif pR > .10 and pR <.15 and  pG>.35 and pG<.40 and pB>.45 and pB<.55:
      print "Cyan\n"
      foundColor="cyan"
  elif pR > .10 and pR <.32 and  pG>.38 and pG<.60 and pB>.25 and pB<.35:
      print "Green\n"
      foundColor="green"
  elif pR > .30 and pR <.55 and  pG>.28 and pG<.55 and pB>.1 and pB<.25:
      print "Yellow\n"
      foundColor="yellow"
  elif pR > .5 and pR <.6 and  pG>.1 and pG<.2 and pB>.20 and pB<.30:
      print "Pink\n"
      foundColor="pink"
  elif pR > .50 and pR <.80 and  pG>.10 and pG<.25 and pB>.10 and pB<.25:
      print "Red\n"
      foundColor="red"
  elif pR > .25 and pR <.37 and  pG>.26 and pG<.37 and pB>.26 and pB<.37:
      print "Gray\n"
      foundColor="gray"
  else:
      print "Dunno.\n"
      foundColor="Dunno."

  return foundColor

def change(k):
    p.ChangeDutyCycle(1)
    time.sleep(k)
    p.ChangeDutyCycle(0)

GPIO.setmode(GPIO.BOARD)

GPIO.setup(12, GPIO.OUT)

p = GPIO.PWM(12, 50)

p.start(0)
bus = smbus.SMBus(1)

try:
    # I2C address 0x29
    # Register 0x12 has device ver. 
    # Register addresses must be OR'ed with 0x80
    bus.write_byte(0x29,0x80|0x12)
    ver = bus.read_byte(0x29)
    # version # should be 0x44
    if ver == 0x44:
     bus.write_byte(0x29, 0x80|0x00) # 0x00 = ENABLE register
     bus.write_byte(0x29, 0x01|0x02) # 0x01 = Power on, 0x02 RGB sensors enabled
     bus.write_byte(0x29, 0x80|0x14) # Reading results start register 14, LSB then MSB
     while True:
           color="blue"
           print("starting")
           colorFound=getColor()
           if colorFound==color:
               p.ChangeDutyCycle(0)  # turn towards 90 degree
               time.sleep(5) # sleep 1 second
           else:
               print("hi")
               change(.05)
           time.sleep(.1)
    else: 
        print "Device not found\n"

except KeyboardInterrupt:
    p.stop()
    GPIO.cleanup()
    exit
