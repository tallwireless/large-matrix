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

int16_t x = 0;
int16_t y = 0;

int16_t x_1 = 0;
int16_t y_1 = 0;

uint16_t t_w = 0;
uint16_t t_h = 0;

uint16_t colors[] = { color565(0,64,32), color565(64,0,32), color565(32,32,32) };


void setup(void) {
  Serial.begin(9600) ;
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(5000);
  canvas = new Display(128, 64);
  Serial.println("STARTING....");
  Serial.println("Write something?");
  canvas->setTextSize(2);
  canvas->getTextBounds("00:00",x,y,&x_1, &y_1, &t_w, &t_h);
  canvas->setCursor(x+((64-t_w)/2),y);
  y = y + t_h-2;
  canvas->print("00:00");
  canvas->setTextSize(1);
  canvas->getTextBounds("EST",x,y,&x_1, &y_1, &t_w, &t_h);
  canvas->setCursor(x+((64-t_w)/2),y);
  y = y + t_h-1;
  canvas->print("EST");
  canvas->setTextSize(2);
  canvas->getTextBounds("00:00",x,y,&x_1, &y_1, &t_w, &t_h);
  canvas->setCursor(x+((64-t_w)/2),y);
  y = y + t_h-2;
  canvas->print("00:00");
  canvas->setTextSize(1);
  canvas->getTextBounds("CST",x,y,&x_1, &y_1, &t_w, &t_h);
  canvas->setCursor(x+((64-t_w)/2),y);
  y = y + t_h-1;
  canvas->print("CST");
  canvas->setTextSize(2);
  canvas->getTextBounds("00:00",x,y,&x_1, &y_1, &t_w, &t_h);
  canvas->setCursor(x+((64-t_w)/2),y);
  y = y + t_h-2;
  canvas->print("00:00");
  canvas->setTextSize(1);
  canvas->getTextBounds("UTC",x,y,&x_1, &y_1, &t_w, &t_h);
  canvas->setCursor(x+((64-t_w)/2),y);
  y = y + t_h;
  canvas->print("UTC");
  canvas->setTextSize(2);
  Serial.println("update matrix");

  canvas->updateMatrix();
  Serial.println("updated matrix");
}

int count = 0;
int x_dir = 1;
int y_dir = 1;
void loop(void) {
  digitalWrite(13, count++ % 2);
  Serial.print("Refresh FPS = ~");
  Serial.println(canvas->matrixFrameCount());
  delay(1000);
}
