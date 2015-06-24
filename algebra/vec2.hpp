#ifndef Vec2H
#define	Vec2H

template <class T> class vec2
{
public:
    typedef vec2 type;
    typedef T item_type;
    typedef type& ref;
    typedef type* ptr;
    typedef const type cref;
    typedef type * const cptr;

	///default constructor - does nothing
    vec2() {}
    
	///copy constructor
	vec2(const vec2& aCopy):
		x(aCopy.x), y(aCopy.y) {}
		
	///init x and y value
	vec2(const T& aX, const T& aY):
		x(aX), y(aY) {}
	
	///init aLength fields with aValue 
    vec2(const item_type& aValue):
		x(aValue), y(aValue) {}
    
	///returns dot product of this and aOther
    inline item_type dot(cref aOther) const { return x*aOther.x + y*aOther.y; }
    
	///returns square length of this
    inline item_type length_sq() const { return x*x + y*y; }
    
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
    }
	
    ///vector by vector addition 
    inline ref operator +=(cref aOther) 
    {
		x += aOther.x;
		y += aOther.y;
		return *this;
	}
    
    ///vector by vector substraction
    inline ref operator -=(cref aOther) 
    {
		x -= aOther.x;
		y -= aOther.y;
		return *this;
	}
    
    ///vector by scalar multiplication
    inline ref operator *=(const item_type& aOther) 
    {
		x *= aOther;
		y *= aOther;
		return *this;
	}
    
    ///vector by scalar division
    inline ref operator /=(const item_type& aOther) 
    {
		x /= aOther;
		y /= aOther;
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
		return type(x+aOther.x, y+aOther.y);
	}
    
    ///substraction by aOther vector
	///returns new vector 
    inline type operator-(cref aOther) const
    {
		return type(x-aOther.x, y-aOther.y);
	}
    
    ///vector by scalar multiplication
	///returns new vector 
    inline type operator*(const item_type& aOther) const
    {
		return type(x*aOther, y*aOther);
	}
    
    ///division by scalar
	///returns new vector 
    inline type operator/(const item_type& aOther) const 
    {
		return type(x/aOther, y/aOther);
	}
    
    ///vector negation
	///returns new vector 
    inline type operator-()
    {
		return type(-x, -y);
    }
	
    ///vector assignation
    inline ref operator=(cref aOther)
    {
		x = aOther.x;
		y = aOther.y;
    }
	
	inline type perp() const { return vec2(-y, x); }

	inline friend type operator *(const T& lhs, cref& rhs)
	{
		return type(rhs.x * lhs, rhs.y * lhs);
	}
	
	inline bool operator ==(cref aOther) const 
	{
		return x==aOther.x && y==aOther.y;
	}
	
	inline bool operator !=(cref aOther) const 
	{
		return x!=aOther.x || y!=aOther.y;
	}
	
	inline bool operator >(cref aOther) const 
	{
		return x>aOther.x && y>aOther.y;
	}
	
	inline bool operator <(cref aOther) const 
	{
		return x<aOther.x && y<aOther.y;
	}
	
	inline bool operator >=(cref aOther) const 
	{
		return x>=aOther.x && y>=aOther.y;
	}
	
	inline bool operator <=(cref aOther) const 
	{
		return x<=aOther.x && y<=aOther.y;
	}
	
public:
	T x, y;
};



#endif	/* Vec2H */