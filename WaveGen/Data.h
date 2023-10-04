#pragma once

#include <fstream>



namespace Wave
{

class Data
{

private :
	uint32_t chunkId ;
	uint32_t chunkSize ;

public :
	Data() ;

	void SetChunkSize( uint32_t const & size ) ;

	void Write( std::ofstream & ofs ) ;

} ;

}