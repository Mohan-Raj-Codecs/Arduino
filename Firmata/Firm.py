import pyfirmata as fir
from pyfirmata import INPUT,OUTPUT,PWM
from time import sleep
from urllib.request import urlopen
import json


def fetch():
    url="http://3.108.227.188/data.json"
    data = json.loads(urlopen(url).read())
    return data["on"]

board=fir.Arduino('COM3')
it = fir.util.Iterator(board)  
fetch()

##VARS
volt=0.0
on=False
##VARS End


##Setup
net = board.get_pin('d:8:o')
it.start()
##Setup End


##Loop
print("Ready :) ")
while True:
    try:
        if fetch():
            net.write(1)
        else:
            net.write(0)
    except:
        pass
##Loop End
#http://3.108.227.188/

board.exit()
