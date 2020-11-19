#include <SoftwareSerial.h>

#define BT_RXD 2
#define BT_TXD 3
#define SensorA0 0
#define SensorD0 9
#define BUZZER 10
#define RedLed 5
#define WhiteLed 6

#define MULTIPLY 1.05f

SoftwareSerial bluetooth(BT_RXD, BT_TXD);

float averageSound = 0;

bool isRedOn = false;

void setup()
{
	Serial.begin(9600);
	pinMode(SensorD0, INPUT);
	pinMode(RedLed, OUTPUT);
	pinMode(WhiteLed, OUTPUT);
  pinMode(BUZZER, OUTPUT);
	digitalWrite(WhiteLed, HIGH);
	bluetooth.begin(9600);
	averageSound = analogRead(SensorA0);

//	for (size_t i = 0; i < 10; i++)
//		averageSound = ((averagesound * 2) + analogRead(SensorA0)) / 3.0f;
}

void loop()
{
	float soundValue = analogRead(SensorA0);

  String soundStr = String(soundValue), averageSoundStr  = String(averageSound);
 
	Serial.println(String("SoundValue : ") + String(soundStr) +  String(" ||| AverageSound : ") + String(averageSoundStr));
 if(averageSound * MULTIPLY < soundValue) {
   if (!isRedOn)
    {
      for (size_t i = 0; i <= 255; i++)
      {
        analogWrite(WhiteLed, 255 - i);
        analogWrite(RedLed, i);

        if(i % 40 == 0 && i % 80 != 0) {
          //buzzer on
          digitalWrite(BUZZER, HIGH);
        } else if (i % 80 == 0) {
          //buzzer off
          digitalWrite(BUZZER, LOW);
        }
//        if(i == 0) {
//          digitalWrite(BUZZER, HIGH);
//        } else if (i == 255) {
//          digitalWrite(BUZZER, LOW);
//        }
        delay(1);
      }
      delay(3000);
      isRedOn = true;
    }
    bluetooth.write("[");
    String currsoundstr = String((int)soundValue);
    for (size_t i = 0; i < 4 - currsoundstr.length(); i++) {
      bluetooth.write('0');
    }
    String cstr  = String((int)soundValue);
    bluetooth.write(cstr.c_str());
    bluetooth.write("]\r\n");
 } else {
   averageSound = ( averageSound * 9 + soundValue ) / 10;
   if (isRedOn)
    {
      for (size_t i = 0; i <= 255; i++)
      {
        analogWrite(RedLed, 255 - i);
        analogWrite(WhiteLed, i);
        delay(1);
      }
      isRedOn = false;
    }
 }

   
//	if (isnoising)
//	{
//		for (size_t i = 0; i < 10000; i++)
//		{
////      delay(1);
//			if (averagesound + 4 < analogRead(SensorA0)) 
//			{
//				  i = 0;
//			}
//		}
//		isnoising = false;
//		return;
//	}
//
//	int currsound = analogRead(SensorA0);
//
//	if (averagesound + 3 < currsound)
//	{
//		isnoising = true;
//		if (!isRedOn)
//		{
//			for (size_t i = 0; i <= 255; i++)
//			{
//				analogWrite(WhiteLed, 255 - i);
//        analogWrite(RedLed, i);
//				delay(1);
//			}
//			isRedOn = true;
//		}
//		bluetooth.write("[");
//		String currsoundstr = String(currsound);
//		for (size_t i = 0; i < 4 - currsoundstr.length(); i++)
//			bluetooth.write('0');
//		char cstr[16];
//		itoa(currsound, cstr, 10);
//		bluetooth.write(cstr);
//		bluetooth.write("]\r\n");
//	}
//	else
//	{
//		//digitalWrite(RedLed, LOW);
//		//digitalWrite(WhiteLed, HIGH);
//		if (isRedOn)
//		{
//			for (size_t i = 0; i <= 255; i++)
//			{
//				analogWrite(RedLed, 255 - i);
//        analogWrite(WhiteLed, i);
//				delay(1);
//			}
//			isRedOn = false;
//		}
//		//averagesound = ((averagesound * 2) + currsound) / 3.0f;
//	}

	// Serial.print("======");
	// Serial.print(averagesound);
	// Serial.print("==");
	// Serial.print(currsound);
	// Serial.println("======");
}
