#pragma once

#include "Widget.h"
#include <Adafruit_GFX.h>
#include <Adafruit_Protomatter.h>

class Display {

  public:
    Display(const int x, const int y, const int row, const int col);
    void updateMatrix(void);
    void clearBuffer(void) { canvas->writeFillRect(0, 0, width, height, 0); updateMatrix(); };
    void clearSpace(const int, const int, const int, const int);
    uint32_t matrixFrameCount(void) { return matrix->getFrameCount(); };
    void registerWidget(Widget *, const int row, const int col);
    void updateWidgets(void);
    void printText(int x, int y, String str, uint16_t color = -1) {
        if (color == -1) {
            color = color565(32, 32, 32);
        }
        canvas->setTextColor(color);
        canvas->setTextSize(1);
        canvas->setCursor(x, y);
        canvas->print(str);
        updateMatrix();
    }
    static uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) {
        return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
    };


  private:
    GFXcanvas16 *canvas = NULL;
    Adafruit_Protomatter *matrix = NULL;
    Widget ***widgets;
    int widget_count = 0;
    int width = -1;
    int height = -1;
    int rows = -1;
    int cols = -1;
};
