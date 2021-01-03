#include "utils.h"

bool utils::create_thread( DWORD WINAPI function( void* ), void* parameter ) {

	HANDLE handle = CreateThread( NULL, 0, function, parameter, 0, NULL );

	if ( !handle )
		return false;

	CloseHandle( handle );

	return true;

}