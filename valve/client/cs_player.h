#pragma once

#include "base_animating.h"

struct csgo_player_anim_state;

struct cs_player : base_animating {

	inline auto& is_player_ghost( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bIsPlayerGhost" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_third_person_recoil( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flThirdpersonRecoil" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_duck_amount( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flDuckAmount" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_playback_rate( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flPlaybackRate" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_cycle( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flCycle" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_lower_body_yaw_target( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flLowerBodyYawTarget" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_eye_angles( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_angEyeAngles" ) ];

		return *reinterpret_cast< q_angle* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_killed_by_taser( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bKilledByTaser" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto get_player_anim_state_csgo( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_CSPlayer->m_PlayerAnimStateCSGO" ).add( 0x2 ).to< std::size_t >( );

		return *reinterpret_cast< csgo_player_anim_state** >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto& get_use_new_animstate( ) {

		static auto offset = m_modules.m_client_dll.get_address( "C_CSPlayer->m_bUseNewAnimstate" ).add( 0x2 ).to< std::size_t >( );

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto eye_angles( ) {

		return m_utils.get_v_func< q_angle& ( __thiscall* )( void* ) >( this, 169 )( this );

	}

	inline auto handle_taser_animation( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_CSPlayer::HandleTaserAnimation" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

};