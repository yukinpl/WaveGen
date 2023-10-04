#pragma once


#include <fstream>


namespace Wave
{

class Riff
{

private :
	uint32_t chunkId   ;
	uint32_t chunkSize ;
	uint32_t format    ;

public :
	Riff() ;

	void SetChunkSize( uint32_t const & size ) ;
	void Write( std::ofstream & ofs ) ;
} ;

} // namespace Wave