#pragma once

#include "Riff.h"
#include "Fmt.h"
#include "Data.h"

#include <fstream>


namespace Wave
{


class Wav
{

private :
	Riff riff ;
	Fmt  fmt  ;
	Data data ;

	uint32_t rawDataSize ; 

public :
	Wav() ;

	void SetNumbersOfChannel( uint16_t const & chNo ) ;
	void SetSampleRate( uint32_t const & rate ) ;
	void SetByteRate( uint32_t const & rate ) ;
	void SetSizeOfSampleFrame( uint16_t const & size ) ;
	void SetBitDepth( uint16_t const & depth ) ;

	void SetRawDataSize( uint32_t const & size ) ;

	void Write( std::ofstream & ofs ) ;

} ;


} // namespace Wave