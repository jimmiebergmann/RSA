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

// Constructors
RSA::RSA( )
{
}

RSA::RSA( const LargeInteger & p_e, const LargeInteger & p_d, const LargeInteger & p_n ) :
	m_e( p_e ),
	m_d( p_d ),
	m_n( p_n )
{
}

RSA::RSA( const LargeInteger & p_e, const LargeInteger & p_d,
	const LargeInteger & p_n, const LargeInteger & p_z ) :
	m_e( p_e ),
	m_d( p_d ),
	m_n( p_n ),
	m_z( p_z )
{
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
