#include "world.h"
#include <iostream>


World::World() : videoCapture(0)
{
	skippedFrames = 0;
	flip = WORLD_NO_FLIP;
	displayDebugWindows = false;
}



World::World(int deviceNum) : videoCapture(deviceNum)
{
	skippedFrames = 0;
	flip = WORLD_NO_FLIP;
	displayDebugWindows = false;
}



bool World::init()
{
	if (!videoCapture.isOpened())
	{
		std::cerr << "Cannot open video capture\n";
		return false;
	}

	while (!videoCapture.read(capturedMatBGR)){}

	sceneSize = capturedMatBGR.size();
}



bool World::step()
{
	/*SKIPPING FRAMES*/
	for (int a(0); a < skippedFrames; a++)
	{
		videoCapture.grab();
	}


	/*GETTING IMAGE FROM CAMERA*/
	captureResult = videoCapture.read(capturedMatBGR);


	if (!captureResult)
	{
		std::cerr << "Cannot read an image from camera\n";
		return false;
	}


	/*FLIPPING IMAGE IF NEEDED*/
	if (flip != WORLD_NO_FLIP)
	{
		cv::flip(capturedMatBGR, capturedMatBGR, flip);
	}

	/*CONVERSION TO HSV*/
	cvtColor(capturedMatBGR, capturedMatHSV, cv::COLOR_BGR2HSV);

	/*LOOP BY LIGHTPOINTS*/
	for (std::map<std::string, LightPoint*>::iterator it = lightPoints.begin(); it != lightPoints.end(); ++it)
	{
		/*THRESHOLD IMAGE*/
		cv::inRange(
			capturedMatHSV, 
			cv::Scalar( it->second->lowerLimit.getH(), it->second->lowerLimit.getS(), it->second->lowerLimit.getV() ),
			cv::Scalar( it->second->upperLimit.getH(), it->second->upperLimit.getS(), it->second->upperLimit.getV() ),
			thresholdMat );

		/*MORPHOLOGICAL OPENNING REMOVES SMALL OBJECTS IN BACKGROUND*/
		cv::erode(thresholdMat, thresholdMat, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::dilate(thresholdMat, thresholdMat, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

		/*MORPHOLOGICAL CLOSING REMOVES SMALL HOLES FROM FOREGROUND*/
		cv::dilate(thresholdMat, thresholdMat, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::erode(thresholdMat, thresholdMat, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

		//Calculate the moments of the thresholded image
		cv::Moments moments = cv::moments(thresholdMat);

		double dM01 = moments.m01;
		double dM10 = moments.m10;
		double dArea = moments.m00;

		
		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if (dArea > 10000)
		{
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;

			it->second->position.x = posX;
			it->second->position.y = posY;
		}
		

		if (displayDebugWindows)
		{
			cv::imshow("Thresholded Image", thresholdMat);
			cv::imshow("Original", capturedMatBGR); //show the original image
			cv::waitKey(1); //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		}


	}

	
}



bool World::addLighPoint(LightPoint* lp, std::string tag)
{
	std::pair<std::string, LightPoint*> item(tag, lp);
	std::pair<std::map<std::string, LightPoint*>::iterator, bool> result;
	result = lightPoints.insert(item);
	if (result.second == false)
	{
		std::cerr << "Element " + tag + " already exists.\n";
	}

	return result.second;
}



void World::enableDebugWindows(bool value)
{
	displayDebugWindows = value;
}



void World::setFlip(int f)
{
	if (f == WORLD_NO_FLIP || f == WORLD_HORIZONTAL_FLIP || f == WORLD_VERTICAL_FLIP || f == WORLD_VERTICAL_and_VERTICAL_FLIP)
	{
		flip = f;
	}
	else
	{
		std::cerr << "Wrong parameter in function setFlip.\n";
	}
}


void World::setFrameSkip(int fs)
{
	if (fs >= 0)
	{
		skippedFrames = fs;
	}
	else
	{
		std::cerr << "Wrong parameter in function setFrameSkip.\n";
	}
}