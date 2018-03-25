import RPi.GPIO as GPIO
import time
import smbus
GPIO.setmode(GPIO.BOARD)

def getColor():
  # Gets a color from the color sensor on the color encoder for the dispenser
  bus.write_byte(0x29, 0x80|0x14) # Reading results start register 14, LSB then MSB
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
  print pR, pG, pB

    #Prints color to screen
  if pR > .10 and pR <.20 and  pG>.3 and pG<.35 and pB>.39 and pB<.60:
      print "Blue\n"
      foundColor="blue"
  elif pR > .10 and pR <.20 and  pG>.35 and pG<.40 and pB>.40 and pB<.55:
      print "Cyan\n"
      foundColor="cyan"
  elif pR > .10 and pR <.32 and  pG>.38 and pG<.60 and pB>.25 and pB<.35:
      print "Green\n"
      foundColor="green"
  elif pR > .30 and pR <.55 and  pG>.28 and pG<.55 and pB>.1 and pB<.25:
      print "Yellow\n"
      foundColor="yellow"
  elif pR > .5 and pR <.6 and  pG>.1 and pG<.2 and pB>.20 and pB<.30:
      print "Magenta\n"
      foundColor="magenta"
  elif pR > .50 and pR <.80 and  pG>.10 and pG<.25 and pB>.10 and pB<.25:
      print "Red\n"
      foundColor="red"
  elif pR > .3 and pR <.4 and  pG>.3 and pG<.37 and pB>.3 and pB<.37:
      print "Gray\n"
      foundColor="gray"
  else:
      print "Dunno.\n"
      foundColor="Dunno."

  return foundColor

def change(d,k):
  # Changes the direction of the servo basked on the target color
  
    print("----moving----")
    if d=='counter':
      # Move counter clockwise
      p.ChangeDutyCycle(1) #on
    if d=='clock':
      # Move clockwise
      p.ChangeDutyCycle(60)
    time.sleep(k/2)
    p.ChangeDutyCycle(0)#off
    time.sleep(k/2)

def moveToColor(color, spd):
  # Changes the direction of the servo based on the target color
  if color == 'yellow' or color == 'cyan' or color == 'magenta' or color == 'gray':
    change('counter', spd)
  if color == 'red' or color == 'green' or color == 'blue':
    change('clock', spd)


GPIO.setup(18, GPIO.IN) # Go Button
GPIO.setup(12, GPIO.OUT) # Servo 1
GPIO.setup(40, GPIO.OUT) # Serial to Arduino

p = GPIO.PWM(12, 50)
p.start(0) # Start the servo at 0, (no predefined angles?)

bus = smbus.SMBus(1)

try:
    # Color Sensor Setup
    bus.write_byte(0x29,0x80|0x12)
    ver = bus.read_byte(0x29)
    bus.write_byte(0x29, 0x80|0x00) # 0x00 = ENABLE register
    bus.write_byte(0x29, 0x01|0x02) # 0x01 = Power on, 0x02 RGB sensors enabled

    if ver == 0x44:
     while True:
       if GPIO.input(18):
         GPIO.output(40, GPIO.HIGH) # This doesn't work, fix, maybe use interrupts
         color="green" # This is where a color from the pi camera comes in
        
        wheelColor=getColor() # Get the encoder current position
         while wheelColor != color:
           print("-------polling-------")
           time.sleep(.1)
           if wheelColor=='Dunno.':
             # Color Sensor got a bad value, pluse it until it gets a proper value
             moveToColor(color, .02)
           else:
             moveToColor(color, .20) # move time
           time.sleep(.2)
           print("     ")
           wheelColor=getColor() # Get new color
           print ("I found"), wheelColor
         print("~~~~~~~~~~found!~~~~~~~~~~~~~~")
         time.sleep(2)
       else:
            GPIO.output(40, GPIO.LOW) # bad, fix
    else: 
        print "Device not found\n"

except KeyboardInterrupt: # Control C is life
    p.stop()
    GPIO.cleanup()
    exit
