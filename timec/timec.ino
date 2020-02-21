#include <TM1637Display.h>
#include <Servo.h>

const int CLK = 2; //Set the CLK pin connection to the display
const int DIO = 3; //Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.

int Relay1 = 6;
int Relay2 = 7;
int Relay3 = 8;
int Relay4 = 9;
int Relay5 = 10;
int Relay6 = 11;
int Relay7 = 12;
Servo myservo;
int count = 1;
int remote = 13;
bool bottonstate = 0;
bool flag = true;
unsigned long endtime = 600; //5400 max

unsigned long time[2] = {0, 0}; // 記錄運行時間
unsigned long timestart = 0;
uint8_t segto;
void setup()
{

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Relay5, OUTPUT);
  pinMode(Relay6, OUTPUT);
  pinMode(Relay7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(remote, INPUT);
  //myservo.attach(4);
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
  display.clear();
  display.showNumberDec(0);
  segto = 0x80 | display.encodeDigit(0);
  display.setSegments(&segto, 1, 1);
  Serial.begin(9600);
}

void loop()
{
  bottonstate = digitalRead(remote);
  if (bottonstate != 0)
  {
    count = 0;
    Serial.println("1");
  }
  if (count == 0)
  {
    display.clear();
    display.showNumberDec(0);
    segto = 0x80 | display.encodeDigit(0);
    display.setSegments(&segto, 1, 1);
    timestart = millis();
    flag = true;
    while (flag)
    {
      time[0] = millis() - timestart;
      if (time[1] != time[0])
      { //避免1毫秒運行2次
        time[1] = time[0];
//
//        if (time[0] % 1000 == 0)
//        { //每1秒執行一次
//          //運行程式碼;
//          //運行完後還可做其他事情
          int minute = time[0] / 60000;
          int second = (time[0] % 60000) / 1000;
          int t = (minute * 100 + second);
          display.showNumberDec(t);
          segto = 0x80 | display.encodeDigit(minute);
          display.setSegments(&segto, 1, 1);
//        }
        
        //if (time[0]/100 == 3690)//4100
        //{
          //myservo.write(140);
          //digitalWrite(4, HIGH);
        //}
        //if (time[0]/100 == 3728)//4110
        //{
          //myservo.attach(95);
          //digitalWrite(4, LOW);
        //}
        if (time[0]/100 == 3708)
        {
          digitalWrite(Relay1, HIGH);
        }
        if (time[0]/100 == 3753)
        {
          digitalWrite(Relay1, LOW);
        }
        if (time[0]/100 == 3709)
        {
          digitalWrite(Relay2, HIGH);
        }
        if (time[0]/100 == 3754)
        {
          digitalWrite(Relay2, LOW);
        }

        if (time[0]/100 == 3770)
        {
          digitalWrite(Relay3, HIGH);
        }
        if (time[0]/100 == 3830)
        {
          digitalWrite(Relay3, LOW);
        }
        if (time[0]/100 == 3772)
        {
          digitalWrite(Relay4, HIGH);
        }
        if (time[0]/100 == 3832)
        {
          digitalWrite(Relay4, LOW);
        }
        if (time[0]/100 == 3774)
        {
          digitalWrite(Relay5, HIGH);
        }
        if (time[0]/100 == 3834)
        {
          digitalWrite(Relay5, LOW);
        }
        if (time[0]/100 == 3776)
        {
          digitalWrite(Relay6, HIGH);
        }
        if (time[0]/100 == 3836)
        {
          digitalWrite(Relay6, LOW);
        }
        if (time[0]/100 == 3778)
        {
          digitalWrite(Relay7, HIGH);
        }
        if (time[0]/100 == 3838)
        {
          digitalWrite(Relay7, LOW);
        }
      }
    }
    count++;

  }
}
