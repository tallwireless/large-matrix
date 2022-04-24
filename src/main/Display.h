#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_Protomatter.h>
#include "Widget.h"

class Display {

  public:
    Display(const int x, const int y);
    void updateMatrix(void);
    void clearBuffer(void) {
      canvas->writeFillRect(0, 0, height, width, 0);
    };
    void clearSpace(const int, const int, const int, const int);
    uint32_t matrixFrameCount(void) {
      return matrix->getFrameCount();
    };
    void registerWidget(Widget*);
    void updateWidgets(void);
    void printText(int x, int y, String str) {
      canvas->setTextSize(1);
      canvas->setCursor(x, y);
      canvas->print(str);
      updateMatrix();
    }
  private:
    GFXcanvas16 *canvas = NULL;
    Adafruit_Protomatter *matrix = NULL;
    Widget** widgets;
    int widget_count = 0;
    int widget_size = 1;
    int width = -1;
    int height = -1;
   
};
