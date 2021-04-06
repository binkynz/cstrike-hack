#pragma once

#include "../client/base_animating.h"

struct base_view_model : public base_animating {

	inline auto update_all_viewmodel_addons( ) {

		auto function = m_signatures.m_update_all_viewmodel_addons.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_arm_models( ) {

		auto function = m_signatures.m_remove_viewmodel_arm_models.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_label( ) {

		auto function = m_signatures.m_remove_viewmodel_label.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_stat_track( ) {

		auto function = m_signatures.m_remove_viewmodel_stat_track.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_stickers( ) {

		auto function = m_signatures.m_remove_viewmodel_stickers.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

};