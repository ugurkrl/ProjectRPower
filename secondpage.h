/*  -Project RP 5V-
 *  secondpage.h
 *  second page function
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */
void SecPage(){ //page2
  
  
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x12_tr);
  oled.setDrawColor(1);

  /*Read Remcap + FCC*/
  pointery=10; //Set text location
  pointerx=3; //Set text location
  oled.setCursor(pointerx,pointery);
  LSB = gg.read(0x10); //Read RM
  MSB = gg.read(0x11);
  val = word(MSB,LSB); 
  oled.print(val);
  oled.print("mAh");
  LSB = gg.read(0x12); //Read FCC
  MSB = gg.read(0x13);
  val = word(MSB,LSB);
  oled.print("/");
  oled.print(val);
  oled.print("mAh");

  /*Add Passed Charge*/
  LSB = gg.read(0x34); //Read dQ
  MSB = gg.read(0x35);
  val = word(MSB,LSB); 
  pointery=19; //Set text location
  pointerx=3; //Set text location
  oled.setCursor(pointerx,pointery);
  oled.print("dQ:");
  oled.print(val);
  oled.print("mAh");

  /*Read Temperature*/ //will verify by ev2300 , not sure about readings
  LSB = gg.read(0x06); //Read temperature
  MSB = gg.read(0x07);
  val = word(MSB,LSB); 
  othval = val;
  othval = (othval/10)-273;
  pointery=28; //Set text location (7 pixel text height + 2 pixel gap )
  pointerx=3; //Set text location
  oled.setCursor(pointerx,pointery);
  oled.print("Temp:");
  oled.print(othval,1);
  oled.print("C");

  /*TimeToEmpty (Time to full has been removed in G1 Firmware)*/
  LSB = gg.read(0x16); //Read TimeToEmpty
  MSB = gg.read(0x17);
  val = word(MSB,LSB); 
  pointery=37; //Set text location (7 pixel text height + 2 pixel gap )
  pointerx=3; //Set text location
  oled.setCursor(pointerx,pointery);
  oled.print("TTE:");
  oled.print(val);
  oled.print("Mins");

  
  
  oled.sendBuffer();

  
}
