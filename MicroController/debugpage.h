/*  -Project RP 5V-
 *  debugpage.h
 *  debug page function
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */

void DevPage(int type){
  bool dev=true;
  oled.setFont(u8g2_font_helvR10_tr);
  oled.setCursor(0,12);
  oled.print("BOOTMODE=DEV\n");
  oled.setCursor(0,26);
  oled.print("KEY TO OPEN UART");
  oled.sendBuffer();
  delay(2000);
  while(digitalRead(4)==0 && digitalRead(5)==0){}
  Serial.print("BOOTMODE=DEV\n");
  Serial.print("VERSION=");
  Serial.print(VER);
  
  //check if battery is unsealed
  LSB=gg.read(0);
  MSB=gg.read(1);
  if(bitRead(MSB, 5)==0){
    Serial.println("PACK IS UNSEALED");
  }else
  //try to unseal battery
  gg.write(0x0,0x36);
  delay(10);
  gg.write(0x1,0x72);
  delay(10);
  gg.write(0x0,0x04);
  delay(10);
  gg.write(0x1,0x14);
  delay(10);
  gg.write(0x0,0xFF);
  delay(10);
  gg.write(0x1,0xFF);
  delay(10);
  gg.write(0x0,0xFF);
  delay(10);
  gg.write(0x1,0xFF);
  //recheck battery
  if(bitRead(MSB, 5)==0){
    Serial.println("PACK IS UNSEALED");
  }
  int x,y,z;
  
  //printalldataflash
  while(dev==true){
    int data = millis();
    gg.write(0x61,0x00); 
    for(x=0;x<128;x++){ //128 subclass
     gg.write(0x3E,x);
       for(y=0;y<4;y++){ //4blocks ?
        gg.write(0x3F,y);
          for(z=0;z<32;z++){ //32byte
            MSB=gg.read(64+z);
            Serial.print("C:");
            Serial.print(x);
            Serial.print(" B:");
            Serial.print(y);
            Serial.print(" S:");
            Serial.print(z);
            Serial.print(" : ");
            Serial.print(MSB,HEX);
            Serial.print("\n");
          }
        }
        oled.drawFrame(0,32,128,12);
        oled.drawBox(0,33,x,11);
        oled.sendBuffer();
    } Serial.print("Took ");Serial.print((millis()-data)/1000);Serial.print(" secs");delay(999999);
   }
}
