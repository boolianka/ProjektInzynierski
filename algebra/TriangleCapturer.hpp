#ifndef TriangleCapturerH
#define TriangleCapturerH

#include "ITriangleCapturer.hpp"

class TriangleCapture : public ITriangleCapturer
{
//szuka plam o zblizonych rozmiarach, mozliwie daleko oddalonych od siebie i normalizuje uklad wg tak obranego maksimum
public:
	virtual void init(const std::vector<dyn_mat<unsigned>::type>& aImageVec, const std::vector<vec2<float>::type> aPtVec,
		const std::vector<int>& aFrameIndices);

	virtual void work(const std::vector<dyn_mat<unsigned>::type>& aImageVec, const std::vector<vec2<float>::type> aPtVec,
		std::vector<vec3<float>::type>& aResPtVec);

private:
	void internal_work(const std::vector<dyn_mat<unsigned>::type>& aImageVec, //plamy
		const std::vector<vec2<float>::type> aPtVec, //wspolrzedne plamy
		std::vector<vec3<float>::type>& aResPtVec); //promien plamy

	float m_Distance;

};

#endif