#include "LightPoint.h"


LightPoint::LightPoint()
{
	active = true;
}


void LightPoint::setLowerLimit(HSVColor limit)
{
	lowerLimit = limit;
}


void LightPoint::setUpperLimit(HSVColor limit)
{
	upperLimit = limit;
}


HSVColor LightPoint::getLowerLimit()
{
	return lowerLimit;
}


HSVColor LightPoint::getUpperLimit()
{
	return upperLimit;
}


cv::Mat LightPoint::getShapeMatrix()
{
	return shapeMatrix;
}


coordi LightPoint::getPosition()
{
	return position;
}


/*NOT FINISHED*/
coordf LightPoint::getCenterOffset()
{
	coordf temp;
	return temp;
}