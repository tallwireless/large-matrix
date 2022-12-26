#pragma once

#include <Adafruit_GFX.h>

void drawIcon(const uint8_t x, const uint8_t y, const uint16_t icon[], GFXcanvas16 *canvas) {
    uint8_t height = icon[0];
    uint8_t width = icon[1];
    uint8_t offset = 2;

    for(uint8_t y_offset = 0; y_offset<height; y_offset++) {
        for(uint8_t x_offset=0; x_offset<width; x_offset++) {
            canvas->drawPixel(x+x_offset,y+y_offset,icon[offset+y_offset*width+x_offset]);
        }
    }
}
