#include "HSVColor.h"
#include <algorithm>


HSVColor::HSVColor()
{
	h = 0;
	s = 0;
	v = 0;
}


HSVColor::HSVColor(int _h, int _s, int _v)
{
	h = _h;
	s = _s;
	v = _v;
}


void HSVColor::setH(int _h)
{
	h = std::max( H_MIN_RANGE , std::min(_h, H_MAX_RANGE ));
}


void HSVColor::setS(int _s)
{
	s = std::max(S_MIN_RANGE, std::min(_s, S_MAX_RANGE));
}


void HSVColor::setV(int _v)
{
	v = std::max(V_MIN_RANGE, std::min(_v, V_MAX_RANGE));
}


int HSVColor::getH()
{
	return h;
}


int HSVColor::getS()
{
	return s;
}


int HSVColor::getV()
{
	return v;
}