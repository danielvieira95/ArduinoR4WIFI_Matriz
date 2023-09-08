/*
Programa Scan de redes wifi e animação na matriz de led
08/09/2023
*/
#include <WiFiS3.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
const uint32_t d[] = {
    0x1c012,
		0x1201201,
		0x201c0000,
		66
};

const uint32_t a[] = {
    0xc012012,
		0x1201e01,
		0x20120000,
		66
};  
const uint32_t n[] = {
    0x10,
		0x82882482,
		0x28210000,
		66
};
const uint32_t i[] = {
   0x4004,
		0x400400,
		0x40040040,
		66
};
const uint32_t e[] = {
   0xe008,
		0x800e00,
		0x800800e0,
		66
};
const uint32_t l[] = {
   0x4004004,
		0x400400,
		0x40040078,
		66
};
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   matrix.begin();

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
}

void loop() {
  matrix.loadFrame(d);
  delay(500);
   matrix.loadFrame(a);
  delay(500);
   matrix.loadFrame(n);
  delay(500);
   matrix.loadFrame(i);
  delay(500);
   matrix.loadFrame(e);
  delay(500);
   matrix.loadFrame(l);
  delay(500);
  byte mac[6];
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
  WiFi.macAddress(mac);
  Serial.println();
  Serial.print("Your MAC Address is: ");
  printMacAddress(mac);
  delay(100);
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a WiFi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print(" Signal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print(" Encryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_WPA:
      Serial.println("WPA");
      break;
    case ENC_TYPE_WPA2:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_WPA3:
      Serial.print("WPA3");
      break;   
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      Serial.println("Unknown");
      break;
  }
}


void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
