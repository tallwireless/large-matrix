#ifndef DISPLAY_H

#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_Protomatter.h>

class Display : public GFXcanvas16 {

    public:
        Display(const int x, const int y);
        void updateMatrix(void);
        uint32_t matrixFrameCount(void) { return matrix->getFrameCount();};

    private:
        Adafruit_Protomatter *matrix = NULL;
};


#endif
