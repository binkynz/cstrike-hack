#include "hooked.h"

bool hooked::setup( ) {

	m_console.log( "hooking functions...\n\n" );

	m_console.log( "C_BasePlayer::CreateMove" );
	if ( !m_create_move.hook( m_pattern.find( "client.dll", "E8 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 29" ).relative( ), &functions::create_move ) )
		return false;

	m_console.log( "\n\nhooked functions" );

	return true;

}

void hooked::unload( ) {

	m_create_move.unload( );

}