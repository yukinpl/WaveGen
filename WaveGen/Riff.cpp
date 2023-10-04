#include "pch.h"
#include "Riff.h"

#include "WaveWrite.h"


Wave::Riff::Riff()
	: chunkId( 0x52494646 ) /* RIFF */ , chunkSize( 0x00000000 ) , format( 0x57415645 ) /* WAVE */
{

}


void Wave::Riff::SetChunkSize( uint32_t const & size )
{
	chunkSize = size ;
}


void Wave::Riff::Write( std::ofstream & ofs )
{
	Write32Bit( ofs , chunkId   , Endian::Big    ) ;
	Write32Bit( ofs , chunkSize , Endian::Little ) ;
	Write32Bit( ofs , format    , Endian::Big    ) ;
}