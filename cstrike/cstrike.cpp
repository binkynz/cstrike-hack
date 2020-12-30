#include "cstrike.h"

#include "hooked/hooked.h"

DWORD WINAPI cstrike::setup( void* parameter ) {

	const auto handle = static_cast< HMODULE >( parameter );

	m_console.setup( "cstrike-hack" );

	if ( !hooked::setup( ) ) {

		FreeLibraryAndExitThread( handle, EXIT_FAILURE );

		return EXIT_FAILURE;

	}

	while ( !GetAsyncKeyState( VK_DELETE ) )
		m_utils.sleep( 100 );

	FreeLibraryAndExitThread( handle, EXIT_SUCCESS );

	return EXIT_SUCCESS;

}

void cstrike::unload( ) {

	hooked::unload( );

	m_console.unload( );

	Beep( 400, 400 );

}