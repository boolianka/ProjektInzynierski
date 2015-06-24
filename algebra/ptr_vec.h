#ifndef PtrVecH
#define PtrVecH

#include "dyn_vec.hpp"

template <class T> class ptr_vec : public dyn_vec
{
public:
	typedef ptr_vec type;
	typedef T item_type;
	typedef type& ref;
	typedef type* ptr;
	typedef const type& cref;
	typedef type * const cptr;
	typedef item_type* iterator;

	ptr_vec() : 
		dyn_vec() {}

	ptr_vec(cref aCopy) : 
		m_Length(aCopy.m_Length), m_Data(aCopy.m_Data) {}

	ptr_vec(item_type* aArray, const unsigned& aLength) : 
		m_Length(aLength), m_Data(aArray)  {}
};

#endif