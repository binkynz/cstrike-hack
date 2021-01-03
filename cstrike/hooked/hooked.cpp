#include "hooked.h"

bool hooked::setup( ) {

	m_console.log( "hooking functions..." );

	m_detour.setup( "C_BasePlayer::CreateMove", m_pattern.find( "client.dll", "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ).relative( ), &create_move );

	m_detour.setup( "C_EngineVGui::Paint", m_pattern.find( "engine.dll", "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" ), &paint );

	m_detour.setup( "ClientModeShared::GetViewModelFOV", m_pattern.find( "client.dll", "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" ), &get_view_model_fov );

	m_detour.setup( "C_BaseEntity::ShouldInterpolate", m_pattern.find( "client.dll", "A1 ? ? ? ? 56 57 8B F9 8B 30 8D 4F 08" ), &should_interpolate );

	m_detour.setup( "C_WeaponCSBase::DrawCrosshair", m_pattern.find( "client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" ), &draw_crosshair );

	m_console.log( "hooked functions" );

	return true;

}

void hooked::unload( ) {

	m_detour.unload( );

}