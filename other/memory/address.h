#pragma once

struct address {

	address( ) : m_address{ } {



	}

	address( const std::size_t address ) : m_address{ address } {



	}

	address( const void* address ) : m_address{ reinterpret_cast< std::size_t >( address ) } {



	}

	inline operator std::size_t( ) {

		return m_address;

	}

	inline operator void* ( ) {

		return reinterpret_cast< void* >( m_address );

	}

	inline operator const void* ( ) {

		return reinterpret_cast< const void* >( m_address );

	}

	inline bool operator==( address address ) {

		return as< std::size_t >( ) == address.as< std::size_t >( );

	}

	inline bool operator!=( address address ) {

		return as< std::size_t >( ) != address.as< std::size_t >( );

	}

	template< typename t = address > inline t to( ) const {

		return *( t* )m_address;

	}

	template< typename t = address > inline t as( ) const {

		return m_address ? ( t )m_address : t( );

	}

	template< typename t = address > inline t at( const std::size_t offset ) const {

		return m_address ? *( t* )( m_address + offset ) : t( );

	}

	template< typename t = address > inline t add( const std::size_t offset ) const {

		return m_address ? ( t )( m_address + offset ) : t( );

	}

	template< typename t = address > inline t sub( const std::size_t offset ) const {

		return m_address ? ( t )( m_address - offset ) : t( );

	}

	template< typename t = address > inline t get( std::size_t dereferences = 1 ) const {

		if ( !m_address )
			return t( );

		std::size_t object = m_address;

		while ( dereferences-- )
			if ( object )
				object = *reinterpret_cast< std::size_t* >( object );

		return ( t )object;

	}

	template< typename t = std::size_t > inline void set( const t& value ) const {

		if ( !m_address )
			return;

		*( t* )m_address = value;

	}

	template< typename t = address > inline t relative( const std::size_t offset = 0x1 ) const {

		if ( !m_address )
			return t( );

		const std::size_t new_address = m_address + offset;

		// boris will gutter stomp you

		const std::int32_t relative_offset = *reinterpret_cast< std::int32_t* >( new_address );

		if ( !relative_offset )
			return t( );

		return ( t )( new_address + sizeof( std::size_t ) + relative_offset );

	}

private:

	std::size_t m_address;

};