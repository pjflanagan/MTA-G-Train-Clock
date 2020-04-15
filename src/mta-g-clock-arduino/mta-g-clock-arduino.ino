
#include <string.h>

#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

#include "credentials.h"

// GLOBALS
bool requested = false;

// WIFI

void init_wifi()
{
  Serial.begin(115200); // can be removed after debugging
  delay(10);
  Serial.println('\n');

  // connect to the network
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(SSID);

  // wait for the Wi-Fi to connect
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print('.');
  }
  Serial.println("\nConnection established.");
}

String send_request()
{
  String response;
  WiFiClientSecure client; // use WiFiClientSecure class to create TLS connection

  // host
  Serial.printf("Connecting to host %s\n", HOST);
  client.setFingerprint(FINGERPRINT);
  if (!client.connect(HOST, HTTPS_PORT))
  {
    Serial.println("Connection failed.");
    return "";
  }

  // path
  Serial.printf("Requesting url %s\n", PATH);
  client.print(String("GET ") + PATH + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  // response
  Serial.println("Request sent.");
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    if(line.charAt(0) == '#') {
      return line;
    }
  }
  return "";
}

// ARDUINO

void setup()
{
  init_wifi();
}

void loop()
{
  if (!requested)
  {
    String response = send_request();
    Serial.println(response);
    requested = true;
  }

  delay(5000);
}
