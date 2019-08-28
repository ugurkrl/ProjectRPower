/*  -Project RP 5V-
 *  mainpage.h
 *  main page function
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */
#include "dispfuncs.h"
int MainPage(){   //page1
    oled.clearBuffer();
    oled.setCursor(0,0);
    oled.setDrawColor(1);
    oled.setFont(u8g2_font_helvB10_tr);


    /* Draw Battery*/
    LSB = gg.read(0x2c); //read SoC
    MSB = gg.read(0x2d);
    val = word(MSB,LSB); 

    pointerx = map(val, 0, 100, 0, 114); //Map SoC Value to Box size
    oled.drawFrame(0,2,118,38); //draw frame
    oled.drawBox(118,10,8,21); //draw frame
    oled.drawBox(2,4,pointerx,34); //Draw battery level

    /*Draw StateOfCharge */
    if(val>9 && val<100){pointery=51;}else if(val<10){pointery=55;}else if(val==100){pointery=47;} //Set text location
    oled.setCursor(pointery, 58);
    oled.print(val);
    oled.print("%");

    /* Draw Power */
    pointery=0; //Set text location
    oled.setCursor(pointery,58);
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
    oled.setCursor(pointery,58);
    othval = (val*0.001);
    oled.print(othval);
    oled.print("V");

    /* Draw Charging Icon */
    if(chg==1){ //Charging detection
    drawuImage(54,10,10,21,chgicon);
    }
    oled.sendBuffer();
    return volt;
}
