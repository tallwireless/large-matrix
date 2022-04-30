#pragma once

#include "Widget.h"

class ScrollingTextWidget : public Widget {

    public:
        ScrollingTextWidget(int x, int y, int h, int w, String text, uint16_t color, int size = 2 ): Widget(x, y, h, w) {
            this->color = color;
            this->text = text;
            this->size = size;

            this->h = h;
            this->w = w;
            update_interval = 25;

        };


        bool updateWidget(void) {
            if ( !timeToUpdate() ) {
                return true;
            }
            // Clear the space
            clearWidget();

            canvas->setTextWrap(false);
            canvas->setTextColor(color);
            canvas->setTextSize(size);
            canvas->setCursor(text_x--, text_y);
            canvas->print(text);

            if (text_x < text_width * -1 ) {
                return false;
            }
            return true;

        };

    private:

        void setup (void) {
            canvas->setTextWrap(false);
            canvas->setTextColor(color);
            canvas->setTextSize(size);

            // Grab the size of the text for scrolling purposes;
            int16_t x_1, y_1;
            uint16_t t_h, t_w;
            int16_t pos_x = x, pos_y = y;
            canvas->getTextBounds(text, pos_x, pos_y, &x_1, &y_1, &text_width, &text_height);

            // Where are we going to put the text centered on the y
            text_y = y + (h-text_height)/2;
            // start off screen and scroll across
            text_x = 128;
            Serial.print("Text height: "); Serial.println(text_height);
            Serial.print("Text width: "); Serial.println(text_width);
            Serial.print("Text h: "); Serial.println(h);
            Serial.print("Text w: "); Serial.println(w);
            Serial.printf("Starting Point: (%d,%d)\n",text_x,text_y);
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
