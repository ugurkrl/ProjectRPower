/*  -Project RP 5V-
 *  dispfuncs.h
 *  display functions
 *  ugurkrcl
 *  this code belongs to device "uPower 5400"
 *  Impedance Track(TM) integrated USB Power Bank Solution with 128x64 OLED Display
 */

/* Function for drawing images to OLED from array.Inside array 0 means clear pixel , 1 means draw pixel and 2 means skip that pixel
 *  I'll try to use progmem later. For now this will enough for drawing charging icon
 */
void drawuImage(int x,int y,int width,int height,byte arr[]){
  int loc = 0;
  for(int m=0; m < height ; m++){;
     for(int n=0; n < width ; n++){
      if(arr[loc]!=2){
           if(arr[loc]==0){ oled.setDrawColor(0);}
           if(arr[loc]==1){ oled.setDrawColor(1);}
           oled.drawPixel(x+n,y+m);
       }
      loc = loc +1;
    }
  }
  oled.setCursor(0,0);
}
  
