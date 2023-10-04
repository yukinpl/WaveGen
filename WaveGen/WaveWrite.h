#pragma once

#include <fstream>

namespace Wave
{

enum class Endian : uint8_t
{
	Big    = 0 ,
	Little = 1 ,
} ;

void Write32Bit( std::ofstream & ofs , uint32_t const & val , Endian const & endian ) ;
void Write16Bit( std::ofstream & ofs , uint16_t const & val , Endian const & endian ) ;
void Write08Bit( std::ofstream & ofs , uint8_t  const & val ) ;

}