#include "hooked.h"

bool hooked::setup( ) {

	m_console.log( "hooking functions..." );

	m_console.log( "C_BasePlayer::CreateMove" );
	if ( !m_create_move.hook( m_pattern.find( "client.dll", "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ).relative( ), &functions::create_move ) )
		return false;

	m_console.log( "C_EngineVGui::Paint" );
	if ( !m_paint.hook( m_pattern.find( "engine.dll", "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" ), &functions::paint ) )
		return false;

	m_console.log( "hooked functions" );

	return true;

}

void hooked::unload( ) {

	m_create_move.unload( );
	m_paint.unload( );

}