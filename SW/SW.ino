/*  -Project RP 5V-
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */
#include <HDQ.h>
#include <U8g2lib.h>
#include <avr/power.h>
#include <avr/pgmspace.h>

#define VER "0.0001"

int MSB=0; //for HDQ readings
int LSB=0; //for HDQ readings
unsigned long t0=2000; //time variables for millis based delay function
unsigned long t1; //time variables for millis based delay function
unsigned long timediff;
int page=0; //Current display page
int pointerx=0; //multi purpose pointers
int pointery=0; //multi purpose pointers
int val=0; //temp value
float othval=0; //temp float value
bool chg=0; //charge detection
bool menubut=0;
bool funcbut=0;
int menutrig=0;
int functrig=0;
int contrastval=255;

bool latch=0; //for debounce
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R2); //Define SH1106 OLED display on framebuffer mode

HDQ gg(3); //Battery is connected on D4 Pin

#include "debugpage.h"
#include "contrastpage.h"
#include "mainpage.h"
#include "secondpage.h"

void setup() {
  
  pinMode(4,INPUT); //14
  pinMode(5,INPUT); //15
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH); //Enable step up
  oled.initDisplay();
  oled.clearBuffer();
  oled.begin();
  delay(250);
 
//  power_adc_disable();
//  power_spi_disable();
 // oled.sendF("caca", 0xd5 , 0xf0,0x30,0x31); //fix OLED flicker
  Serial.begin(115200);
  if(digitalRead(5)==1){
    DevPage(0);
  }
  if(digitalRead(15)==1){
    DevPage(1);
  }
  if(digitalRead(14)==1 && digitalRead(15)==1){
    DevPage(2);
  }
  /* Power Saving */ 
//  USBCON|=(1<<OTGPADE);
//  if((USBSTA&(1<<VBUS))!=1){  //checks state of VBUS
//    power_usb_disable();
//    USBCON |= (1 << FRZCLK);             // Freeze the USB Clock              
//    PLLCSR &= ~(1 << PLLE);              // Disable the USB Clock (PPL) 
//    UDINT  &= ~(1 << SUSPI);
//    USBCON &=  ~(1 << USBE  );
   
//   }
   
}

void loop() {
  /* Should refresh every 2 sec while scanning any key action without delays */ 
  t1=millis();
  timediff=t1-t0;
  
  ScanButton();

  
  page=SetPage();
  if(timediff >= 250){
    if(page==0){
      MainPage();
    }
    if(page==1){
      SecPage();
    }
    if(page==2){
      ContPage();
    }
    t0=t1; //sync time variables
  }
}






void ScanButton(){
  if(digitalRead(4)==1){ //read menu button
  menutrig=menutrig+1;
  }else{
  menutrig=0;
  }
  
  if(digitalRead(5)==1){ //read function button 
  functrig=functrig+1;
  }else{
  functrig=0;
  }

  if(menutrig>=1000){ //some sort of debouncing
  if(menutrig>=1200){latch=1;}
  if(latch==1 && menubut==1){menutrig=0;}
  menubut=1;
  menutrig=0;
  timediff=2000;
  }else{
  menubut=0;
  latch=0;
  }
  if(functrig>=1000){
  if(functrig>=1200){latch=1;}
  if(latch==1 && funcbut==1){functrig=0;}
  funcbut=1;
  functrig=0;
  timediff=2000;
  }else{
  funcbut=0;
  latch=0;
  }
  
}

int SetPage(){
  if(menubut==1){
  page=page+1;
  }
  if(page>=3){
  page=0;
  }
  return page;
}

void LowBatteryHandler(){
  if(val<=3100){ //Low Battery
  oled.setContrast(0); //Reduce display contrast to avoid deep discharge and allow precharge. Can reduce power consumption to 0.25W
}else{oled.setContrast(contrastval);}

}
