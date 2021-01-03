/*  -Project RP 5V-
 *  mainpage.h
 *  main page function
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */
#include "dispfuncs.h"
static const unsigned char CHGBACK[] PROGMEM = {
   0x9e, 0x07, 0x92, 0x04, 0x92, 0x04, 0x92, 0x04, 0x92, 0x04, 0xf3, 0x0c,
   0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x01, 0x08, 0x03, 0x0c, 0x06, 0x06,
   0x0c, 0x03, 0x98, 0x01, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00,
   0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0x90, 0x00, 0xf0, 0x00 };
   
static const unsigned char CHG[] PROGMEM = {
   0x86, 0x01, 0x86, 0x01, 0x86, 0x01, 0x86, 0x01, 0x86, 0x01, 0xff, 0x03,
   0xff, 0x03, 0xff, 0x03, 0xff, 0x03, 0xfe, 0x01, 0xfc, 0x00, 0x78, 0x00,
   0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00,
   0x30, 0x00, 0x30, 0x00, 0x30, 0x00 };

int MainPage(){   //page1
    oled.clearBuffer();
    oled.setCursor(0,0);
    oled.setDrawColor(1);
    oled.setFont(u8g2_font_helvB10_tr);


    /* Draw Battery*/
    LSB = gg.read(0x2c); //read SoC
    MSB = gg.read(0x2d);
    val = word(MSB,LSB); 

    pointerx = map(val, 0, 100, 0, 114); //Map SoC Value to Box size  /*needs lim*/
    oled.drawFrame(0,2,118,42); //draw frame
    oled.drawBox(118,10,8,26); //draw frame
    oled.drawBox(2,4,pointerx,38); //Draw battery level

    /*Draw StateOfCharge */
    if(val>9 && val<100){pointery=51;}else if(val<10){pointery=55;}else if(val==100){pointery=47;} //Set text location
    oled.setCursor(pointery, 60); //58 for sh
    oled.print(val);
    oled.print("%");

    /* Draw Power */
    pointery=0; //Set text location
    oled.setCursor(pointery,60);//58 for sh
    LSB = gg.read(0x24); //read Power
    MSB = gg.read(0x25);
    val = word(MSB,LSB); 
    if(val>8){chg=1;} else {chg=0;} //Charging Status detection (CHG DSG bits have some issues on bq27541 , we have to detect charging status manually
    othval = word(MSB,LSB);
    if(val<0){othval=(65535-othval);} //Fix discharge power issue
    othval = (othval*0.001);
    oled.print(othval);
    oled.print("W");

    /* Draw Voltage*/
    pointery=88; //Set text location
    LSB = gg.read(8); //Read voltage
    MSB = gg.read(9);
    val = word(MSB,LSB); 
    int volt=val;
    oled.setCursor(pointery,60);//58 for sh
    othval = (val*0.001);
    oled.print(othval);
    oled.print("V");
    Serial.print(volt);
    Serial.print(" ");
    LSB = gg.read(0x14); //read Power
    MSB = gg.read(0x15);
    val = word(MSB,LSB); 
    Serial.println(val);
   
    /* Draw Charging Icon */
    if(chg==1){ //Charging detection
    oled.setBitmapMode(1); // Draw transparent icon
    oled.setDrawColor(0); 
    oled.drawXBMP(53,11,12,23,CHGBACK); //draw background
    oled.setDrawColor(1);
    oled.drawXBMP(54,12,10,21,CHG); //draw charging icon
    }
    
    oled.sendBuffer();
    return volt;
}
