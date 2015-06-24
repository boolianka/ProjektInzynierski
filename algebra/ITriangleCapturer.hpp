#ifndef ITriangleCapturerH
#define	ITriangleCapturerH

#include <vector>
#include "vec2.hpp"
#include "vec3.hpp"
#include "dyn_mat.hpp"

class ITriangleCapturer
{
public:

	///calibrate ITriangleCapture
	///aPtVec - vector contains weighted means of tracked objects (per point in video frame)
	///aIndices -  vector contains indices of frames (per point in video frame)
	//virtual void init(const std::vector<dyn_vec<float>::type>& aPtVec, const std::vector<int>& aIndices)=0;
	virtual void init(const std::vector<dyn_mat<unsigned>::type>& aImageVec, const std::vector<vec2<float>::type> aPtVec,
		const std::vector<int>& aFrameIndices) = 0;

	///converts 2d triangle to 3d triangle using calibrated data
	///aPtVec - 2d triangle
	///aResultVec - 3d triangle
	//virtual void work(const std::vector<dyn_vec<float>::type>& aPtVec, std::vector<dyn_vec<float>::type>& aResPtVec) = 0;
	virtual void work(const std::vector<dyn_mat<unsigned>::type>& aImageVec, const std::vector<vec2<float>::type> aPtVec,
		std::vector<vec3<float>::type>& aResPtVec) = 0;

};

#endif	/* ITriangleCaptureH */