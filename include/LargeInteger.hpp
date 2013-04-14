///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2013 Jimmie Bergmann - jimmiebergmann@gmail.com
//
// This software is provided 'as-is', without any express or
// implied warranty. In no event will the authors be held
// liable for any damages arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute
// it freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but
//    is not required.
// 
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any
//    source distribution.
// 
///////////////////////////////////////////////////////////////////////////////////

#ifndef __LARGE_NUMBER_HPP__
#define __LARGE_NUMBER_HPP__

// Very useful macro for check single bits
#define Bit(n)       (1 << (n))
#define CheckBit(n,i) ((bool)(((n) & Bit(i)) != 0)) // <- Use this

#include <memory>
#include <string>
#include <iostream>

// Notes:
// 1.	The "double operators" like += is way faster than some single sign operators.

class LargeInteger
{

public:

	// Constructors / descructors
	LargeInteger( );
	LargeInteger( const unsigned int p_Size );
	LargeInteger( const unsigned int p_Size, unsigned short p_Components, ... );
	LargeInteger( const unsigned int p_Size, unsigned short * p_Components );
	LargeInteger( const LargeInteger & p_LargeInteger );
	~LargeInteger( );

	// Public functions
	void Clear( );
	void PrintBinary( ) const;

	// Set functions
	void SetComponent( const unsigned int p_Index, const unsigned short p_Value );

	// Get functions
	unsigned short GetComponent( const unsigned int p_Index ) const;

	// Operators
	operator bool( ) const;
	bool operator ! ( ) const;
	void operator = ( const LargeInteger & p_LargeInteger );
	bool operator == ( const unsigned short p_Short ) const;
	bool operator == ( const LargeInteger & p_LargeInteger ) const;
	bool operator != ( const unsigned short p_Short ) const;
	bool operator != ( const LargeInteger & p_LargeInteger ) const;
	bool operator > ( const unsigned short p_Short ) const;
	bool operator > ( const LargeInteger & p_LargeInteger ) const;
	bool operator >= ( const unsigned short p_Short ) const;
	bool operator >= ( const LargeInteger & p_LargeInteger ) const;
	bool operator < ( const unsigned short p_Short ) const;
	bool operator < ( const LargeInteger & p_LargeInteger ) const;
	bool operator <= ( const unsigned short p_Short ) const;
	bool operator <= ( const LargeInteger & p_LargeInteger ) const;
	LargeInteger operator + ( const LargeInteger & p_LargeInteger ) const;
	LargeInteger & operator += ( const LargeInteger & p_LargeInteger );
	LargeInteger operator - ( const LargeInteger & p_LargeInteger ) const; // NOT WORKING
	LargeInteger & operator -= ( const LargeInteger & p_LargeInteger );  // NOT WORKING
	LargeInteger operator * ( const LargeInteger & p_LargeInteger ) const; // NOT WORKING
	LargeInteger & operator *= ( const LargeInteger & p_LargeInteger );  // NOT WORKING
	LargeInteger operator / ( const LargeInteger & p_LargeInteger ) const; // NOT WORKING
	LargeInteger & operator /= ( const LargeInteger & p_LargeInteger );  // NOT WORKING
	LargeInteger operator % ( const LargeInteger & p_LargeInteger ) const; // NOT WORKING
	LargeInteger & operator %= ( const LargeInteger & p_LargeInteger );  // NOT WORKING
	friend std::ostream & operator << ( std::ostream & os, const LargeInteger & p_LargeInteger );

private:

	// Private functions
	bool Allocate( const unsigned int p_Size );
	void Copy( const LargeInteger & p_LargeInteger );

	// Private variable members
	unsigned short * m_pComponents;
	unsigned int m_Size;

};

#endif