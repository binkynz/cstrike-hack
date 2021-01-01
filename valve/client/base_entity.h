#pragma once

#include "../client_networkable.h"
#include "../client_renderable.h"

#include "../netvars/netvars.h"

struct base_entity {

	inline client_renderable* get_client_renderable( ) {

		return reinterpret_cast< client_renderable* >( reinterpret_cast< std::size_t >( this ) + 0x4 );

	}

	inline client_networkable* get_client_networkable( ) {

		return reinterpret_cast< client_networkable* >( reinterpret_cast< std::size_t >( this ) + 0x8 );

	}

	inline auto is_alive( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 155 )( this );

	}

	inline auto& get_origin( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_vecOrigin" ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_simulation_time( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_flSimulationTime" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_team( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_iTeamNum" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

};