#include "pch.h"
#include "Data.h"

#include "WaveWrite.h"


Wave::Data::Data()
	: chunkId( 0x64617461 ) , chunkSize( 0x00000000 )
{

}

void Wave::Data::SetChunkSize( uint32_t const & size )
{
	chunkSize = size ;
}


void Wave::Data::Write( std::ofstream & ofs )
{
	Write32Bit( ofs , chunkId   , Endian::Big    ) ;
	Write32Bit( ofs , chunkSize , Endian::Little ) ;
}