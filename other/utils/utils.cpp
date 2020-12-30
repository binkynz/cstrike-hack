#include "utils.h"

bool utils::create_thread( DWORD WINAPI function( void* ), void* parameter ) {

	const auto handle = CreateThread( NULL, 0, function, parameter, 0, NULL );

	if ( !handle )
		return false;

	CloseHandle( handle );

	return true;

}