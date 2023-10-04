#pragma once


#include <fstream>


namespace Wave
{

class Fmt
{

private :
	uint32_t chunkId ;
	uint32_t chunkSize ;
	uint16_t audioFormat ;
	uint16_t numChannels ;
	uint32_t sampleRate ;
	uint32_t byteRate ;
	uint16_t blockAlign ;
	uint16_t bps ;

public :
	Fmt() ;

	void SetNumbersOfChannel( uint16_t const & chNo ) ;
	void SetSampleRate( uint32_t const & rate ) ;
	void SetByteRate( uint32_t const & rate ) ;
	void SetSizeOfSampleFrame( uint16_t const & size ) ;
	void SetBitDepth( uint16_t const & depth ) ;

	void Write( std::ofstream & ofs ) ;

} ;

} // namespace Wave