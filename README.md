
# MTA

This project uses the MTA GTFS Feed to get the times of upcoming trains for my stop. Using an Arduino compatible ESP this project is capable of representing the time of upcoming trains in each direction using a stepper motor.

## Board

Wemos D1 R2 with ESP8266 WiFi. How to setup IDE:

1.  Go to File > Preferences and copy the URL below to get the ESP board manager extensions
	- http://arduino.esp8266.com/stable/package_esp8266com_index.json (must use http://)
2. Go to Tools > Board > Board Manager > Type "esp8266" and download the Community esp8266 and install
3. Set up the board
	- Tools > Board > Wemos D1 RR
	- Tools > Flash Size > 4M (3M SPIFFS)
	- Tools > CPU Frequency > 80 Mhz
	- Tools > Upload Speed > 921600
	- Tools > Port > (select board port, if not found see step 4)
4. Install esptool.py, running this will find the board on the command line
	- https://pypi.org/project/esptool/

## Help

### ESP8266
- https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html
- https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html#begin
- https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/

### WiFi / HTTP
- https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure
- https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/HTTPSRequest/HTTPSRequest.ino

### GTFS
- https://developers.google.com/transit/gtfs-realtime/reference
- https://developers.google.com/transit/gtfs-realtime/gtfs-realtime-proto
- https://developers.google.com/transit/gtfs-realtime/examples/python-sample

### MTA
- http://api.mta.info
- http://datamine.mta.info/sites/all/files/pdfs/GTFS-Realtime-NYC-Subway%20version%201%20dated%207%20Sep.pdf

### GRPC / NanoPB
- https://developers.google.com/protocol-buffers/docs/cpptutorial#compiling-your-protocol-buffers
- https://www.dfrobot.com/blog-1177.html
- https://www.dfrobot.com/blog-1161.html
- https://github.com/nanopb/nanopb/blob/master/examples/simple/simple.c
- https://jpa.kapsi.fi/nanopb/docs/concepts.html

### Stepper
- https://www.instructables.com/id/BYJ48-Stepper-Motor/
- https://www.arduino.cc/en/Reference/StepperExample
