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

	inline auto on_latch_interpolated_variables( int flags ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int ) >( this, 107 )( this, flags );

	}

	inline auto is_alive( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 155 )( this );

	}

	inline auto is_player( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 157 )( this );

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

	inline auto calc_absolute_velocity( ) { // grr

		static auto function = m_modules.m_client_dll.get_address( "C_BaseEntity::CalcAbsoluteVelocity" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto& get_abs_velocity( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BaseEntity->m_vecAbsVelocity" ).add( 0x4 ).to< std::size_t >( );

		calc_absolute_velocity( );

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	// note - seems to be crashing, but base version also crashes for me so i'll leave it to sean to fix
	// ...
	// sean: doesnt crash for me?
	inline auto get_anim_overlay( int i ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BaseEntity->m_nAnimOverlay" ).add( 0x2 ).to< std::size_t >( );

		return reinterpret_cast< animation_layer* >( i * 0x38 + *reinterpret_cast< std::size_t* >( reinterpret_cast< std::size_t >( this ) + offset ) );

	}

	inline auto get_ground_entity( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseEntity::GetGroundEntity" ).as< base_entity* ( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto invalidate_physics_recursive( int change_flags ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseEntity::InvalidatePhysicsRecursive" ).as< void( __thiscall* )( void*, int ) >( );

		return function( this, change_flags );

	}

	inline auto set_abs_angles( const q_angle& angles ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseEntity::SetAbsAngles" ).as< void( __thiscall* )( void*, const q_angle& ) >( );

		return function( this, angles );

	}

};