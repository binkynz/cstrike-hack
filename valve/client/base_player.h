#pragma once

#include "base_combat_character.h"

struct user_cmd;
struct base_view_model;

struct base_player : base_combat_character {

	inline auto& get_health( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BasePlayer->m_iHealth" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto* get_pose_parameter( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flPoseParameter" ) ];

		return reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_sequence( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BasePlayer->m_nSequence" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto create_move( float input_sample_time, user_cmd* cmd ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, float, user_cmd* ) >( this, 288 )( this, input_sample_time, cmd );

	}

	inline auto is_local_player( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BasePlayer::IsLocalPlayer" ).as< bool( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto util_player_by_index( int entindex ) {

		static auto function = m_modules.m_server_dll.get_address( "UTIL_PlayerByIndex" ).as< base_player* ( __thiscall* )( int ) >( );

		return function( entindex );

	}

	inline auto get_view_model( int index ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BasePlayer::GetViewModel" ).as< base_view_model* ( __thiscall* )( void*, int ) >( );

		return function( this, index );

	}

};