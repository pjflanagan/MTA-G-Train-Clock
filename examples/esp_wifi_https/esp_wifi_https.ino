

#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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

	// use WiFiClientSecure class to create TLS connection
	WiFiClientSecure client;

	Serial.printf("Connecting to host %s using fingerprint %s\n", HOST, FINGERPRINT);
	client.setFingerprint(FINGERPRINT);
	if (!client.connect(HOST, HTTPS_PORT))
	{
		Serial.println("Connection failed.");
		return response;
	}

	Serial.printf("Requesting url %s\n", PATH);

	client.print(String("GET ") + PATH + " HTTP/1.1\r\n" +
				 "Host: " + HOST + "\r\n" +
				 "User-Agent: BuildFailureDetectorESP8266\r\n" +
				 "x-api-key:" + KEY + "\r\n" +
				 "Connection: close\r\n\r\n");

	Serial.println("Request sent.");
	while (client.connected())
	{
		String line = client.readStringUntil('\n');
		response = response + line + '\n';
	}
	return response;
}

// ARDUINO

void setup()
{
	init_wifi();
}

void loop()
{
	if (requested == false)
	{
		void send_request();
		requested = true;
	}

	delay(5000);
}
