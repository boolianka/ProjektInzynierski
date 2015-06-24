#ifndef Vec3H
#define	Vec3H

#include "vec2.hpp"

template <class T> class vec3 : public vec2<T>
{
public:
    typedef vec3 type;
	typedef typename vec2::item_type item_type;
    typedef type& ref;
    typedef type* ptr;
    typedef const type cref;
    typedef type * const cptr;
    	
	///default constructor - does nothing
    vec3() {}
	
	///copy constructor
	vec3(const vec3& aCopy) :
		x(aCopy.x), y(aCopy.y), z(aCopy.z) {}
    
	///init x,y,z using base constructor
	vec3(const vec2& aVec, const T& aZ) :
		vec2(aVec), z(aZ) {}
		
	///init x,y,z using base constructor
	vec3(const T& aX, const T& aY, const T& aZ) :
		vec2(aX, aY), z(aZ) {}
		
	///init aLength fields with aValue 
    vec3(const item_type& aValue) :
		vec2(aValue), z(aValue) {}
    
	///returns dot product of this and aOther
    inline item_type dot(cref aOther) const { return x*aOther.x + y*aOther.y + z*aOther.z; }
    
	///returns square length of this
    inline item_type length_sq() const { return x*x + y*y + z*z; }
    
	///returns length of this
    inline item_type length() const { return (item_type) sqrt(length_sq()); }
        
	///returns distance between this and aOther
    inline item_type dist(cref aOther) const 
    { return (*this-aOther).length(); }
    
	///returns square distance between this and aOther
    inline item_type dist_sq(cref aOther) const 
    { return (*this-aOther).length_sq(); }
    
	///attempts to normalize vector (length will be 1, otherwise was/is 0) 
    inline void normalize() 
    {
        item_type len = length_sq();
        if(IS_NEAR_EQUAL(item_type::ONE, temp, item_type::EPSILON_SQ))
            return;
        len = (item_type) sqrt(len);
		x /= len;
		y /= len;
		z /= len;
    }
	
    ///vector by vector addition 
    inline ref operator +=(cref aOther) 
    {
		x += aOther.x;
		y += aOther.y;
		z += aOther.z;
		return *this;
	}
    
    ///vector by vector substraction
    inline ref operator -=(cref aOther) 
    {
		x -= aOther.x;
		y -= aOther.y;
		z -= aOther.z;
		return *this;
	}
    
    ///vector by scalar multiplication
    inline ref operator *=(const item_type& aOther) 
    {
		x *= aOther;
		y *= aOther;
		z *= aOther;
		return *this;
	}
    
    ///vector by scalar division
    inline ref operator /=(const item_type& aOther) 
    {
		x /= aOther;
		y /= aOther;
		z /= aOther;
		return *this;
	}
	
	///returns dot product of this and aOther vector
    inline item_type operator*(cref aOther) const
    {
		return dot(aOther);
	}
    
    ///summation with aOther vector
	///returns new vector 
    inline type operator+(cref aOther) const
    {
		return type(x+aOther.x, y+aOther.y, z+aOther.z);
	}
    
    ///substraction by aOther vector
	///returns new vector 
    inline type operator-(cref aOther) const
    {
		return type(x-aOther.x, y-aOther.y, z-aOther.z);
	}
    
    ///vector by scalar multiplication
	///returns new vector 
    inline type operator*(const item_type& aOther) const
    {
		return type(x*aOther, y*aOther, z*aOther);
	}
    
    ///division by scalar
	///returns new vector 
    inline type operator/(const item_type& aOther) const 
    {
		return type(x/aOther, y/aOther, z/aOther);
	}
    
    ///vector negation
	///returns new vector 
    inline type operator-()
    {
		return type(-x, -y, -z);
    }
	
    ///vector assignation
    inline ref operator=(cref aOther)
    {
		x = aOther.x;
		y = aOther.y;
		z = aOther.z;
    }
	
	inline type cross(cref other) const 
	{
		return type(y*other.z - z*other.y,
			z*other.x - x*other.z,
			x*other.y - y*other.x);
	}

	inline friend type operator *(const T& lhs, cref& rhs)
	{
		return type(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
	}
	
	inline bool operator ==(cref aOther) const 
	{
		return x==aOther.x && y==aOther.y && z==aOther.z;
	}
	
	inline bool operator !=(cref aOther) const 
	{
		return x!=aOther.x || y!=aOther.y || z!=aOther.z;
	}
	
	inline bool operator >(cref aOther) const 
	{
		return x>Other.x && y>aOther.y && z>aOther.z;
	}
	
	inline bool operator <(cref aOther) const 
	{
		return x<aOther.x && y<aOther.y && z<aOther.z;
	}
	
	inline bool operator >=(cref aOther) const 
	{
		return x>=aOther.x && y>=aOther.y && z>=aOther.z;
	}
	
	inline bool operator <=(cref aOther) const 
	{
		return x<=aOther.x && y<=aOther.y && z<=aOther.z;
	}
	
public:
	T z;
};


#endif	/* Vec3H */