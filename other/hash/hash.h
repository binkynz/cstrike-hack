#pragma once

#include <cstddef>

struct hash {

	std::size_t get( const char* string );

private:

	std::size_t m_basis = 0x8adf9ed5;
	std::size_t m_prime = 0x60561129;

};

inline hash m_hash;