#pragma once

#include "base_combat_character.h"

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

	inline auto& get_tick_base( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BasePlayer->m_nTickBase" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_next_think_tick( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BasePlayer->m_nNextThinkTick" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_current_command( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_LastCmd" ).add( 0xc ).to< std::size_t >( );

		return *reinterpret_cast< user_cmd** >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_last_command( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_LastCmd" ).add( 0x2 ).to< std::size_t >( );

		return *reinterpret_cast< user_cmd* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_forced( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonForced" ).add( 0x2 ).to< std::size_t >( );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_disabled( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonForced" ).add( 0x2 ).to( ).sub< std::size_t >( 0x4 );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_last( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonLast" ).add( 0x4 ).to< std::size_t >( );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_pressed( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonLast" ).add( 0x4 ).to( ).add< std::size_t >( 0x4 );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_button_released( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonLast" ).add( 0x4 ).to( ).add< std::size_t >( 0x8 );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_buttons( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonLast" ).add( 0x4 ).to( ).add< std::size_t >( 0xc );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_impulse( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_BasePlayer->m_afButtonLast" ).add( 0x4 ).to( ).add< std::size_t >( 0x10 );

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto create_move( float input_sample_time, user_cmd* cmd ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, float, user_cmd* ) >( this, 288 )( this, input_sample_time, cmd );

	}

	inline auto pre_think( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 317 )( this );

	}

	inline auto post_think( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 318 )( this );

	}

	inline auto select_item( const char* str, int sub_type ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, const char*, int ) >( this, 329 )( this, str, sub_type );

	}

	inline auto set_local_view_angles( const q_angle& view_angles ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, const q_angle& ) >( this, 372 )( this, view_angles );

	}

	inline auto is_local_player( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BasePlayer::IsLocalPlayer" ).as< bool( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto get_view_model( int index ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BasePlayer::GetViewModel" ).as< base_view_model* ( __thiscall* )( void*, int ) >( );

		return function( this, index );

	}

	inline auto util_player_by_index( int entindex ) {

		static auto function = m_modules.m_server_dll.get_address( "UTIL_PlayerByIndex" ).as< base_player* ( __thiscall* )( int ) >( );

		return function( entindex );

	}

	inline auto update_button_state( int user_cmd_button_mask ) {

		get_button_last( ) = get_buttons( );

		get_buttons( ) = user_cmd_button_mask;
		int buttons_changed = get_button_last( ) ^ get_buttons( );

		get_button_pressed( ) = buttons_changed & get_buttons( );
		get_button_released( ) = buttons_changed & ( ~get_buttons( ) );

	}

};