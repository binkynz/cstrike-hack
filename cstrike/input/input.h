#pragma once

#include <array>

#include "../cstrike.h"

enum key_state {

	up,
	toggled,
	down

};

struct input {

	bool setup( );

	void unload( );

	void think( UINT message, WPARAM w_param, LPARAM l_param );

	inline bool is_key_toggled( std::size_t code ) {

		if ( m_key_states[ code ].m_state != toggled )
			return false;

		return m_key_states[ code ].m_framecount == m_interfaces.m_globals->m_framecount;

	}

	inline bool is_key_down( std::size_t code ) {

		return m_key_states[ code ].m_state == down;

	}

private:

	static long __stdcall wnd_proc( HWND window, UINT message, WPARAM w_param, LPARAM l_param );

	WNDPROC m_original_wnd_proc;

	struct key_states {

		key_state m_state;
		int m_framecount;

	};

	std::array< key_states, 256 > m_key_states = { up };

};

inline input m_input;