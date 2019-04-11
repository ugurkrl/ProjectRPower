/*  -Project RP 5V-
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */
#include <HDQ.h>
#include <U8g2lib.h>
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
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0); //Define SH1106 OLED display on framebuffer mode
HDQ gg(4); //Battery is connected on D4 Pin

void setup() {
  oled.begin();
  pinMode(14,INPUT);
  pinMode(15,INPUT);
  //add Micro Splash logo
  //Add Impedance Track logo
  Serial.begin(9600);

}

void loop() {
  /* Should refresh every 2 sec while scanning any key action without delays */ 
  t1=millis();
  timediff=t1-t0;
  ScanButton();
  page=SetPage();
  if(timediff >= 2000){
    if(page==0){
      MainPage();
    }
    if(page==1){
      ExtPage();
    }
    if(page==2){
      ContPage();
    }
    t0=t1; //sync time variables
  }
   Serial.println(menubut);
   Serial.print(funcbut);
   Serial.print(page);

  
}


void MainPage(){   //page0
    oled.clearBuffer();
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
    oled.setCursor(pointery,58);
    othval = (val*0.001);
    oled.print(othval);
    oled.print("V");
    LowBatteryHandler();
    

    /* Draw Charging Icon */
    if(chg==1){ //Charging detection
    oled.setDrawColor(0); //Clean Charging Icon Area
    oled.drawBox(54,10,10,21);
    oled.setDrawColor(1);
//  oled.drawLine(x0, y0, x1, y1);
    oled.drawLine(58, 16, 58, 29);
    oled.drawLine(59, 16, 59, 29); 
    oled.drawLine(58, 16, 55, 16);
    oled.drawLine(59, 16, 62, 16);
    oled.drawLine(58, 17, 55, 17);
    oled.drawLine(59, 17, 62, 17);
    oled.drawLine(55, 18, 62, 18);
    oled.drawLine(55, 16, 62, 16);
    oled.drawLine(55, 15, 62, 15);
    oled.drawLine(56, 19, 61, 19);
    oled.drawLine(57, 20, 60, 20);
    oled.drawLine(56, 17, 56, 11);
    oled.drawLine(61, 17, 61, 11); 
    
    
    }
    
    
    oled.sendBuffer();
}

void ExtPage(){
  oled.setFont(u8g2_font_helvB10_tr);
  oled.clearBuffer();
  oled.setCursor(0,24);
  oled.print("Page2");
  oled.sendBuffer();
}

void ContPage(){
  oled.setFont(u8g2_font_helvB10_tr);
  oled.clearBuffer();
  oled.setCursor(0,24);
  oled.print("Page3");
  oled.sendBuffer();
}

void ScanButton(){
  if(digitalRead(14)==1){ //read menu button
  menutrig=menutrig+1;
  }else{
  menutrig=0;
  }
  
  if(digitalRead(15)==1){ //read function button 
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
  if(othval<=3.1){ //Low Battery
  oled.setContrast(0); //Reduce display contrast to avoid deep discharge and allow precharge. Can reduce power consumption to 0.25W
}else{oled.setContrast(contrastval);}

}
  
