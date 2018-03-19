import smbus
import time
bus = smbus.SMBus(1)
#file=open("blue_vals.txt","w")

# I2C address 0x29
# Register 0x12 has device ver. 
# Register addresses must be OR'ed with 0x80
bus.write_byte(0x29,0x80|0x12)
ver = bus.read_byte(0x29)
# version # should be 0x44
if ver == 0x44:
 print "starting test\n"
 bus.write_byte(0x29, 0x80|0x00) # 0x00 = ENABLE register
 bus.write_byte(0x29, 0x01|0x02) # 0x01 = Power on, 0x02 RGB sensors enabled
 bus.write_byte(0x29, 0x80|0x14) # Reading results start register 14, LSB then MSB
 time.sleep(2)
 print "go!!"
 #t_end=time.time()+10 #10 second test
 while 1: #time.time()<t_end:
  data = bus.read_i2c_block_data(0x29, 0)
  clear = clear = data[1] << 8 | data[0]
  red = data[3] << 8 | data[2]
  green = data[5] << 8 | data[4]
  blue = data[7] << 8 | data[6]
  totalRGB=red+green+blue
  if totalRGB==0:
        totalRGB=ArithmeticError
  pR=float(red)/float(totalRGB)
  pG=float(green)/float(totalRGB)
  pB=float(blue)/float(totalRGB)
  print pR
  print pG
  print pB

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
  elif pR > .25 and pR <.4 and  pG>.26 and pG<.37 and pB>.26 and pB<.37:
      print "Gray\n"
      foundColor="gray"
  else:
      print "Dunno.\n"
      foundColor="Dunno."
 
  time.sleep(1)
else: 
 print "Device not found\n"
#file.close()
