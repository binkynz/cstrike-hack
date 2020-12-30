#pragma once

#include <windows.h>
#include <string>

struct console {

	bool setup( const std::string_view name );

	void unload( );

	void log( const std::string_view format, ... );

private:

	HANDLE m_handle;

	char m_buffer[ 256 ];

};

inline console m_console;