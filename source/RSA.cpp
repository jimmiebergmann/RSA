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

#include "RSA.hpp"
#include <stdlib.h>
#include <cmath>

///////////////////////////////////////////////////////////////////////////////////
// General functions used that's being defined on the bottom of this file
//LargeInteger PowMod( LargeInteger base, LargeInteger exponent, LargeInteger modulus );
unsigned int RandomNumber( unsigned int min, unsigned int max );
bool RandomPrime( LargeInteger & p_Prime );
/*unsigned int EuclideanAlgorithm ( unsigned int a, unsigned int b ); // Euclid's algorithm
*/bool IsPrime( LargeInteger & p_Number );


// Constructors
RSA::RSA( const unsigned int p_Size ) :
	m_Initialized( true ),
	m_Size( p_Size )
{
	m_e = LargeInteger( p_Size );
	m_d = LargeInteger( p_Size );
	m_p = LargeInteger( p_Size );
	m_q = LargeInteger( p_Size );
	m_n = LargeInteger( p_Size );
	m_z = LargeInteger( p_Size );
}

RSA::RSA( const unsigned int p_Size, const LargeInteger & p_e, const LargeInteger & p_d,
	const LargeInteger & p_n ) :
	m_Initialized( false )
{
	// Make sure the numbers are of the same size
	// We should cosider adding auto-resize here in some way.
	if( p_e.GetSize( ) != p_Size || p_d.GetSize( ) != p_Size ||
		p_n.GetSize( ) != p_Size )
	{
		return;
	}

	m_e = p_e;
	m_d = p_d;
	m_p = LargeInteger( p_Size );
	m_q = LargeInteger( p_Size );
	m_n = p_n;
	m_z = LargeInteger( p_Size );
	m_Initialized = true;
}

RSA::RSA( const unsigned int p_Size, const LargeInteger & p_e, const LargeInteger & p_d,
	const LargeInteger & p_n, const LargeInteger & p_z ) :
	m_Initialized( false )
{
	// Make sure the numbers are of the same size
	// We should cosider adding auto-resize here in some way.
	if( p_e.GetSize( ) != p_Size || p_d.GetSize( ) != p_Size ||
		p_n.GetSize( ) != p_Size || p_z.GetSize( ) != p_Size )
	{
		return;
	}

	m_e = p_e;
	m_d = p_d;
	m_p = LargeInteger( p_Size );
	m_q = LargeInteger( p_Size );
	m_n = p_n;
	m_z = p_z;
	m_Initialized = true;
}

// Initialization functions
bool RSA::RandomizeKeys( const unsigned int p_seed ) // Randomly generate the keys.
{
	// You have to seed the rand function by yourself if you're not
	// providing any seed.
	if( p_seed != 0 )
	{
		srand( p_seed );
	}

	// Set p and q by generating random primes.
	m_p.Clear( );
	m_q.Clear( );

	// Do start at 46341 since it's closest to the lowest possible 32 bit number
	// by any number multiplied by itself. 46341^2 almost equals to the lowest 32 bit number...
	//unsigned int prime_range_low = 46341; //32768;
	//unsigned int prime_range_high = 65535;

	// Make sure that they're not equal to each other.
	while( m_p == m_q || !m_p || !m_q )
	{
		RandomPrime( m_p );
		RandomPrime( m_q );
	}
/*
	// Calculate n, z, e and d by using two primes: p and q. Simple? :)
	if( !CalculateNZED( m_p, m_q ) )
	{	
		return false;
	}
*/
	return true;
}

// Set functions
void RSA::SetE( const LargeInteger & p_e )
{
	m_e = p_e;
}

void RSA::SetD( const LargeInteger & p_d )
{
	m_d = p_d;
}

void RSA::SetP( const LargeInteger & p_p )
{
	m_p = p_p;
}

void RSA::SetQ( const LargeInteger & p_q )
{
	m_q = p_q;
}

void RSA::SetN( const LargeInteger & p_n )
{
	m_n = p_n;
}

void RSA::SetZ( const LargeInteger & p_z )
{
	m_z = p_z;
}

// Get functions
LargeInteger RSA::GetE( ) const
{
	return LargeInteger( m_e );
}

LargeInteger RSA::GetD( ) const
{
	return LargeInteger( m_d );
}

LargeInteger RSA::GetP( ) const
{
	return LargeInteger( m_p );
}

LargeInteger RSA::GetQ( ) const
{
	return LargeInteger( m_q );
}

LargeInteger RSA::GetN( ) const
{
	return LargeInteger( m_n );
}

LargeInteger RSA::GetZ( ) const
{
	return LargeInteger( m_z );
}


///////////////////////////////////////////////////////////////////////////////////
// General functions used that's being defined on the bottom of this file
/*LargeInteger PowMod( LargeInteger base, LargeInteger exponent, LargeInteger modulus )
{
	// Resource:
	// http://en.wikipedia.org/wiki/Modular_exponentiation

	if( base < 1 || exponent < 0 || modulus < 1 )
	{
		return 0;
	}
/*
	// use 64 bit integers to make sure we're not getting out of range.
	unsigned __int64 result = 1;
	unsigned __int64 new_base = base;
	unsigned __int64 new_exponent = exponent;
	unsigned __int64 new_modulus = modulus;

	// Keep on looping until the exponent which is being divided
	// every single loop is larger than 0.
	while( new_exponent > 0 )
	{
		if( ( new_exponent % 2 ) == 1 )
		{
			result = ( result * new_base ) % new_modulus;
		}

		new_exponent = new_exponent >> 1;
		new_base = ( new_base * new_base ) % new_modulus;
	}

	// return the result as an unsigned int.
	return static_cast< unsigned int >( result );*/
	//return 
//}*/

unsigned int RandomNumber( unsigned int min, unsigned int max )
{
	return ( rand( ) % ( max - ( min - 1 ) ) ) + min;
}

bool RandomPrime( LargeInteger & p_Prime )
{
	// Error check the param value
	if( p_Prime.GetSize( ) == 0 )
	{
		return false;
	}

	// Randomize the first component, The last bit should be 1 and therefore,
	// we use the value 128 as the start value
	// We use the end value 254 because we don't want to overflow
	p_Prime.SetComponent( 0, RandomNumber( 128, 254 ) );

	// Randomly set the other ones
	for( unsigned int i = 1; i < p_Prime.GetSize( ); i++ )
	{
		p_Prime.SetComponent( i, RandomNumber( 0, 255 ) );
	}

	// Make the large integer odd
	if( p_Prime % (unsigned short)( 2 ) )
	{
		p_Prime++;
	}

	// Keep on looping until we find a prime
	// NOT SAFE
	while( 1 )
	{
		if( IsPrime( p_Prime ) )
		{
			return true;
		}

		p_Prime += 2;
	}

	// We did not find any prime.
	return false;
}

bool IsPrime( LargeInteger & p_Number )
{

	// Resource:
	// http://holmezideas.com/programming/optimization-techniques/fastest-algorithm-to-check-if-a-given-number-is-prime/

	if( p_Number <= (unsigned short)( 1 ) )
	{
		return false;
	}
	else if( p_Number == (unsigned short)( 2 ) )
	{
		return true;
	}
	else if( ( p_Number % (unsigned short)( 2 ) ) == 0 )
	{
		return false;
	}
	else
	{
		//float square_root = sqrt( static_cast< float >( number ) );
		LargeInteger square_root( p_Number.GetSize( ) / 2 );
		square_root = p_Number.Sqrt( );

		// Let's loop sqrt( number ) times and check if the number isn't a prime
		for( unsigned int i = 3; i <= square_root; i+=2 )
		{
			if( ( p_Number % (unsigned short)( i ) ) == 0 )
			{
				return false;
			}
		}
	}

	return true;
}