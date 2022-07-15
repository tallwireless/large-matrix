#pragma once

#include "Widget.h"
#include <Adafruit_GFX.h>
#include <Adafruit_Protomatter.h>

class Display {

  public:
    Display(const int x, const int y, const int row, const int col);
    void updateMatrix(void);
    void clearBuffer(void) { canvas->writeFillRect(0, 0, height, width, 0); };
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

    void drawIcon(const uint8_t x, const uint8_t y, const uint16_t icon[]) {
        uint8_t height = icon[0];
        uint8_t width = icon[1];
        uint8_t offset = 2;

        for(uint8_t y_offset = 0; y_offset<height; y_offset++) {
            for(uint8_t x_offset=0; x_offset<width; x_offset++) {
                canvas->drawPixel(x+x_offset,y+y_offset,icon[offset+y_offset*width+x_offset]);
            }
        }
        this->updateMatrix();
    }

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
