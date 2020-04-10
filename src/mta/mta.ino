
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "pb_common.h"
#include "pb.h"
#include "pb_decode.h"
#include "gtfs-realtime.pb.h"

#include "credentials.h"

const char *SSID = STASSID;
const char *PASSWORD = STAPSK;
const char *KEY = API_KEY;
const char *URL = API_URL;
int requested = 0;

void setup()
{
	Serial.begin(115200); // can be removed after debugging
	delay(10);
	Serial.println('\n');

	// connect to the network
	WiFi.begin(SSID, PASSWORD);
	Serial.print("Connecting to ");
	Serial.print(SSID);

	// wait for the Wi-Fi to connect
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.print('.');
	}
	Serial.println('\n');
	Serial.println("Connection established!");
}

void loop()
{
	if (requested >= 1)
	{
		delay(5000);
	}
	else if (WiFi.status() == WL_CONNECTED)
	{
		// if the wifi is connected
		HTTPClient http;
		http.begin(URL);
		http.addHeader("x-api-key", KEY)

			// send the request and get the code
			int httpCode = http.GET();
		if (httpCode > 0)
		{ // TODO: == 200
			// get the request response payload
			String payload = http.getString();
			// print the response payload
			Serial.println(payload);
		}

		// close connection
		http.end();
		requested += 1;
	}

	delay(5000);
}
