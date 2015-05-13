#pragma once
#include "../HSVColor/HSVColor.h"
#include "opencv/cv.h"
#include <string>


struct coordi{
	int x;
	int y;
};


struct coordf{
	double x;
	double y;
};


class LightPoint
{
private:
	HSVColor lowerLimit;
	HSVColor upperLimit;
	cv::Mat shapeMatrix;
	coordi position;
	coordf centerOffset;
	bool active;

	friend class World;

public:
	LightPoint();

	void setLowerLimit(HSVColor limit);
	void setUpperLimit(HSVColor limit);
	HSVColor getLowerLimit();
	HSVColor getUpperLimit();
	cv::Mat getShapeMatrix();
	coordi getPosition();
	coordf getCenterOffset();
};