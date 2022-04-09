#include "Adafruit_Protomatter.h"
#include "Adafruit_GFX.h"
#include "WiFiNINA.h"

uint8_t rgbPins[]  = {7, 8, 9, 10, 11, 12};
uint8_t addrPins[] = {17, 18, 19, 20};
uint8_t clockPin   = 14;
uint8_t latchPin   = 15;
uint8_t oePin      = 16;

Adafruit_Protomatter matrix(
  256, 4, 1, rgbPins, 4, addrPins, clockPin, latchPin, oePin, false);

#define MATRIX_WIDTH  128
#define MATRIX_HEIGHT 64

GFXcanvas16 canvas(128,64);

WiFiClient espClient;
int wifiStatus = -1;

void wifiConnect(){
  while (wifiStatus != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println("LinuxCats");
    Serial.print("STARTING STATUS: ");
    Serial.println(wifiStatus);
    wifiStatus = WiFi.begin("LinuxCats", "sophieisthcoolest");
    Serial.print(" ENDING STATUS: ");
    Serial.println(wifiStatus);
    delay(10000);
  }
}

void updateMatrix(void){
    for( int w = 0; w < MATRIX_WIDTH; w++) {
        for( int h = 0; h < MATRIX_HEIGHT/2; h++ ) {

            matrix.drawPixel((MATRIX_WIDTH-w)-1, (MATRIX_HEIGHT/2)-h-1, canvas.getPixel(w,h));
            // handle the lower part of the canvas
            matrix.drawPixel(w+128,h,canvas.getPixel(w,h+MATRIX_HEIGHT/2));
        }
    }
    matrix.show();
}

void setup(void) {
  Serial.begin(9600);
  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    for(;;);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }


  canvas.setTextSize(3);
  canvas.setCursor(0,24);
  canvas.print("TESTING");

  updateMatrix();
}
uint16_t colors[] = { matrix.color565(32,64,32), matrix.color565(64,0,32), matrix.color565(32,32,32) };
int count = 0;
void loop(void) {
  Serial.print("Refresh FPS = ~");
  Serial.println(matrix.getFrameCount());
  canvas.setTextColor(colors[count++%3]);
  canvas.setTextSize(3);
  canvas.setCursor(0,24);
  canvas.print("TESTING");
  updateMatrix();

  delay(1000);
}
