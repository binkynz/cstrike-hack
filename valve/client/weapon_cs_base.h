#pragma once

#include "base_entity.h"

struct cs_weapon_info {

	char _pad0[ 0x14 ]; // 0
	int m_max_clip1; // 20
	char _pad1[ 0x70 ]; // 24
	const char* m_hud_name; // 136
	char _pad2[ 0x3c ]; // 140
	int m_weapon_type; // 200

};

struct weapon_cs_base : base_entity {

	inline auto& get_ammo( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_WeaponCSBase->m_iClip1" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	inline auto get_max_speed( ) {

		return m_utils.get_v_func< float( __thiscall* )( void* ) >( this, 441 )( this );

	}

	inline auto get_cs_wpn_data( ) {

		return m_utils.get_v_func< cs_weapon_info* ( __thiscall* )( void* ) >( this, 460 )( this ); // 8B 81 ? ? ? ? 85 C0 0F 84 ? ? ? ? C3

	}

};