#include "Sunset.h"
#include "Shore.h"

#define MINIMUM_BATTERY_LEVEL 3.65f
#define MAXIMUM_BATTERY_LEVEL 4.1f
#define SUN_DIAMETER 50
#define SUN_RADIUS SUN_DIAMETER / 2
#define BITMAP_HEIGHT 48
#define BITMAP_TOP 200 - BITMAP_HEIGHT

Sunset::Sunset() {} //constructor

void Sunset::drawWatchFace() {
    display.fillScreen(GxEPD_BLACK);
	display.setTextColor(GxEPD_WHITE);

	//Get a number between 0 and 1 where 0 <= MINIMUM_BATTERY_LEVEL and 1 >= MAXIMUM_BATTERY_LEVEL
	auto batteryLevel = InverseLerp(MINIMUM_BATTERY_LEVEL, MAXIMUM_BATTERY_LEVEL, getBatteryVoltage()); 

	// Use the normalized battery level to move the sun up and down
	auto sunHeight = (BITMAP_TOP + SUN_RADIUS) - (batteryLevel * SUN_DIAMETER); 
	display.fillCircle(100, sunHeight, SUN_RADIUS, GxEPD_WHITE);

	display.drawBitmap(0, BITMAP_TOP, epd_bitmap_shoreshore, 200, BITMAP_HEIGHT, GxEPD_WHITE, GxEPD_BLACK);

	display.setFont(&DSEG7_Classic_Bold_53);
	display.setCursor(7,70);


	auto displayHour = currentTime.Hour;
	if (displayHour < 10) {
		display.print("0");
	}
	display.print(displayHour);
	display.print(":");
	if (currentTime.Minute < 10) {
		display.print("0");
	}
	display.println(currentTime.Minute);
}

float Sunset::InverseLerp(float min, float max, float value)
{
	return Clamp(0.0f, 1.0f, (value-min)/(max-min));
}

float Sunset::Clamp(float min, float max, float value)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}