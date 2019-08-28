/*  -Project RP 5V-
 *  contrastpage.h
 *  contrast setting page function
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */
void ContPage(){
  oled.setFont(u8g2_font_helvR10_tr);
  oled.clearBuffer();
  oled.setCursor(0,24);
  oled.print("Page3");
  oled.sendBuffer();
}
