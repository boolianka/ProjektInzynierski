#ifndef Vec4H
#define	Vec4H

template <class T> class vec4 : virtual protected vec3
{
public:
    typedef vec4 type;
    typedef T item_type;
    typedef type& ref;
    typedef type* ptr;
    typedef const type cref;
    typedef type * const cptr;
    	
	///default constructor - does nothing
    vec4() {}
	
	///copy constructor
	vec4(const vec4& aCopy):
		x(aCopy.x), y(aCopy.y), z(aCopy.z), w(aCopy.w) {}
    
	///init x,y,z,w using base constructor
	vec4(const vec3& aVec, const T& aW):
		vec3(aVec), w(aW) {}
		
	///init x,y,z,w using base constructor
	vec4(const vec2& aVec, const T& aZ, const T& aW):
		vec2(aVec), z(aZ), w(aW) {}
		
	///init x,y,z,w using base constructor
	vec4(const T& aX, const T& aY, const T& aZ, const T& aW):
		vec3(aX, aY, aZ), w(aW) {}
		
	///init aLength fields with aValue 
    vec4(const item_type& aValue)
		x(aValue), y(aValue), z(aValue), w(aValue) {}
    
	///returns dot product of this and aOther
    inline item_type dot(cref aOther) const { return x*aOther.x + y*aOther.y + z*aOther.z +w*aOther.w; }
    
	///returns square length of this
    inline item_type length_sq() const { return x*x + y*y + z*z + w*w; }
    
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
		w /= len;
    }
	
    ///vector by vector addition 
    inline ref operator +=(cref aOther) 
    {
		x += aOther.x;
		y += aOther.y;
		z += aOther.z;
		w += aOther.w;
		return *this;
	}
    
    ///vector by vector substraction
    inline ref operator -=(cref aOther) 
    {
		x -= aOther.x;
		y -= aOther.y;
		z -= aOther.z;
		w -= aOther.w;
		return *this;
	}
    
    ///vector by scalar multiplication
    inline ref operator *=(const item_type& aOther) 
    {
		x *= aOther;
		y *= aOther;
		z *= aOther;
		w *= aOther;
		return *this;
	}
    
    ///vector by scalar division
    inline ref operator /=(const item_type& aOther) 
    {
		x /= aOther;
		y /= aOther;
		z /= aOther;
		w /= aOther;
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
		return type(x+aOther.x, y+aOther.y, z+aOther.z, w+aOther.w);
	}
    
    ///substraction by aOther vector
	///returns new vector 
    inline type operator-(cref aOther) const
    {
		return type(x-aOther.x, y-aOther.y, z-aOther.z, w-aOther.w);
	}
    
    ///vector by scalar multiplication
	///returns new vector 
    inline type operator*(const item_type& aOther) const
    {
		return type(x*aOther, y*aOther, z*aOther, w*aOther);
	}
    
    ///division by scalar
	///returns new vector 
    inline type operator/(const item_type& aOther) const 
    {
		return type(x/aOther, y/aOther, z/aOther, w/aOther);
	}
    
    ///vector negation
	///returns new vector 
    inline type operator-()
    {
		return type(-x, -y, -z, -w);
    }
	
    ///vector assignation
    inline ref operator=(cref aOther)
    {
		x = aOther.x;
		y = aOther.y;
		z = aOther.z;
		w = aOther.w;
    }

	inline friend type operator *(const T& lhs, cref& rhs)
	{
		return type(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
	}
	
	inline bool operator ==(cref aOther) const 
	{
		return x==aOther.x && y==aOther.y && z==aOther.z && w==aOther.w;
	}
	
	inline bool operator !=(cref aOther) const 
	{
		return x!=aOther.x || y!=aOther.y || z!=aOther.z || w!=aOther.w;
	}
	
	inline bool operator >(cref aOther) const 
	{
		return x>Other.x && y>aOther.y && z>aOther.z && w>aOther.w;
	}
	
	inline bool operator <(cref aOther) const 
	{
		return x<aOther.x && y<aOther.y && z<aOther.z && w<aOther.w;
	}
	
	inline bool operator >=(cref aOther) const 
	{
		return x>=aOther.x && y>=aOther.y && z>=aOther.z && w>=aOther.w;
	}
	
	inline bool operator <=(cref aOther) const 
	{
		return x<=aOther.x && y<=aOther.y && z<=aOther.z && w<=aOther.w;
	}
	
protected:
	T w;
};

#endif	/* Vec4H */