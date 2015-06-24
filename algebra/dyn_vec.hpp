#ifndef DynVectorH
#define DynVectorH

#include <math.h>

#define MIN(x,y) (x)<(y)?(x):(y)

class VectorLengthException {};

class VectorArithmeticException {};



//template <class T, class R, class A> class dyn_vec
//{
//public:
//	typedef dyn_vec type;
//	typedef T item_type;
//	typedef type& ref;
//	typedef type* ptr;
//	typedef const type& cref;
//	typedef type * const cptr;
//	typedef item_type* iterator;
//	typedef A allocator;
//};

//wektor dokonuje obliczen, ale nie powinien miec zadnych informacji skad ma dane, po prostu na nich operuje


//
//template <class T> class dyn_mat
//{
//public:
//	typedef dyn_vec type;
//	typedef T item_type;
//	typedef type& ref;
//	typedef type* ptr;
//	typedef const type& cref;
//	typedef type * const cptr;
//	typedef weakptr_vec* iterator;
//};

template <class T> class base_alloc
{
public:
	virtual T* alloc(T* aPtr, const unsigned& aLength) = 0;
	virtual void dealloc() = 0;
};

template <class T> class array_alloc : public base_alloc<T>
{
public:
	virtual T* alloc(T* aPtr, const unsigned& aLength) { return new T[aLength]; }
	virtual void dealloc() {}
};


template <class T>  class array_share : public base_alloc<T>
{
public:
	virtual T* alloc(T* aPtr, const unsigned& aLength) { return aPtr; }
	virtual void dealloc() {}
};


template <class T>//, template <typename> class A> 
class dyn_vec
{
public:
	typedef dyn_vec type;
	typedef T item_type;
	typedef type& ref;
	typedef type* ptr;
	typedef const type& cref;
	typedef type * const cptr;
	//typedef item_type* iterator;
	//typedef A<T> allocator;

	friend class dyn_mat<T, A>;

	///default constructor - does nothing
	dyn_vec() :
		m_Data(0), m_Length(0) {}

	///init all aLength fields with aValue 
	dyn_vec(const unsigned& aLength, const item_type& aValue) :
		m_Data(new T[aLength])
	{
		for (unsigned i = 0; i < aLength; ++i)
			m_Data[i] = aValue;
	}

	///init aLength fields with aArray 
	dyn_vec(const unsigned& aLength, const item_type* aArray) :
		m_Data(new T[aLength])
	{
		for (unsigned i = 0; i < aLength; ++i)
			m_Data[i] = aArray[i];
	}

	///copy constructor
	dyn_vec(cref aCopy) : 
		m_Data(new item_type[aCopy.m_Length]), m_Length(aCopy.m_Length)
	{
		for (unsigned i = 0; i < aLength; ++i)
			m_Data[i] = aCopy.m_Data[i];
	}

	~dyn_vec()
	{
		delete[] m_Data; //to jest problem
		//m_Allocator.destroy(m_Data);
	}

	///returns dot product of this and aOther
	item_type dot(cref aOther) const
	{
		unsigned length = MIN(m_Length, aOther.m_Length);
		item_type tmp(0);
		for (unsigned i = 0; i < length; ++i)
			tmp += m_Data[i] * aOther.m_Data[i];
		return tmp;
	}

	///returns square length of this
	item_type length_sq() const { return dot(*this); }

	///returns length of this
	item_type length() const { return (item_type) sqrt(length_sq()); }

	///returns distance between this and aOther
	item_type dist(cref aOther) const { return (*this - aOther).length(); }

	///returns square distance between this and aOther
	item_type dist_sq(cref aOther) const { return (*this - aOther).length_sq(); }

	///attempts to normalize dyn_vector (length will be 1, otherwise was/is 0) 
	void normalize()
	{
		item_type temp = length_sq();
		//if (IS_NEAR_EQUAL(item_type::ONE, temp, item_type::EPSILON_SQ))
		//	return;
		temp = (item_type) sqrt(temp);
		for (unsigned i = 0; i < m_Length; ++i)
			m_Data[i] /= temp;
	}

	///dyn_vector by dyn_vector addition 
	ref operator +=(cref aOther)
	{
		if (m_Length < aOther.m_Length)
			resize(aOther.m_Length);
		unsigned length = MIN(m_Length, aOther.m_Length);
		for (unsigned i = 0; i < length; ++i)
			m_Data[i] += aOther.m_Data[i];
		return (*this);
	}

	///dyn_vector by dyn_vector substraction
	ref operator -=(cref aOther)
	{
		if (m_Length < aOther.m_Length)
			resize(aOther.m_Length);
		unsigned length = MIN(m_Length, aOther.m_Length);
		for (unsigned i = 0; i < length; ++i)
			m_Data[i] -= aOther.m_Data[i];
		return (*this);
	}

	///dyn_vector by scalar multiplication
	ref operator *=(const item_type& aOther)
	{
		for (unsigned i = 0; i < m_Length; ++i)
			m_Data[i] *= aOther;
		return (*this);
	}

	///dyn_vector by scalar division
	ref operator /=(const item_type& aOther)
	{
		for (unsigned i = 0; i < m_Length; ++i)
			m_Data[i] /= aOther;
		return (*this);
	}

	///summation with aOther dyn_vector
	///returns new dyn_vector 
	type operator+(cref aOther) const
	{
		return type(*this) += aOther;
	}

	///substraction by aOther dyn_vector
	///returns new dyn_vector 
	type operator-(cref aOther) const
	{
		return type(*this) += aOther;
	}

	///returns dot product of this and aOther dyn_vectors
	item_type operator*(cref aOther) const
	{
		return dot(aOther);
	}

	///dyn_vector by scalar multiplication
	///returns new dyn_vector 
	type operator*(const item_type& aOther) const
	{
		return type(*this) *= aOther;
	}

	///division by scalar
	///returns new dyn_vector 
	type operator/(const item_type& aOther) const
	{
		return type(*this) /= aOther;
	}

	///dyn_vector negation
	///returns new dyn_vector 
	type operator-()
	{
		for (unsigned i = 0; i < m_Length; ++i)
			m_Data[i] = -m_Data[i];
		return (*this);
	}

	///dyn_vector assignation
	ref operator=(cref aOther)
	{
		resize(aOther.m_Length);
		for (unsigned i = 0; i < m_Length; ++i)
			m_Data[i] = aOther.m_Data[i];
		return (*this);
	}

	///returns dyn_vector field by index 
	const item_type& operator[](const unsigned& index) const { return m_Data[index]; }
	item_type& operator[](const unsigned& index) { return m_Data[index]; }

	friend type operator *(const item_type& rhs, cref lhs) { return lhs*rhs; }

protected:
	unsigned m_Length;
	T* m_Data;

	virtual void resize(const unsigned& aLength)
	{
		T* newData = new T[aLength];

		unsigned length = MIN(m_Length, aLength);
		for (unsigned i = 0; i < length; ++i)
			newData[i] = m_Data[i];
		for (unsigned i = length; i < m_Length; ++i)
			newData[i] = item_type();

		delete[] m_Data;
		m_Data = newData;
		m_Length = aLength;
	}
};

#endif ///DynVectorH