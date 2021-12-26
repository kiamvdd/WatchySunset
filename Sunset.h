#include "Watchy.h"

class Sunset : public Watchy {
public:
    Sunset();
    void drawWatchFace();
	float InverseLerp(float min, float max, float value);
	float Clamp(float min, float max, float value);
};