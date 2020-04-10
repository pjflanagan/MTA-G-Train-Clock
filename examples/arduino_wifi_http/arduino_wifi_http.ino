
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>
#include "credentials.h"

const char* ssid     = STASSID;         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = STAPSK;     // The password of the Wi-Fi network
bool requested = 0;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');

  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  if (requested >= 1) {
    delay(5000);
  } else if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
    int httpCode = http.GET(); //Send the request

    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection
    requested += 1;

  }
 
  delay(5000);
}
