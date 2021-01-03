#pragma once

#include "address.h"

struct stack : address {

	stack( void* address_of_return_address ) : address( m_utils.get_ebp( address_of_return_address ) ) {



	}

	inline stack& next( ) {

		return *reinterpret_cast< stack* >( m_address );

	}

	template< typename t = address > inline t local( std::size_t offset ) {

		return ( t )( m_address - offset );

	}

	template< typename t = address > inline t argument( std::size_t offset ) {

		return ( t )( m_address + offset );

	}

	inline address return_address( ) {

		if ( !m_address )
			return address( );

		return *reinterpret_cast< std::size_t* >( m_address + sizeof( std::size_t ) );

	}

	inline address address_of_return_address( ) {

		if ( !m_address )
			return address( );

		return m_address + sizeof( std::size_t );

	}

};