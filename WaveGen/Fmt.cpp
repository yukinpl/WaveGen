#include "pch.h"
#include "Fmt.h"

#include "WaveWrite.h"


Wave::Fmt::Fmt()
	: chunkId( 0x666D7420 ) /* "fmt " */ , chunkSize( 0x00000010 ) /* 16 */ , audioFormat( 0x0001 ) /* PCM */ , 
	  numChannels( 0x0000 ) , sampleRate( 0x00000000 ) , byteRate( 0x00000000 ) , blockAlign( 0x0000 ) , bps( 0x0000 )
{

}


void Wave::Fmt::SetNumbersOfChannel( uint16_t const & chNo )
{
	numChannels = chNo ;
}


void Wave::Fmt::SetSampleRate( uint32_t const & rate )
{
	sampleRate = rate ;
}


void Wave::Fmt::SetByteRate( uint32_t const & rate )
{
	byteRate = rate ;
}


void Wave::Fmt::SetSizeOfSampleFrame( uint16_t const & size )
{
	blockAlign = size ;
}


void Wave::Fmt::SetBitDepth( uint16_t const & depth )
{
	bps = depth ;
}


void Wave::Fmt::Write( std::ofstream & ofs )
{
	Write32Bit( ofs , chunkId     , Endian::Big    ) ;
	Write32Bit( ofs , chunkSize   , Endian::Little ) ;
	Write16Bit( ofs , audioFormat , Endian::Little ) ;
	Write16Bit( ofs , numChannels , Endian::Little ) ;
	Write32Bit( ofs , sampleRate  , Endian::Little ) ;
	Write32Bit( ofs , byteRate    , Endian::Little ) ;
	Write16Bit( ofs , blockAlign  , Endian::Little ) ;
	Write16Bit( ofs , bps         , Endian::Little ) ;
}