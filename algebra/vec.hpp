#include <math.h>

#ifndef VectorH
#define	VectorH

#define IS_NEAR_EQUAL(x,y,eps) (((x)-(y)<=(eps)) || ((y)-(x)<=(eps))) 
#define IS_EQUAL(x,y,zero) ((x)-(y)==(zero))

#define MIN(x,y) (((x)<(y))*x | ((x)>=(y))*y)

template <unsigned N, unsigned M> struct val_min
{
	const unsigned value = N < M ? N : M;
};

template <unsigned N, unsigned M> struct val_max
{
	const unsigned value = N > M ? N : M;
};

template <unsigned N, unsigned M> struct val_diff
{
	const unsigned value = val_max<N,M>::value < val_max<M,N>::value ? N-M : M-N;
};

template <class T, unsigned N> class vec
{
public:
    typedef vec type;
    typedef T item_type;
    typedef type& ref;
    typedef type* ptr;
    typedef const type& cref;
    typedef type * const cptr;
    static const unsigned Length = N;
	
	template <class S, unsigned M> 
		friend class vec;
	
	template <class S, unsigned P, unsigned Q>
		friend class mat;
	
	///default constructor - does nothing
    vec() {}

	///init aLength fields with aValue 
    vec(const item_type& aValue, const unsigned& aLength = N)
    {
        for(unsigned i=0; i<aLength; ++i)
            m_Data[i] = aValue;
        for(unsigned i=aLength; i<N; ++i)
            m_Data[i] = item_type();
    }
    
	///init fields with corresponding aOther fields, otherwise 0
    template <unsigned M> 
        explicit vec(const vec<T,M>& aOther) 
    {
        unsigned i=0, n=MIN(N, aOther.Length);
        for(i=0; i<n; ++i)
            m_Data[i] = aOther.m_Data[i];
        for(i=n; i<N; ++i)
            m_Data[i] = item_type();
    }
    
	///returns dot product of this and aOther
    item_type dot(cref aOther) const 
    {
        item_type tmp(0);
        for(unsigned i=0; i<N; ++i)
            tmp += m_Data[i] * aOther.m_Data[i];
        return tmp;
    }
    
	///returns square length of this
    item_type length_sq() const { return dot(*this); }
    
	///returns length of this
    item_type length() const { return (item_type) sqrt(length_sq()); }
        
	///returns distance between this and aOther
    item_type dist(cref aOther) const 
    { return (*this-aOther).length(); }
    
	///returns square distance between this and aOther
    item_type dist_sq(cref aOther) const 
    { return (*this-aOther).length_sq(); }
    
	///attempts to normalize vector (length will be 1, otherwise was/is 0) 
    void normalize() 
    {
        item_type temp = length_sq();
        if(IS_NEAR_EQUAL(item_type::ONE, temp, item_type::EPSILON_SQ))
            return;
        temp = (item_type) sqrt(temp);
        for(unsigned i=0; i<N; ++i)
            m_Data[i] /= temp;
    }
	
    ///vector by vector addition 
    ref operator +=(cref aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] += aOther.m_Data[i];
        return (*this);
    }
    
    ///vector by vector substraction
    ref operator -=(cref aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] -= aOther.m_Data[i];
        return (*this);
    }
    
    ///vector by scalar multiplication
    ref operator *=(const item_type& aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] *= aOther;
        return (*this);
    }
    
    ///vector by scalar division
    ref operator /=(const item_type& aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] /= aOther;
        return (*this);
    }
    
    ///summation with aOther vector
	///returns new vector 
    type operator+(cref aOther) const
    { return type(*this) += aOther; }
    
    ///substraction by aOther vector
	///returns new vector 
    type operator-(cref aOther) const
    { return type(*this) += aOther; }
    
	///returns dot product of this and aOther vectors
    item_type operator*(cref aOther) const
    { return dot(aOther); }
    
    ///vector by scalar multiplication
	///returns new vector 
    item_type operator*(const item_type& aOther) const
    { return type(*this) *= aOther; }
    
    ///division by scalar
	///returns new vector 
    item_type operator/(const item_type& aOther) const 
    { return type(*this) /= aOther; }
    
    ///vector negation
	///returns new vector 
    type operator-()
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] = -m_Data[i];
        return (*this);
    }
	
    ///vector assignation
    ref operator=(cref aOther)
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] = aOther.m_Data[i];
        return (*this);
    }
    
	///returns vector field by index 
    const item_type& operator[](const unsigned& index) const { return m_Data[index]; }
    item_type& operator[](const unsigned& index) { return m_Data[index]; } 
    	
protected:
    T m_Data[N];
};

template <class T, unsigned N, unsigned M>
	vec<T,val_max<N,M>::value> operator +(const vec<T,N>& x, const vec<T,M>& y)
	{
		vec<T,val_max<N,M>::value> p(x);
		vec<T,val_max<N,M>::value> q(y);
		return p+q;
	}
	
template <class T, unsigned N, unsigned M>
	vec<T,val_max<N,M>::value> operator -(const vec<T,N>& lhs, const vec<T,M>& rhs)
	{ return vec<T,val_max<N,M>::value>(rhs) - vec<T,val_max<N,M>::value>(lhs); }
	
template <class T, unsigned N, unsigned M>
	vec<T,val_max<N,M>::value>::item_type operator *(const vec<T,N>& x, const vec<T,M>& y)
	{ return vec<T,val_max<N,M>::value>(rhs) + vec<T,val_max<N,M>::value>(lhs); }
	
template <class T, unsigned N, unsigned M>
	vec<T, N> operator *(const T& lhs, cref rhs) 
	{ return rhs * lhs; }


#endif	/* VECTOR_HPP */

