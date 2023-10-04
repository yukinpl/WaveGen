#include "pch.h"
#include "Wav.h"


Wave::Wav::Wav()
	: rawDataSize( 0 )
{

}


void Wave::Wav::SetRawDataSize( uint32_t const & size )
{
	data.SetChunkSize( size ) ;
	riff.SetChunkSize( size + 36 ) ;
}


void Wave::Wav::Write( std::ofstream & ofs )
{
	riff.Write( ofs ) ;
	 fmt.Write( ofs ) ;
	data.Write( ofs ) ;
}


void Wave::Wav::SetNumbersOfChannel( uint16_t const & chNo )
{
	fmt.SetNumbersOfChannel( chNo ) ;
}


void Wave::Wav::SetSampleRate( uint32_t const & rate )
{
	fmt.SetSampleRate( rate ) ;
}


void Wave::Wav::SetByteRate( uint32_t const & rate )
{
	fmt.SetByteRate( rate ) ;
}


void Wave::Wav::SetSizeOfSampleFrame( uint16_t const & size )
{
	fmt.SetSizeOfSampleFrame( size ) ;
}


void Wave::Wav::SetBitDepth( uint16_t const & depth )
{
	fmt.SetBitDepth( depth ) ;
}