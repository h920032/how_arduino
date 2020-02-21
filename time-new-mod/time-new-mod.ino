#include <TM1637Display.h>
#include <Servo.h>

const int CLK = 2; //Set the CLK pin connection to the display
const int DIO = 3; //Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);  //set up the 4-Digit Display.

int Relay1 = 7;//蘋果醬1
int Relay2 = 10; //洛絲巾
int Relay3 = 13; 
int Relay4 = 12;
int Relay5 = 11;
int Relay6 = 6;//球降
int Relay7 = 9; //排落
int Relay8 = 8; //瀑布排
int Relay9 = 5;//蘋果醬2
Servo myservo;
int ser1 = 4;
int count = 1;
int bottonstate = 0;
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
  pinMode(Relay8, OUTPUT);
  pinMode(Relay9, OUTPUT);
  myservo.attach(ser1);
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
  display.clear();
  display.showNumberDec(0);
  segto = 0x80 | display.encodeDigit(0);
  display.setSegments(&segto, 1, 1);
  Serial.begin(9600);
}

void loop()
{
  Serial.println( analogRead(A0));
  bottonstate = analogRead(A0);
  if (bottonstate > 500 || Serial.read() == '1')
  {
    count = 0;
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
        
        if (time[0] >= endtime*7200)
        {
          flag = false;
        }
        if (time[0]/100 == 40)
        {
          digitalWrite(Relay1, HIGH);
        }
        if (time[0]/100 == 140)
        {
          digitalWrite(Relay1, LOW);
        }
        if (time[0]/100 == 2520)
        {
          digitalWrite(Relay2, HIGH);
        }
        if (time[0]/100 == 2522)
        {
          digitalWrite(Relay2, LOW);
        }
        if (time[0]/100 == 2830)
        {
          digitalWrite(Relay3, HIGH);
        }
        if (time[0]/100 == 2833)
        {
          digitalWrite(Relay3, LOW);
        }
        if (time[0]/100 == 2925)//2490
        {
          digitalWrite(Relay5, HIGH);
        }
        if (time[0]/100 == 2930)//2960
        {
          digitalWrite(Relay5, LOW);
        }
        if (time[0]/100 == 3020)
        {
          digitalWrite(Relay4, HIGH);
        }
        if (time[0]/100 == 3025)
        {
          digitalWrite(Relay4, LOW);
        }
        
        if (time[0]/100 == 3195)
        {
          digitalWrite(Relay6, HIGH);
        }
        if (time[0]/100 == 3260)
        {
          digitalWrite(Relay6, LOW);
        }
        if (time[0]/100 == 3490)
        {
          digitalWrite(Relay7, HIGH);
        }
        if (time[0]/100 == 3493)
        {
          digitalWrite(Relay7, LOW);
        }
        if (time[0]/100 == 3580)
        {
          digitalWrite(Relay8, HIGH);
        }
        if (time[0]/100 == 3582)
        {
          digitalWrite(Relay8, LOW);
        }
        if (time[0]/100 == 3890)
        {
          digitalWrite(Relay9, HIGH);
        }
        if (time[0]/100 == 3938)
        {
          digitalWrite(Relay9, LOW);
        }
      }
    }
    count++;
  }
}
