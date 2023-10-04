#include "pch.h"
#include "WaveWrite.h"

void Wave::Write32Bit( std::ofstream & ofs , uint32_t const & val , Endian const & endian )
{
	uint8_t buf[ 4 ] = { 0 , 0 , 0 , 0 } ;

	if( Endian::Big == endian )
	{
		buf[ 0 ] = ( val >> 24 ) & 0x000000FF ;
		buf[ 1 ] = ( val >> 16 ) & 0x000000FF ;
		buf[ 2 ] = ( val >>  8 ) & 0x000000FF ;
		buf[ 3 ] = ( val >>  0 ) & 0x000000FF ;
	}
	else
	{
		buf[ 0 ] = ( val >>  0 ) & 0x000000FF ;
		buf[ 1 ] = ( val >>  8 ) & 0x000000FF ;
		buf[ 2 ] = ( val >> 16 ) & 0x000000FF ;
		buf[ 3 ] = ( val >> 24 ) & 0x000000FF ;
	}

	ofs.write( reinterpret_cast< char const * >( buf ) , 4 ) ;
}


void Wave::Write16Bit( std::ofstream & ofs , uint16_t const & val , Endian const & endian )
{
	uint8_t buf[ 2 ] = { 0 , 0 } ;

	if( Endian::Big == endian )
	{
		buf[ 0 ] = ( val >> 8 ) & 0x000000FF ;
		buf[ 1 ] = ( val >> 0 ) & 0x000000FF ;
	}
	else
	{
		buf[ 0 ] = ( val >> 0 ) & 0x000000FF ;
		buf[ 1 ] = ( val >> 8 ) & 0x000000FF ;
	}

	ofs.write( reinterpret_cast< char const * >( buf ) , 2 ) ;
}


void Wave::Write08Bit( std::ofstream & ofs , uint8_t  const & val )
{
	ofs.write( reinterpret_cast< char const * >( val ) , 1 ) ;
}