#ifndef Matrix2x2H
#define	Matrix2x2H

#include "vec.hpp"

template <class T> class mat<T,2,2>
{
public:
    const unsigned Rows = 2;
    const unsigned Cols = 2;
    typedef mat<T,Cols,Rows> transpose_type;
    typedef mat<T,Cols-1, Rows-1> minor_type;
    typedef vec<T,Cols> row_vector_type;
    typedef vec<T,Rows> col_vector_type;
    typedef const unsigned& index_type;
    
    enum {eDiag=1, eNonDiag=2, eAll=(eNonDiag|eDiag)};
    
    static const type ONE;
    static const type ZERO;
    
    template <unsigned N, unsigned M>
        friend class mat<T, N, M>;
        
	///default constructor - does nothing
    mat() {}
    
	///initializes matrix fields with aValue using choosen aMode
    mat(const item_type& aValue, const int& aMode = eAll)
    {
        if(aMode==eDiag || aMode==eAll)
        {
            for(unsigned i=0; i<Rows; ++i)
                m_Data[i][i] = aValue;
        }
        if(aMode==eNonDiag || aMode==eAll)
        {
            for(unsigned i=0; i<Rows; ++i)
                for(unsigned j=0; j<i; ++j)
                    m_Data[i][j] = aValue;
            for(unsigned i=0; i<Rows; ++i)
                for(unsigned j=i+1; j<Cols; ++j)
                    m_Data[i][j] = aValue;
        }
    }
	
	///copy constructor
    mat(cref aCopy) 
    {
        for(unsigned i=0; i<Rows; ++i)
            m_Data[i] = aCopy[i];
    }

	///initializes matrix fields with corresponding fields of aCopy matrix
    template <unsigned P, unsigned Q>
        explicit mat(mat<T,P,Q>::cref aOther)                     //TO DO ?
    {
        unsigned rows = std::min(row_count, aOther.row_count);
        unsigned cols = std::min(col_count, aOther.col_count);
        
        for(unsigned i=0; i<rows; ++i)
            for(unsigned j=0; i<cols; ++j)
                m_Data[i][j] = aOther[i][j];    
    }
    
	///returns matrix transposition
    transpose_type transpose() const
    {
        transpose_type result;
		t = m_Data[0][1];
		m_Data[0][1] = m_Data[1][0];
		m_Data[1][0] = m_Data[0][1];
        return result;
    }
    
	///returns matrix without aX row and aY column
    minor_type minor(index_type aX, index_type aY) const
    {
        minor_type result;
        
        for(unsigned i=0; i<aX; ++i)
        {
            for(unsigned j=0; j<aY; ++j)
                result[i][j] = m_Data[i][j];
            for(unsigned j=aY; j<Cols; ++j)
                result[i][j-1] = m_Data[i][j];
        }
        
        for(unsigned i=aX+1; i<Rows; ++i)
        {
            for(unsigned j=0; j<aY; ++j)
                result[i-1][j] = m_Data[i][j];        
            for(unsigned j=aY+1; j<Cols; ++j)
                result[i-1][j-1] = m_Data[i][j];
        }
        
        return result;
    }
    
	///returns row as a vector
    row_vector_type row(index_type aIndex) const
    { return m_Data[aIndex]; }
    
	///returns column as a vector
    const col_vector_type& col(index_type aIndex) const
    {
        col_vector_type result;
        for(unsigned i=0; i<Rows; ++i)
            result[i] = m_Data[i][aIndex];
        return result;
    }
    
	///returns matrix determinant
    item_type det() const
    {
		return m_Data[0][0]*m_Data[1][1]-m_Data[0][1]*m_Data[1][0];
    }
    
	///returns inversed square matrix 
    type inverse() const
    {        
        type result(type::ONE);
		
        type copy(*this);
        typename row_vector_type::item_type k;
        
        for(unsigned i=0; i<Rows; ++i)
        {
            k = copy[i][i];
            for(unsigned j=i+1; j<Rows; ++j)
            {
                copy[j] -= (copy[j][i]/k)*copy[i];
                result[j] -= (result[j][i]/k)*result[i];
            }
            copy[i] /= k;
        }
        
        return result;
    }
    
    ///calculates LUx decomposition
	///aLower - lower triangle matrix
	///aUpper - upper triangle matrix
    void factorize(ref aLower, ref aUpper) const                              //TO DO
    {
        if(Rows != Cols)
            throw "LU decomposition error";//return result;
        
        new(&aLower) type(ONE);
        new(&aUpper) type(*this);
        
        typename row_vector_type::item_type k;
        
        for(unsigned i=0; i<Rows; ++i)
        {
            k=x[i][i];
            for(unsigned j=i+1; j<Rows; ++j)
            {
                y[j] = x[j][i] / k;
                x[j] -= (x[j][i] / k) * x[i];
            }
        }
    }
    
	///matrix addition
    ref operator +=(cref x) 
    {
        for(unsigned i=0; i<Rows; ++i)
            for(unsigned j=0; j<Cols; ++j)
                m_Data[i][j] += x[i][j];
        return *this;
    }
    
	///matrix substraction
    ref operator -=(cref x) 
    {
        for(unsigned i=0; i<Rows; ++i)
            for(unsigned j=0; j<Cols; ++j)
                m_Data[i][j] -= x[i][j];
        return *this;
    }
    
	///matrix by transponed matrix  multiplication
    mat<T,Rows,Rows> mul_trans(cref x)
    {
        mat<T,Rows,Rows> temp;
        for(unsigned i=0; i<Rows; ++i)
            for(unsigned j=0; j<Cols; ++j)
                temp[i][j] = m_Data[i].dot(x[j]);
        return temp;
    }
    
	///matrix by matrix multiplication
    template <unsigned Columns>
        mat<T,Rows,Columns> operator *=(typename mat<T,Cols,Columns>::cref x) 
        {

            mat<T,Rows,Columns> temp;
            for(unsigned i=0; i<Rows; ++i)
                for(unsigned j=0; j<Columns; ++j)
                    temp[i][j] = m_Data[i].dot(x.col(j));
            return temp;
        }
    
	///matrix by scalar multiplication 
    ref operator *=(const item_type& x)
    {
        for(unsigned i=0; i<Rows; ++i)
            m_Data[i] *= x;
        return *this;
    }
    
	///matrix by scalar division 
    ref operator /=(const item_type& x)
    {
        for(unsigned i=0; i<Rows; ++i)
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
    { return type(*this) -= x; }
    
	///matrix by scalar division 
    type operator /(const item_type& x) const
    { return type(*this) -= x; }
    
	///matrix field extraction
    row_vector_type& operator[](const unsigned& index) { return m_Data[index];}
    const row_vector_type& operator[](const unsigned& index) const { return m_Data[index];}
    
	///matrix assignation
    ref operator =(cref x)
    {
        for(unsigned i=0; i<Rows; ++i)
            m_Data[i] = x[i];
    }
    
private:
    vec<T, Cols>::type m_Data[Rows];
	
    //item_type m_Data[Rows*Cols];
};

typedef mat<T,2,2> mat2x2;

template <class T> 
	const mat2x2::type mat2x2::ONE = mat2x2(1, eDiag);
	
template <class T> 
	const mat2x2::type mat2x2::ZERO = mat2x2(0, eAll);
	
//brakuje speca dla 2x2, on wyczerpuje minor :) 
//i ogolnie jest prostz w implementacji

//brakuje szablonu dla kontroli safe_matrix i fast_matrix,
//chyba ze osobne szablony

//template <class T, class Size> class mat<T, Size, Size>
//{
//};

#endif	/* Matrix2x2H */

