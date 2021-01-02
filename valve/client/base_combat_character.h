#pragma once

#include "base_entity.h"

struct base_combat_character : base_entity {

	inline auto& get_active_weapon( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseCombatCharacter->m_hActiveWeapon" ) ];

		return *reinterpret_cast< std::size_t* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

};