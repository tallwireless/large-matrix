#pragma once

#include "Widget.h"

Widget::Widget( int x, int y, int h, int w) {
    this->x = x;
    this->y = y;
    this->h = h;
    this->w = w;
}

bool Widget::timeToUpdate(void) {
    ulong now = millis();
    if (last_update == -1 || update_interval < now - last_update ) {
        last_update = now;
        return true;
    }
    return false;
}
