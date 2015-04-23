#ifndef Plane3H
#define Plane3H

typedef float safe_float;//tak zeby wyszczeglolnic, w miare czego zmienic 

template <class T> class vec3 : public vec<T,3> {};
template <class T> class mat2x2 : public mat<T,2,2> {};
template <class T> class mat3x3 : public mat<T,3,3> {};
template <class T> class mat4x4 : public mat<T,4,4> {};
template <class T> class mat3x4 : public mat<T,3,4> {};


class Plane3
{
public:
	Plane3(const vec3<safe_float>& aNormal, const safe_float& aDist);
	Plane3(const vec3<safe_float>& aPt, const vec3<safe_float>& aNormal);
	Plane3(const vec3<safe_float>& aPt1, const vec3<safe_float>& aPt2, const vec3<safe_float>& aPt3);
	
	void getProjectionMatrix(mat3x4<safe_float>& aMtx) const;
	safe_float getDistance() const;
	vec3<safe_float> getNormal() const;

private:
	vec3<safe_float> m_Normal;
	safe_float m_Dist;
	
};

#endif