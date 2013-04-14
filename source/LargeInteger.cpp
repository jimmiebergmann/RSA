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

#include "LargeInteger.hpp"
#include <algorithm>
#include <stdlib.h>

// Constructors / descructors
LargeInteger::LargeInteger( ) :
	m_pComponents( NULL ),
	m_Size( 0 )
{
}

LargeInteger::LargeInteger( const unsigned int p_Size ) :
	m_pComponents( NULL ),
	m_Size( 0 )

{
	if( Allocate( p_Size ) )
	{
		return;
	}
}

LargeInteger::LargeInteger( const unsigned int p_Size, unsigned short p_Components, ... ) :
	m_pComponents( NULL ),
	m_Size( 0 )
{
	if( !Allocate( p_Size ) )
	{
		return;
	}

	// Get the pointer to the value param in order to get all the components that we want to set.
	unsigned short * pointer = &p_Components;

	// Set every single value
	for( unsigned int i = 0; i < p_Size; i++ )
	{
		// Set the current value to the value that the pointer currently is pointing at.
		m_pComponents[ i ] = *pointer;

		// Move the pointer 2 bytes since we are using shorts.
		pointer += 2;
	}
}

LargeInteger::LargeInteger( const unsigned int p_Size, unsigned short * p_Components ) :
	m_pComponents( NULL ),
	m_Size( 0 )
{
	// Allocate the components
	if( !Allocate( p_Size ) )
	{
		return;
	}

	// Add all the components
	for( unsigned int i = 0; i < p_Size; i++ )
	{
		m_pComponents[ i ] = *p_Components;

		// Move the pointer
		p_Components++;
	}
}

LargeInteger::LargeInteger( const LargeInteger & p_LargeInteger ) :
	m_pComponents( NULL ),
	m_Size( 0 )
{
	if( Allocate( p_LargeInteger.m_Size ) )
	{
		return;
	}

	Copy( p_LargeInteger );
}

LargeInteger::~LargeInteger( )
{
	// Delete the allocated components
	if( m_pComponents )
	{
		delete [ ] m_pComponents;
		m_pComponents = NULL;
	}

	// Set the size of the large interger to 0
	m_Size = 0;
}

// Public functions
void LargeInteger::Clear( )
{
	for( unsigned int i = 0; i < m_Size; i++ )
	{
		m_pComponents[ i ] = 0;
	}
}

void LargeInteger::Copy( const LargeInteger & p_LargeInteger )
{
	// Make sure we don't go out of bound by calculating the right size.
	unsigned int componentsToCopy = ( m_Size >= p_LargeInteger.m_Size ) ? p_LargeInteger.m_Size : m_Size ;

	// You might lose data if the parameter large integer is larger in allocation size.
	for( unsigned int i = 0; i < componentsToCopy; i++ )
	{
		m_pComponents[ i ] = p_LargeInteger.m_pComponents[ i ];
	}
}

int LargeInteger::Compare( const unsigned short p_Short ) const
{
	for( unsigned int i = 1; i < m_Size; i++ )
	{
		if( m_pComponents[ i ] != 0 )
		{
			return 1;
		}
	}

	if( m_pComponents[ 0 ] > p_Short )
	{
		return 1;
	}
	else if( m_pComponents[ 0 ] < p_Short )
	{
		return -1;
	}

	// They are equal
	return 0;
}

int LargeInteger::Compare( const LargeInteger & p_LargeInteger ) const
{
	// Let's calculate how many components we want to compare with each other.
	unsigned int i = 0;

	if( m_Size == p_LargeInteger.m_Size )
	{
		i = m_Size - 1;
	}
	else if( m_Size > p_LargeInteger.m_Size )
	{
		// Calculate i + check if the number is larger than the param value
		for( i = m_Size - 1; i >= p_LargeInteger.m_Size; i-- )
		{
			if( m_pComponents[ i ] != 0 )
			{
				return 1;
			}
		}
	}
	else if( m_Size < p_LargeInteger.m_Size )
	{
		// Calculate i + check if the number is lower than the param value
		for( i = p_LargeInteger.m_Size - 1; i >= m_Size; i-- )
		{
			if( p_LargeInteger.m_pComponents[ i ] != 0 )
			{
				return -1;
			}
		}
	}

	while( true )
	{
		if( m_pComponents[ i ] > p_LargeInteger.m_pComponents[ i ] )
		{
			return 1;
		}
		else if( m_pComponents[ i ] < p_LargeInteger.m_pComponents[ i ] )
		{
			return -1;
		}

		// The large integers are obviously equal to each other.
		if( i == 0 )
		{
			return 0;
		}

		// Decrease i
		i--;
	}

	return 0;
}

// Set functions
void LargeInteger::SetComponent( const unsigned int p_Index, const unsigned short p_Component )
{
	if( p_Index < m_Size )
	{
		m_pComponents[ p_Index ] = p_Component;
	}
}

// Get functions
unsigned short LargeInteger::GetComponent( const unsigned int p_Index ) const
{
	if( p_Index >= m_Size )
	{
		return 0;
	}

	return m_pComponents[ p_Index ];
}

unsigned int LargeInteger::GetSize( ) const
{
	return m_Size;
}

// Operators
unsigned short LargeInteger::operator [ ] ( unsigned int p_Index ) const
{
	return GetComponent( p_Index );
}

LargeInteger::operator bool( ) const
{
	// Make sure the large integer is allocated
	if( m_Size == 0 )
	{
		return true;
	}

	// Check if all the components are 0
	for( unsigned int i = 1; i < m_Size; i++ )
	{
		if( m_pComponents[ i ] != 0 )
		{
			return true;
		}
	}

	return false;
}

bool LargeInteger::operator ! ( ) const
{
	// Make sure the large integer is allocated
	if( m_Size == 0 )
	{
		return true;
	}

	// Check if all the components are 0
	for( unsigned int i = 1; i < m_Size; i++ )
	{
		if( m_pComponents[ i ] != 0 )
		{
			return false;
		}
	}

	return true;
}
void LargeInteger::operator = ( const LargeInteger & p_LargeInteger )
{
	Copy( p_LargeInteger );
}

bool LargeInteger::operator == ( const unsigned short p_Short ) const
{
	return Compare( p_Short ) == 0;
}

bool LargeInteger::operator == ( const LargeInteger & p_LargeInteger ) const
{
	return Compare( p_LargeInteger ) == 0;
}

bool LargeInteger::operator != ( const unsigned short p_Short ) const
{
	return Compare( p_Short ) != 0;
}

bool LargeInteger::operator != ( const LargeInteger & p_LargeInteger ) const
{
	return Compare( p_LargeInteger ) != 0;
}

bool LargeInteger::operator > ( const unsigned short p_Short ) const
{
	return Compare( p_Short ) > 0;
}
bool LargeInteger::operator > ( const LargeInteger & p_LargeInteger ) const
{
	return Compare( p_LargeInteger ) > 0;
}

bool LargeInteger::operator >= ( const unsigned short p_Short ) const
{
	return Compare( p_Short ) >= 0;
}

bool LargeInteger::operator >= ( const LargeInteger & p_LargeInteger ) const
{
	return Compare( p_LargeInteger ) >= 0;
}

bool LargeInteger::operator < ( const unsigned short p_Short ) const
{
	return Compare( p_Short ) < 0;
}

bool LargeInteger::operator < ( const LargeInteger & p_LargeInteger ) const
{
	return Compare( p_LargeInteger ) < 0;
}

bool LargeInteger::operator <= ( const unsigned short p_Short ) const
{
	return Compare( p_Short ) <= 0;
}

bool LargeInteger::operator <= ( const LargeInteger & p_LargeInteger ) const
{
	return Compare( p_LargeInteger ) <= 0;
}
/*
LargeInteger LargeInteger::operator + ( const LargeInteger & p_LargeInteger ) const
{
	LargeInteger newInteger( m_Size );
	unsigned int overflow = 0;

	for( unsigned int i = 0; i < m_Size; i++ )
	{
		// Calculate the new current component by adding the two componets
		// plus the last overflow. (Still use the overflow variable fort this, easier)
		overflow = static_cast<unsigned int>( m_pComponents[ i ] ) +
			static_cast<unsigned int>( p_LargeInteger.m_pComponents[ i ] ) +
			overflow;

		// Set the components( just the first 16 bits )
		newInteger.m_pComponents[ i ] = overflow & 0xFFFF;

		// Calculate the new overflow by bitshift 16 bits
		overflow = overflow >> 16;
	}

	// We do not allow overflow at all. We should set all components
	// to the max value if there's a overflow.
	if( overflow )
	{
		for( unsigned int i = 0; i < m_Size; i++ )
		{
			newInteger.m_pComponents[ i ] = 0xFFFF;
		}
	}
	
	// Return a new large integer
	return LargeInteger( newInteger.m_Size, newInteger.m_pComponents );

	return *this;
}*/

LargeInteger & LargeInteger::operator += ( const LargeInteger & p_LargeInteger )
{
	/*unsigned int overflow = 0;

	for( unsigned int i = 0; i < m_Size; i++ )
	{
		// Calculate the new current component by adding the two componets
		// plus the last overflow. (Still use the overflow variable fort this, easier)
		overflow = static_cast<unsigned int>( m_pComponents[ i ] ) +
			static_cast<unsigned int>( p_LargeInteger.m_pComponents[ i ] ) +
			overflow;

		// Set the components( just the first 16 bits )
		m_pComponents[ i ] = overflow & 0xFFFF;

		// Calculate the new overflow by bitshift 16 bits
		overflow = overflow >> 16;
	}

	// We do not allow overflow at all. We should set all components
	// to the max value if there's a overflow.
	if( overflow )
	{
		for( unsigned int i = 0; i < m_Size; i++ )
		{
			m_pComponents[ i ] = 0xFFFF;
		}
	}
*/
	return *this;
}

/*
LargeInteger LargeInteger::operator - ( const LargeInteger & p_LargeInteger ) const
{
	LargeInteger newInteger( m_Size );

	unsigned short borrow = 0;

	if( m_Size == p_LargeInteger.m_Size )
	{
		for( unsigned int i = 0; i < m_Size; i++ )
		{
			newInteger.m_pComponents[ i ] = m_pComponents[ i ] - p_LargeInteger.m_pComponents[ i ] - borrow;

			borrow = static_cast< unsigned short >(
				p_LargeInteger.m_pComponents[ i ] > m_pComponents[ i ] );
		}
	}
	else if( m_Size > p_LargeInteger.m_Size )
	{
		for( unsigned int i = 0; i < p_LargeInteger.m_Size; i++ )
		{
			newInteger.m_pComponents[ i ] = m_pComponents[ i ] - p_LargeInteger.m_pComponents[ i ] - borrow;

			borrow = static_cast< unsigned short >(
				p_LargeInteger.m_pComponents[ i ] > m_pComponents[ i ] );
		}

		for( unsigned int i = p_LargeInteger.m_Size; i < m_Size; i++ )
		{
			if( m_pComponents[ i ] != 0 )
			{
				borrow = 1;
				break;
			}

			newInteger.m_pComponents[ i ] = 0;
		}

	}
	else if( m_Size < p_LargeInteger.m_Size )
	{
		for( unsigned int i = 0; i < m_Size; i++ )
		{
			newInteger.m_pComponents[ i ] = m_pComponents[ i ] - p_LargeInteger.m_pComponents[ i ] - borrow;

			borrow = static_cast< unsigned short >(
				p_LargeInteger.m_pComponents[ i ] > m_pComponents[ i ] );
		}

		for( unsigned int i = m_Size; i < p_LargeInteger.m_Size; i++ )
		{
			if( p_LargeInteger.m_pComponents[ i ] != 0 )
			{
				borrow = -1;
				break;
			}
		}

	}

	// We're having a overflow if there's any borrowed numbers left.
	// Then let's return a clear large integer.
	if( borrow != 0 )
	{
		newInteger.Clear( );
		
		// Return a new large integer
		return LargeInteger( newInteger.m_Size, newInteger.m_pComponents );
	}


	// Return a new large integer
	return LargeInteger( newInteger.m_Size, newInteger.m_pComponents );
}
*/
LargeInteger & LargeInteger::operator -= ( const LargeInteger & p_LargeInteger )
{
	// Check if the param value is larger than the current one.
	// We do this by using the > operator.
	// NOT FAST AT ALL!
	if( p_LargeInteger >= *this )
	{
		Clear( );
		return *this;
	}

	/*bool smallerNumber = false;

	for( int i = m_Size - 1; i >= 0 ; i-- )
	{
	}*/


/*
	int a = 21;

	std::cout << "BIT: ";
	for( int i = 31; i >= 0; i-- )
	{
		std::cout << CheckBit( a, i );
	}
	std::cout << std::endl << std::endl;

*/
/*
	int overflow = 0;

	for( int i = m_Size - 1; i >= 0 ; i-- )
	{
		// Calculate the new current component by subtracting the two componets
		// plus adding the last overflow. (Still use the overflow variable fort this, easier)
		overflow = static_cast<int>( m_pComponents[ i ] ) -
			static_cast<int>( p_LargeInteger.m_pComponents[ i ] ) +
			overflow;

		if( overflow > 0 )
		{
			m_pComponents[ i ] = overflow & 0xFFFF;
		}
		else
		{
			m_pComponents[ i ] = 0;
			overflow = 0xFFFF + overflow;
		}

	}
*/
	return *this;
}

LargeInteger & LargeInteger::operator *= ( const LargeInteger & p_LargeInteger )
{
	return *this;
}

LargeInteger & LargeInteger::operator /= ( const LargeInteger & p_LargeInteger )
{
	return *this;
}

LargeInteger & LargeInteger::operator %= ( const LargeInteger & p_LargeInteger )
{
	return *this;
}

std::ostream & operator << ( std::ostream & os, const LargeInteger & p_LargeInteger )
{
	// a bad way of doing this probably but it's working for now.

	if( p_LargeInteger.m_Size == 0 )
	{
		os << "0";
		return os;
	}

	std::string buffer = "";

	for( int i = p_LargeInteger.m_Size - 1; i >= 0; i-- )
	{
		for( int j = (sizeof( unsigned short ) * 8) - 1; j >= 0; j-- )
		{
			bool bit = static_cast< bool >( CheckBit( p_LargeInteger.m_pComponents[ i ], j ) );
			
			// Add the bits to the buffer
			if( bit )
			{
				buffer += "1";
			}
			else
			{
				buffer += "0";
			}
		}
		buffer += " ";
	}

	
	os << buffer;
	return os;
}

/*
std::auto_ptr< LargeInteger > LargeInteger::operator + ( const LargeInteger & p_LargeInteger ) const
{
	//std::auto_ptr< LargeInteger > number( new LargeInteger(m_Size) );
	//LargeInteger number( m_Size );
	//number.Clear( );

	unsigned int overflow = 0;

	for( unsigned int i = 0; i < m_Size; i++ )
	{
		overflow = static_cast<unsigned int>( m_pComponents[ i ] ) +
			static_cast<unsigned int>( p_LargeInteger.m_pComponents[ i ] ) +
			overflow;

		//unsigned int a = overflow >> 16;
		//unsigned int b = overflow << 16;

		number.m_pComponents[ i ] = overflow & 0xFFFF;

		std::cout << number.m_pComponents[ i ] << std::endl;

		overflow = overflow >> 16;
	}

	//return number;
	return std::auto_ptr< LargeInteger >( new LargeInteger(m_Size) );
}*/

// Private functions
bool LargeInteger::Allocate( const unsigned int p_Size )
{
	if( p_Size == 0 )
	{
		return false;
	}

	// Make sure to delete the old allocated data if there are any.
	if( m_pComponents )
	{
		delete [ ] m_pComponents;
	}
	
	m_Size = p_Size;
	m_pComponents = new unsigned short[ p_Size ];

	return true;
}