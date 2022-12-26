#pragma once

#include <Adafruit_GFX.h>

class Widget {

  public:
    Widget();
    void setCanvas(GFXcanvas16 *canvas) {
        this->canvas = canvas;
        setup();
    }
    void setDimentions(const int x, const int y, const int h, const int w) {
        this->x = x;
        this->y = y;
        this->h = h;
        this->w = w;
    }
    void clearWidget(void) { canvas->writeFillRect(x, y, w, h, 0); };
    virtual bool updateWidget(void) { return false; };

  protected:
    virtual void setup(void){};
    GFXcanvas16 *canvas = NULL;
    int update_interval = 1000;
    bool timeToUpdate(void);
    ulong last_update = -1;
    int x = -1;
    int y = -1;
    int w = -1;
    int h = -1;
    uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) {
        return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
    };
};
