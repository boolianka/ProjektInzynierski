#ifndef MatrixH
#define	MatrixH

#include "dyn_vec.hpp"

class MatrixException {};

template <class T> class dyn_mat
{
public:
	typedef dyn_mat type;
	typedef T item_type;
	typedef type& ref;
	typedef type* ptr;
	typedef const type& cref;
	typedef type * const cptr;

    typedef dyn_mat transpose_type;
	typedef dyn_mat minor_type;
    typedef dyn_vec<T> row_vector_type;
	typedef dyn_vec<T> col_vector_type;
    typedef const unsigned& index_type;
    
    enum {eDiag=1, eNonDiag=2, eAll=(eNonDiag|eDiag)};
    
	///default constructor - does nothing
	dyn_mat() : 
		m_Data(0) {}

	dyn_mat(const unsigned& aRows, const unsigned& aCols) :
		m_Data(new item_type[aRows*aCols]) { }

	dyn_mat(const unsigned& aRows, const unsigned& aCols, const T& aValue, const int& aMode = eAll) :
		m_Data(new T[aRows*aCols])
	{
		unsigned length = aRows*aCols;
		if (aMode == eDiag || aMode == eAll)
		{
			for (unsigned i = 0; i < length; i += aRows + 1)
				m_Data[i] = aValue;
		}
		if (aMode == eNonDiag || aMode == eAll)
		{
			for (unsigned i = 1, count = aRow - 1; i < length; ++i)
			{
				for (j = 0; j < count; ++j, ++i)
					m_Data[i] = aValue;
			}
		}
	}
    
	///copy constructor
	dyn_mat(cref aCopy) :
		m_Data(new T[aCopy.m_RowCount*aCopy.m_ColCount])
	{
		for (unsigned i = 0, length = aCopy.m_; i < m_RowCount; ++i)
			m_Data[i] = aCopy[i];
	}

	virtual ~dyn_mat()
	{
		delete[] m_Data;
	}

	item_type& operator()(index_type aRow, index_type aCol)
	{
		return m_Data[aRow*m_ColCount + aCol];
	}

	const item_type& operator()(index_type aRow, index_type aCol) const
	{
		return m_Data[aRow*m_ColCount + aCol];
	}
    
	///returns matrix transposition
	transpose_type transpose() const
	{
		transpose_type result(m_ColCount, m_RowCount);
		for (unsigned i = 0; i < m_RowCount; ++i)
		{
			for (unsigned j = 0; j < m_ColCount; ++j)
				result.m_Data[i*m_RowCount + j] = m_Data[i*m_ColCount + j];
		}
		return result;
	}
    
	///returns matrix without aX row and aY column
	minor_type minor(index_type aRow, index_type aCol) const	//TO DO
		throw(MatrixException)
	{
		if (m_RowCount == 1 || m_ColCount == 1)
			throw MatrixException();

		minor_type result(m_RowCount - 1, m_ColCount - 1);

		for (unsigned i = 0; i < result.m_RowCount; ++i)
		{
			for (unsigned j = 0; j < result.m_ColCount; ++j)
			{
				result.m_Data[]
			}

		}

		for (unsigned i = 0; i < aRow; ++i)
		{
			for (unsigned j = 0; j < aY; ++j)
				result(i, j) = m_Data[i*m_RowCount + j];
			for (unsigned j = aY; j < Cols; ++j)
				result(i, j - 1) = m_Data[i*m_RowCount + j];
		}

		for (unsigned i = aRow + 1; i < m_RowCount; ++i)
		{
			for (unsigned j = 0; j < aY; ++j)
				result(i - 1, j) = m_Data[i*m_RowCount + j];
			for (unsigned j = aY + 1; j < Cols; ++j)
				result(i - 1, j - 1) = m_Data[i*m_RowCount + j];
		}

		return result;
	}
    
	///returns row as a vector
    row_vector_type row(index_type aIndex) const
    { return  row_vector_type(m_ColCount, m_Data[aIndex*m_ColCount]); }
    
	///returns column as a vector
    /*const col_vector_type& col(index_type aIndex) const
    {
        col_vector_type result;
        for(unsigned i=0; i<m_RowCount; ++i)
            result[i] = m_Data[i][aIndex];
        return result;
    }*/
    
	///returns matrix determinant
    item_type det() const 
		throw(MatrixException)
    {
		if (m_ColCount != m_RowCount)
			throw MatrixException();

		//gauss elimination

		row_vector_type u, w;
		item_type k;

		for (unsigned i = 0; i < m_RowCount; ++i)
		{
			u = (*this)[i];
			for (unexpected j = i+1; j < m_RowCount; ++j)
			{
				w = (*this)[j];
				k = w[i] / u[i];
				w -= u*k;
			}
		}



    }
    
	///returns inversed square matrix 
	type inverse() const throw(MatrixException)
	{
		if (m_ColCount != m_RowCount)
			throw MatrixException();

		type copy(*this);
    }
    
    ///calculates LUx decomposition
	///aLower - lower triangle matrix
	///aUpper - upper triangle matrix
    void factorize(ref aLower, ref aUpper) const throw(MatrixException)                            //TO DO 
    {
		if (m_RowCount != Cols)
			throw MatrixException();
		
		row_vector_type u, w;
		item_type k;

		for (unsigned i = 0; i < m_RowCount; ++i)
		{
			u = (*this)[i];
			for (unsigned j = i + 1; j < m_RowCount; ++j)
			{
				w = (*this)[j];
				k = w[i] / u[i];
				w -= u*k;
			}
		}




            //throw "LU decomposition error";//return result;
        
        new(&aLower) type(ONE);
        new(&aUpper) type(*this);
        
        typename row_vector_type::item_type k;
        
        for(unsigned i=0; i<m_RowCount; ++i)
        {
            k=x[i][i];
            for(unsigned j=i+1; j<m_RowCount; ++j)
            {
                y[j] = x[j][i] / k;
                x[j] -= (x[j][i] / k) * x[i];
            }
        }
    }
    
	///matrix addition
    ref operator +=(cref x) 
    {
        for(unsigned i=0; i<m_RowCount; ++i)
            for(unsigned j=0; j<Cols; ++j)
                m_Data[i][j] += x[i][j];
        return *this;
    }
    
	///matrix substraction
    ref operator -=(cref x) 
    {
        for(unsigned i=0; i<m_RowCount; ++i)
            for(unsigned j=0; j<Cols; ++j)
                m_Data[i][j] -= x[i][j];
        return *this;
    }
    
	///matrix by transponed matrix  multiplication
    type mul_trans(cref x)
    {
		if (m_ColCount != x.m_ColCount)
			throw MatrixException();



        dyn_mat temp;
        for(unsigned i=0; i<m_RowCount; ++i)
            for(unsigned j=0; j<m_ColCount; ++j)
                temp[i][j] = m_Data[i].dot(x[i]);
        return temp;
    }
    
	///matrix by matrix multiplication
	ref operator *=(cref aOther) 
	{
		if (m_ColCount != aOther.m_RowCount)
			throw MatrixException();

		type temp;
		for(unsigned i=0; i<m_RowCount; ++i)
			for(unsigned j=0; j<m_ColCount; ++j)
				temp.m_Data[i][j] = m_Data[i].dot(aOther.col(j));
		return temp;
	}
    
	///matrix by scalar multiplication 
    ref operator *=(const item_type& x)
	{
		for (unsigned i = 0, length = m_RowCount*m_ColCount; i<length; ++i)
            m_Data[i] *= x;
        return *this;
    }
    
	///matrix by scalar division 
    ref operator /=(const item_type& x)
    {
        for(unsigned i=0, length = m_RowCount*m_ColCount; i<length; ++i)
            m_Data[i] /= x;
        return *this;
    }
    
	///matrix addition 
    type operator +(cref x) const 
    { return type(*this) += x; }
    
	///matrix substraction 
    type operator -(cref x) const 
    { return type(*this) -= x; }
    
	///matrix by scalar multiplication 
    type operator *(const item_type& x) const
    { return type(*this) *= x; }
    
	///matrix by scalar division 
    type operator /(const item_type& x) const
    { return type(*this) /= x; }
    
	///matrix field extraction
    row_vector_type& operator[](const unsigned& index) { return m_Data[index*m_ColCount];}
    const row_vector_type& operator[](const unsigned& index) const { return m_Data[index*m_ColCount];}
    
	///matrix assignation
	ref operator =(cref x)
	{
		for (unsigned i = 0, length = m_RowCount*m_ColCount; i < length; ++i)
			m_Data[i] = x.m_Data[i];
	}
    
	unsigned RowCount() const { return m_RowCount; }
	unsigned ColCount() const { return m_ColCount; }

private:
	unsigned m_RowCount;
	unsigned m_ColCount;
	T *m_Data;
};
	
//brakuje speca dla 2x2, on wyczerpuje minor :) 
//i ogolnie jest prostz w implementacji

//brakuje szablonu dla kontroli safe_matrix i fast_matrix,
//chyba ze osobne szablony

//template <class T, class Size> class mat<T, Size, Size>
//{
//};

#endif	/* MatrixH */

