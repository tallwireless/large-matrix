#pragma once

#include "Widget.h"
//#include "fonts/FreeMono24pt7b.h"
#include "fonts/FreeMonoBold24pt7b.h"
class ScrollingTextWidget : public Widget {

   public:
     ScrollingTextWidget(int x, int y, int h, int w, String text,
                         uint16_t color, int size = 1)
         : Widget(x, y, h, w) {
          this->color = color;
          this->text = text;
          this->size = size;

          this->h = h;
          this->w = w;
          update_interval = 25;
     };

     bool updateWidget(void) {
          if (!timeToUpdate()) {
               return true;
          }
          // Clear the space
          clearWidget();

          textSetup();

          Serial.printf("Printing at: (%d,%d)\n", text_x, text_y);
          canvas->setCursor(text_x--, text_y);
          canvas->print(text);
          textCleanup();

          if (text_x < text_width * -1) {
               return false;
          }
          return true;
     };

   private:
     void textSetup() {
          canvas->setTextWrap(false);
          canvas->setFont(&FreeMonoBold24pt7b);
          canvas->setTextColor(color);
          canvas->setTextSize(size);
     }
     void textCleanup() { canvas->setFont(); }
     void setup(void) {
          // Grab the size of the text for scrolling purposes;
          int16_t x_1, y_1;
          uint16_t t_h, t_w;
          int16_t pos_x = x, pos_y = y;
          textSetup();
          canvas->getTextBounds(text, pos_x, pos_y, &x_1, &y_1, &text_width,
                                &text_height);
          // Where are we going to put the text centered on the y
          text_y = y + ((h - text_height) / 2) + (y - y_1);
          // start off screen and scroll across
          text_x = 128;
          textCleanup();
          Serial.print("Text height: ");
          Serial.println(text_height);
          Serial.print("Text width: ");
          Serial.println(text_width);
          Serial.print("Text h: ");
          Serial.println(h);
          Serial.print("Text w: ");
          Serial.println(w);
          Serial.printf("Starting Point: (%d,%d)\n", text_x, text_y);
          Serial.printf("other Point: (%d,%d)\n", x_1, y_1);
     };
     uint16_t color;
     int size = -1;
     String text;
     uint16_t text_height = -1;
     uint16_t text_width = -1;
     int16_t text_y = -1;
     int16_t text_x = -1;
     uint16_t h;
     uint16_t w;
};
