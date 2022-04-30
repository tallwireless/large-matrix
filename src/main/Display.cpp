#include "Display.h"

Display::Display(const int x, const int y) {
     uint8_t rgbPins[] = {7, 8, 9, 10, 11, 12};
     uint8_t addrPins[] = {17, 18, 19, 20};
     uint8_t clockPin = 14;
     uint8_t latchPin = 15;
     uint8_t oePin = 16;

     width = x;
     height = y;
     matrix = new Adafruit_Protomatter(256, 3, 1, rgbPins, 4, addrPins,
                                       clockPin, latchPin, oePin, false);
     ProtomatterStatus status = matrix->begin();
     Serial.print("Protomatter begin() status: ");
     Serial.println((int)status);
     if (status != PROTOMATTER_OK) {
          for (;;)
               ;
     }
     // Allocate the space to handle the widgets
     widgets = (Widget **)calloc(widget_size, sizeof(Widget *));
     canvas = new GFXcanvas16(x, y);
}

void Display::registerWidget(Widget *w) {

     if (widget_count == widget_size) {
          // Need to expand the array
          Serial.println("Increasing the size of the widget array");
          widget_size = widget_size * 2;
          Widget **new_array = (Widget **)calloc(widget_size, sizeof(Widget *));
          for (int i = 0; i < widget_count; i++) {
               new_array[i] = widgets[i];
          }
          Widget **t = widgets;
          widgets = new_array;
          free(t);
     }
     w->setDisplay(canvas);
     widgets[widget_count++] = w;
}

void Display::updateWidgets(void) {
     // Run through all of the widgets and update the screen
     for (int i = 0; i < widget_count; i++) {
          if (widgets[i] != NULL) {
               if (!widgets[i]->updateWidget()) {
                    Serial.printf("Removing widget from position %d\n", i);
                    widgets[i]->clearWidget();
                    delete (widgets[i]);
                    widgets[i] = NULL;
               }
          }
     }
     updateMatrix();
}

void Display::updateMatrix(void) {
     for (int w = 0; w < width; w++) {
          for (int h = 0; h < height / 2; h++) {
               // handle the upper side of the matrix
               matrix->drawPixel((width - w) - 1, (height / 2) - h - 1,
                                 canvas->getPixel(w, h));
               // handle the lower part of the canvas
               matrix->drawPixel(w + 128, h,
                                 canvas->getPixel(w, h + height / 2));
          }
     }
     // update the matrix
     matrix->show();
}
