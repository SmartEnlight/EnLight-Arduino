#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include "BluetoothManager.h"

constexpr auto BluetoothRX = 3;
constexpr auto BluetoothTX = 2;

BluetoothManager bluetoothManager(BluetoothTX, BluetoothRX);

void setup()
{
	Serial.begin(9600);
	bluetoothManager.Begin(9600);
}

void loop()
{
	//bluetoothManager.SerialWrite("HELLOWORLD\r\n");
	char readchar = bluetoothManager.SerialRead();
	if (readchar != '\0') {
		Serial.write(readchar);
	}
	if (Serial.available()) {
		bluetoothManager.SerialWrite(Serial.read());
	}
}