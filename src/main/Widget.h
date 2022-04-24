#pragma once

#include <Adafruit_GFX.h>

class Widget {

    public:
        Widget( int x, int y, int h, int w);
        void setDisplay(GFXcanvas16* canvas) { this->canvas = canvas; }
       virtual void updateWidget(void) {};
    protected:
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
