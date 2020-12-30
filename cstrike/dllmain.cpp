#include "cstrike.h"

BOOL APIENTRY DllMain( HMODULE module_handle, DWORD call_reason, LPVOID reserved ) {

	if ( call_reason == DLL_PROCESS_ATTACH ) {

		DisableThreadLibraryCalls( module_handle );

		return m_utils.create_thread( m_cstrike.setup, module_handle );

	} else if ( call_reason == DLL_PROCESS_DETACH ) {

		m_cstrike.unload( );

		return TRUE;

	}

	return FALSE;

}