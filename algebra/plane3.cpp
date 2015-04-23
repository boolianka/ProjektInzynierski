#include "plane3.hpp"

Plane3::Plane3(const vec3<safe_float>& aNormal, const safe_float& aDist):
	m_Dist(aDist), m_Normal(aNormal)
{
}

Plane3::Plane3(const vec3<safe_float>& aPt, const vec3<safe_float>& aNormal):
	m_Normal(aNormal)
{
	m_Dist = -(aNormal.dot(aPt));
}

Plane3::Plane3(const vec3<safe_float>& aPt1, const vec3<safe_float>& aPt2, const vec3<safe_float>& aPt3)
{
	(m_Normal = cross(aPt2-aPt1,aPt3-aPt1)).normalize();
	m_Dist = m_Normal.dot(aPt1);
}

void Plane3::getProjectionMatrix(mat3x4<safe_float>& aMtx) const
{
	
}

safe_float Plane3::getDistance() const { return m_Dist; }

vec3<safe_float> Plane3::getNormal() const { return m_Normal; }
