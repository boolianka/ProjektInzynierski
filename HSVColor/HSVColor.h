#pragma once

#define H_MIN_RANGE		0
#define H_MAX_RANGE		197
#define S_MIN_RANGE		0
#define S_MAX_RANGE		255
#define V_MIN_RANGE		0
#define V_MAX_RANGE		255


class HSVColor
{
private:
	int h, s, v;

public:
	HSVColor();
	HSVColor(int _h, int _s, int _v);

	void setH(int _h);
	void setS(int _s);
	void setV(int _v);

	int getH();
	int getS();
	int getV();
};