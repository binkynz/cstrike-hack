#pragma once

struct client_entity_list {

	inline auto get_client_entity( int entity_number ) {

		return m_utils.get_v_func< void* ( __thiscall* )( void*, int ) >( this, 3 )( this, entity_number );

	}

	inline auto get_client_entity_from_handle( std::size_t entity ) {

		return m_utils.get_v_func< void* ( __thiscall* )( void*, std::size_t ) >( this, 4 )( this, entity );

	}

	template< class t > inline t get( int entity_number ) {

		return ( t )get_client_entity( entity_number );

	}

	template< class t > inline t get( std::size_t entity ) {

		return ( t )get_client_entity_from_handle( entity );

	}

};