#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <map>
#include <string>
#include "../LightPoint/LightPoint.h"


#define WORLD_NO_FLIP -2
#define WORLD_VERTICAL_FLIP 0
#define WORLD_HORIZONTAL_FLIP 1
#define WORLD_VERTICAL_and_VERTICAL_FLIP -1


class World
{
private:
	cv::VideoCapture videoCapture;
	cv::Mat capturedMatBGR;
	cv::Mat capturedMatHSV;
	cv::Mat thresholdMat;
	cv::Mat outputMat;
	cv::Size sceneSize;
	std::map <std::string, LightPoint*> lightPoints;
	int skippedFrames;
	int flip;
	bool captureResult;
	bool displayDebugWindows;

public:
	World();
	World(int deviceNum);
	bool step();
	bool init();
	bool addLighPoint(LightPoint* lp, std::string tag);
	void setFrameSkip(int fs);
	void setFlip(int f);
	coordi getWorldSize();
	
	void enableDebugWindows(bool value);
};