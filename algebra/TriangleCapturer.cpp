#include "TriangleCapturer.hpp"
#include <map>
#include <algorithm>
#include "dyn_mat.hpp"

struct FramePart
{
	vec2<float> pt;
	std::vector<dyn_mat<unsigned>::type> field;
};

struct Frame
{
	int idx;
	std::vector<FramePart> parts;
};

void TriangleCapture::init(const std::vector<dyn_mat<unsigned>::type>& aImageVec, //plamy
	const std::vector<vec2<float>::type> aPtVec, //wspolrzedne plamy
	const std::vector<int>& aFrameIndices) //ktora plama o ktorej klatki obrazu
{
	//wybierz te plamy ktore maja mozliwie zblizone powierzchnie
	//wybierz to gdzie sa conajmniej 3 plamy
	//wybierz to gdzie plamy sa mozliwie daleko od siebie

	/*std::vector<vec3<float>::type> coords;
	internal_work(aImageVec, aPtVec, coords);

	//chcemy znalezc parametry do normalizacji ukladu

	std::map<int, std::vector<vec3<float>::ptr> > frames;
	for (unsigned i = 0; i < aFrameIndices.size(); i++)
		frames[aFrameIndices[i]].push_back(&coords[i]);

	typename std::map<int, std::vector<vec3<float>::ptr> >::iterator it;
	for (it = frames.begin(); it != frames.end(); ++it) //przegladamy klatka po klatce
	{
		if (it->second.size() == 3) //jezeli w klatce sa 3 plamy
			for (unsigned i = 0; i < it->second.size(); ++i)
			{
				it->second[i]->z;
			}
	}*/

	//tymczasowo
	m_Distance = 8.0f;
}

//zwraca zbior wektorow nieznormalizowanych wpolrzednych 
void TriangleCapture::internal_work(const std::vector<dyn_mat<unsigned>::type>& aImageVec, //plamy
	const std::vector<vec2<float>::type> aPtVec, //wspolrzedne plamy
	std::vector<vec3<float>::type>& aResPtVec) //promien plamy
{
	//znajdz 4 plany (gora, dol prawo lewo)
	//w polowie odcinka okreslamy srodek okregu

	vec2<float> upper, lower, mid;
	unsigned width;
	unsigned height;

	aResPtVec.resize(aImageVec.size());

	for (unsigned k = 0; k < aImageVec.size(); k++) //dla kazdej plamy
	{
		width = aImageVec[k].ColCount();
		height = aImageVec[k].RowCount();

		upper = vec2<float>(0, 0);
		lower = vec2<float>(width, height);

		for (unsigned i = 0; i < width; ++i)
		{

			for (unsigned j = 0; j < height; ++j)
			{
				if (aImageVec[k](i,j) != 0) 
				{
					upper.x = std::max(upper.x, (float)i);
					upper.y = std::max(upper.y, (float)j);
					lower.x = std::min(lower.x, (float)i);
					lower.y = std::min(lower.y, (float)j);
				}
			}
		}

		mid = (upper + lower) / 2;
		aResPtVec[k].x = mid.x;
		aResPtVec[k].y = mid.y;
		aResPtVec[k].z = std::max((upper - mid).length(), (lower - mid).length());
	}

}

void TriangleCapture::work(const std::vector<dyn_mat<unsigned>::type>& aImageVec, //plamy
	const std::vector<vec2<float>::type> aPtVec, //wspolrzedne plamy
	std::vector<vec3<float>::type>& aResPtVec) //koordy 3d
{
	std::vector<vec3<float>::type> coords;
	internal_work(aImageVec, aPtVec, coords);

	for (unsigned i = 0; i < coords.size(); i++)
		coords[i].z = 1.0f - (coords[i].z / m_Distance);
}

