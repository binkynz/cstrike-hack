#include "hooked.h"

bool hooked::setup( ) {

	m_console.log( "hooking functions..." );

	m_detour.setup( "C_BasePlayer::CreateMove", m_pattern.find( "client.dll", "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ).relative( ), &create_move );

	m_detour.setup( "C_EngineVGui::Paint", m_pattern.find( "engine.dll", "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" ), &paint );

	m_console.log( "hooked functions" );

	return true;

}

void hooked::unload( ) {

	m_detour.unload( );

}