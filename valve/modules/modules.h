#pragma once

#include "../../other/pe/pe.h"

struct modules {

	bool setup( );

	loaded_module m_client_dll;
	loaded_module m_engine_dll;
	loaded_module m_server_dll;
	loaded_module m_gameoverlayrenderer_dll;
	loaded_module m_vgui2_dll;
	loaded_module m_vguimatsurface_dll;
	loaded_module m_studiorender_dll;
	loaded_module m_localize_dll;
	loaded_module m_datacache_dll;
	loaded_module m_materialsystem_dll;
	loaded_module m_tier0;

private:

	bool get( );

	void get_addresses( );

	bool got_addresses( );

};

inline modules m_modules;