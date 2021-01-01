#pragma once

struct client_entity_list {

	inline auto get_client_entity( int entity_number ) {

		return m_utils.get_v_func< void* ( __thiscall* )( void*, int ) >( this, 3 )( this, entity_number );

	}

	template< class t > inline t get( int entity_number ) {

		return ( t )get_client_entity( entity_number );

	}

};