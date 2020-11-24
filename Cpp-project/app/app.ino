#include <SoftwareSerial.h>
#include <math.h>

#define BT_RXD 2
#define BT_TXD 3
#define SensorA0 0
#define SensorD0 9
#define BUZZER 10
#define RedLed 5
#define WhiteLed 6

#define MULTIPLY 1.01f

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
}

void loop()
{
  float soundValue = analogRead(SensorA0);

  String soundStr = String(soundValue), averageSoundStr  = String(averageSound);
 
  Serial.println(String("SoundValue : ") + String(soundStr) +  String(" ||| AverageSound : ") + String(averageSoundStr) + " ||| Decibel : " + String((int) ((soundValue+83.2073) / 11.003 * 2.0f )));
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
        delay(1);
      }
      isRedOn = true;
    }
    bluetooth.write("[");
    String currsoundstr = String((int) ((soundValue+83.2073) / 11.003 * 2.0f ));
    Serial.println(currsoundstr);
    for (size_t i = 0; i < 4 - currsoundstr.length(); i++) {
      bluetooth.write('0');
    }
    bluetooth.write(currsoundstr.c_str());
    bluetooth.write("]\r\n");
    delay(3000);
 } else {
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

 averageSound = ( averageSound * 9 + soundValue ) / 10;

}
