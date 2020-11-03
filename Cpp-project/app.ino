#include <SoftwareSerial.h>
#define BT_RXD 2
#define BT_TXD 3
#define SensorA0 0
#define SensorD0 9
#define RedLed 5
#define WhiteLed 6

SoftwareSerial bluetooth(BT_RXD, BT_TXD);
 
int averagesound = 0;
bool isnoising = false;

bool isRedOn = false;

void setup() {
	Serial.begin(9600);
	pinMode(SensorD0, INPUT);
	pinMode(RedLed, OUTPUT);
	pinMode(WhiteLed, OUTPUT);
	digitalWrite(WhiteLed, HIGH);
  	bluetooth.begin(9600);
	averagesound = analogRead(SensorA0);

	for (size_t i = 0; i < 10; i++)
		averagesound = ((averagesound * 2) + analogRead(SensorA0)) / 3.0f;
}

void loop() {
	if (isnoising) {
		for (size_t i = 0; i < 10000; i++) {
			if (averagesound + 4 < analogRead(SensorA0))
				i = 0;
		}
		isnoising = false;
		return;
	}

	int currsound = analogRead(SensorA0);

	if (averagesound + 3 < currsound) {
		isnoising = true;
		if (!isRedOn) {
			for (size_t i = 0; i <= 255; i++)
			{
				analogWrite(WhiteLed, 255 - i);
				delay(20);
			}
			for (size_t i = 0; i <= 255; i++)
			{
				analogWrite(RedLed, i);
				delay(20);
			}
			isRedOn = true;
		}
		bluetooth.write("[");
		String currsoundstr = String(currsound);
		for (size_t i = 0; i < 4 - currsoundstr.length(); i++)
			bluetooth.write('0');
		char cstr[16];
		itoa(currsound, cstr, 10);
		bluetooth.write(cstr);
		bluetooth.write("]\r\n");
	} else {
		//digitalWrite(RedLed, LOW);
		//digitalWrite(WhiteLed, HIGH);
		if (isRedOn) {
			for (size_t i = 0; i <= 255; i++)
			{
				analogWrite(RedLed, 255 - i);
				delay(20);
			}for (size_t i = 0; i <= 255; i++)
			{
				analogWrite(WhiteLed, i);
				delay(20);
			}
			isRedOn = false;
		}
		//averagesound = ((averagesound * 2) + currsound) / 3.0f;
	}
	
	
	// Serial.print("======");
	// Serial.print(averagesound);
	// Serial.print("==");
	// Serial.print(currsound);
	// Serial.println("======");
}