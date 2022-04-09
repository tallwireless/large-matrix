//#include "Adafruit_Protomatter.h"
//#include "Adafruit_GFX.h"
//#include "WiFiNINA.h"
#include "Display.h"

uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

#define MATRIX_WIDTH  128
#define MATRIX_HEIGHT 64

// WiFiClient espClient;
// int wifiStatus = -1;

Display *canvas = NULL;

void setup(void) {
  Serial.begin(9600) ;
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(5000);
  canvas = new Display(128, 64);

  Serial.println("STARTING....");


  Serial.println("Write something?");
 canvas->setTextSize(3);
  canvas->setCursor(0,24);
  canvas->print("TESTING");
  Serial.println("update matrix");

  canvas->updateMatrix();
  Serial.println("updated matrix");
}
uint16_t colors[] = { color565(,64,32), color565(64,0,32), color565(32,32,32) };
int count = 0;
void loop(void) {
   digitalWrite(13, count++ % 2);

  Serial.print("Refresh FPS = ~");
  Serial.println(canvas->matrixFrameCount());
  canvas->setTextColor(colors[count++%3]);
  canvas->setTextSize(3);
  canvas->setCursor(0,24);
  canvas->print("TESTING");
  canvas->updateMatrix();

  delay(1000);
}
