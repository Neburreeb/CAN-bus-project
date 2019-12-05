// CAN-BUS Receive Data

#include "mcp_can.h"
#include <SPI.h>
#include <stdio.h>
#include <LiquidCrystal.h>    //Library for using LCD display

#define INT8U unsigned char
const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);
const int LED_Pin = 8;

//instellingen LCD scherm
const int rs = 7, E = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  
LiquidCrystal lcd(rs, E, d4, d5, d6, d7);  //Define LCD display pins RS,E,D4,D5,D6,D7

INT8U len = 0;
INT8U buf[8];
unsigned char canId;
char str[20];

int btnValue;
int potValue;

void setup()
{
  
  Serial.begin(115200);
  pinMode(LED_Pin, OUTPUT);
 

    while (CAN_OK != CAN.begin(CAN_125KBPS))   // canbus baudrate 500kbps
    {
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.println("CAN BUS fail!!!");
        lcd.setCursor(0,1);
        lcd.println("Init again...");
        delay(100);
        lcd.clear();
    }

    lcd.println("CAN BUS Succesful");
}
void loop()
{

      while (CAN_MSGAVAIL == CAN.checkReceive())
        {
      CAN.readMsgBuf(&len, buf);
      canId = CAN.getCanId();
      potValue = buf[0];
      btnValue = buf[1];
      }
       lcd.begin(16,2);
       lcd.setCursor(0,0);
       lcd.print("Pot Value: ");
       lcd.println(potValue);
       lcd.setCursor(0,1);
       lcd.print("Button Vl: ");
       lcd.println(btnValue);
       delay(1000);
       lcd.clear();
    }
    
