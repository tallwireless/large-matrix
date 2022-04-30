#pragma once

#include "Widget.h"
#include <Timezone_Generic.h>

class TimeWidget : public Widget {

   public:
     TimeWidget(int x, int y, int h, int w, Timezone *tz, uint16_t color)
         : Widget(x, y, h, w) {
          this->tz = tz;
          this->color = color;
     };
     bool updateWidget(void) {
          if (!timeToUpdate()) {
               return true;
          }
          // Clear the space before writing new stuffs
          canvas->writeFillRect(x, y, w, h, 0);

          int16_t x_1, y_1;
          uint16_t t_h, t_w;
          int16_t pos_x = x, pos_y = y;
          TimeChangeRule *tcr;
          time_t local = tz->toLocal(now(), &tcr);

          String t_buff = getTime(local);
          canvas->setTextColor(color);
          canvas->setTextSize(2);
          canvas->getTextBounds(t_buff, pos_x, pos_y, &x_1, &y_1, &t_w, &t_h);
          canvas->setCursor(pos_x + ((64 - t_w) / 2), pos_y);
          pos_y = pos_y + t_h - 2;
          canvas->print(t_buff);
          t_buff = tcr->abbrev;
          canvas->setTextColor(color565(32, 32, 32));
          canvas->setTextSize(1);
          canvas->getTextBounds(t_buff, 0, 0, &x_1, &y_1, &t_w, &t_h);
          canvas->setCursor(pos_x + ((64 - t_w) / 2), pos_y);
          canvas->print(t_buff);
          return true;
     };

   private:
     Timezone *tz;
     uint16_t color;
     String getTime(time_t t) {
          char buf[5];
          sprintf(buf, "%.2d:%.2d", hour(t), minute(t));
          String rV;
          for (int i = 0; i < 5; i++) {
               rV += buf[i];
          }
          return rV;
     };
};
