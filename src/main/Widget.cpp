#pragma once

#include "Widget.h"

Widget::Widget() {}

bool Widget::timeToUpdate(void) {
    ulong now = millis();
    if (last_update == -1 || update_interval < now - last_update) {
        last_update = now;
        return true;
    }
    return false;
}
