/*
 ESP8266 CheckFlashConfig by Markus Sattler

 This sketch tests if the EEPROM settings of the IDE match to the Hardware

 */
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>

const char *ssid = "";        // cannot be longer than 32 characters!
const char *pass = "";       // WiFi password

void setup(void) {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);

	ArduinoOTA.begin();
}

void loop() {
	if (WiFi.status() != WL_CONNECTED) {
		Serial.print("Connecting via WiFi to ");
		Serial.print(ssid);
		Serial.println("...");

		WiFi.begin(ssid, pass);

		if (WiFi.waitForConnectResult() != WL_CONNECTED) {
			return;
		}

		Serial.println("");
		Serial.println("WiFi connect: Success");
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());

	}
	ArduinoOTA.handle();

	uint32_t realSize = ESP.getFlashChipRealSize();
	uint32_t ideSize = ESP.getFlashChipSize();
	FlashMode_t ideMode = ESP.getFlashChipMode();

	Serial.printf("Flash real id:   %08X\n", ESP.getFlashChipId());
	Serial.printf("Flash real size: %u\n\n", realSize);

	Serial.printf("Flash ide  size: %u\n", ideSize);
	Serial.printf("Flash ide speed: %u\n", ESP.getFlashChipSpeed());
	Serial.printf("Flash ide mode:  %s\n",
			(ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" :
				ideMode == FM_DIO ? "DIO" :
				ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));

	if (ideSize != realSize) {
		Serial.println("Flash Chip configuration wrong!\n");
	} else {
		Serial.println("Flash Chip configuration ok.\n");
	}

	delay(5000);
}
