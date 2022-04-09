#include "Display.h"

Display::Display(const int x, const int y) : GFXcanvas16(x,y) {
        uint8_t rgbPins[]  = {7, 8, 9, 10, 11, 12};
        uint8_t addrPins[] = {17, 18, 19, 20};
        uint8_t clockPin   = 14;
        uint8_t latchPin   = 15;
        uint8_t oePin      = 16;


      matrix = new Adafruit_Protomatter( 256, 3, 1, rgbPins, 4, addrPins, clockPin, latchPin, oePin, false);
      ProtomatterStatus status = matrix->begin();
    Serial.print("Protomatter begin() status: ");
    Serial.println((int)status);
    if(status != PROTOMATTER_OK) {
    for(;;);
    }

}

void Display::clearBuffer(void){

    writeFillRect(0,0,width(),height(),0);
}
void Display::updateMatrix(void){
    for( int w = 0; w < width(); w++) {
        for( int h = 0; h < height()/2; h++ ) {
            // handle the upper side of the matrix
            matrix->drawPixel((width()-w)-1, (height()/2)-h-1, getPixel(w,h));
            // handle the lower part of the canvas
            matrix->drawPixel(w+128,h,getPixel(w,h+height()/2));
        }
    }
    //update the matrix
    matrix->show();
}
