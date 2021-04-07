#pragma once

#include "../client/base_animating.h"

struct base_view_model : public base_animating {

	inline auto update_all_viewmodel_addons( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseViewModel::UpdateAllViewmodelAddons" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_arm_models( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseViewModel::RemoveViewmodelArmModels" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_label( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseViewModel::RemoveViewmodelLabel" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_stat_track( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseViewModel::RemoveViewmodelStatTrak" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto remove_viewmodel_stickers( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseViewModel::RemoveViewmodelStickers" ).as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

};