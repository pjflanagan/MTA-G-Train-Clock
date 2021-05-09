
![NYC Subway Wall Clock](https://raw.githubusercontent.com/pjflanagan/MTA/master/read_me/logo.png)

# MTA

This project uses the MTA GTFS Feed to get the times of upcoming trains for my stop. Using an Arduino compatible ESP8266 this project is capable of representing the time of upcoming trains in each direction using a stepper motor.

## Board

Wemos D1 R2 with ESP8266 WiFi. How to setup IDE:

1.  Go to File > Preferences and copy the URL below to get the ESP board manager extensions
	- http://arduino.esp8266.com/stable/package_esp8266com_index.json (must use http://)
2. Go to Tools > Board > Board Manager > Type "esp8266" and download the Community esp8266 and install
3. Set up the board
	- Tools > Board > NodeMCU 1.0 (ESP-12E Module)
	- Tools > Flash Size > 4M (3M SPIFFS)
	- Tools > CPU Frequency > 80 Mhz
	- Tools > Upload Speed > 115200
	- Tools > Port > (select board port, if not found see step 4)
4. Install esptool.py, running this will find the board on the command line
	- https://pypi.org/project/esptool/

## Concept

![Grandfather Clock Concept](https://raw.githubusercontent.com/pjflanagan/MTA/master/read_me/concept.jpg)
