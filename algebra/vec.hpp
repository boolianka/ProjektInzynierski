/* 
 * File:   Vector.hpp
 * Author: Piotr
 *
 * Created on 22 marca 2015, 23:29
 */

#include <math.h>

#ifndef VECTOR_HPP
#define	VECTOR_HPP

#define IS_NEAR_EQUAL(x,y,eps) (((x)-(y)<=(eps)) || ((y)-(x)<=(eps))) 
#define IS_EQUAL(x,y,zero) ((x)-(y)==(zero))

///forward
template <class T, unsigned M, unsigned N> class mat;


template <class T, unsigned N> class vec
{
public:
    typedef vec type;
    typedef T item_type;
    typedef type& ref;
    typedef type* ptr;
    typedef const type cref;
    typedef type * const cptr;
    static const unsigned item_count = N;
    
    template <unsigned M> 
        friend class vec<T, M>;
	template <unsigned M>
		friend class mat<T, N, M>;
	template <unsigned M>
		friend class mat<T, M, N>;
    
	///default constructor - does nothing
    vec() {}
    
	///initializes vector fields with aValue in number of aLength fields
    vec(const item_type& aValue, const unsigned& aLength = N)
    {
        for(unsigned i=0; i<aLength; ++i)
            m_Data[i] = aValue;
        for(unsigned i=aLength; i<N; ++i)
            m_Data[i] = item_type();
    }
    
	///initializes vector fields with aOther vector. If no corresponsing field found takes 0 as value
    template <unsigned M> 
        vec(vec<T, M>::cref aOther) 
    {
        unsigned i=0, n=i<std::min(N, aOther.item_count);
        for(i=0; i<n; ++i)
            m_Data[i] = aOther.m_Data[i];
        for(i=n; i<N; ++i)
            m_Data[i] = item_type();
    }
    
	///returns dot product with aOther vector
    item_type dot(cref aOther) const 
    {
        item_type tmp(0);
        for(unsigned i=0; i<N; ++i)
            tmp += m_Data[i] * aOther.m_Data[i];
        return tmp;
    }
    
	///returns square length of vector
    item_type length_sq() const { return dot(*this); }
    
	///returns length of vector
    item_type length() const { return (item_type) sqrt(length_sq()); }
        
	///returns distance between this and aOther vector
    item_type dist(cref aOther) const 
    { return (*this-aOther).length(); }
    
	///returns square distance between this and aOther vector
    item_type dist_sq(cref aOther) const 
    { return (*this-aOther).length_sq(); }
    
	///attempts to normalize vector (length will be 1, otherwise 0) 
    void normalize() 
    {
        item_type temp = length_sq();
        if(IS_NEAR_EQUAL(item_type::ONE, temp, item_type::EPSILON_SQ))
            return;
        temp = (item_type) sqrt(temp);
        for(unsigned i=0; i<N; ++i)
            m_Data[i] /= temp;
    }
	
    ///summation with aOther vector
	///returns this 
    ref operator +=(cref aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] += aOther.m_Data[i];
        return (*this);
    }
    
    ///substraction by aOther vector
	///returns this 
    ref operator -=(cref aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] -= aOther.m_Data[i];
        return (*this);
    }
    
    ///multiplication by scalar
	///returns this 
    ref operator *=(const item_type& aOther) 
    {
        for(unsigned i=0; i<N; ++i)
            m_Data[i] *= aOther;
        return (*this);
    }
    
    ///division by scalar
	///returns this 
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
    
    ///multiplication by scalar
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
    
	///returns vector field by index 
    item_type& operator[](const unsigned& index) { return m_Data[index]; } //TO DO private
    const item_type& operator[](const unsigned& index) const { return m_Data[index]; }
    
private:
    T m_Data[N];
};

//template <class T> cross(const vec<T,2>& x) TO DO
//template <class T> cross(const vec<T,3>& x, const vec<T,3>& y) TO DO
//template <class T> perp(const vec<T,2>& x) TO DO

#endif	/* VECTOR_HPP */

