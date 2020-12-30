#include "interfaces.h"

bool interfaces::setup( ) {

	m_console.log( "grabbing interfaces..." );

	m_client = get< base_client_dll* >( "client.dll", "VClient018" );

	if ( !m_client )
		return false;

	m_console.log( "grabbed interfaces" );

	return true;

}