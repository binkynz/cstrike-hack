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

	inline bool is_key_toggled( std::size_t code, bool& item ) {

		if ( is_key_toggled( code ) )
			item = !item;

		return item;

	}

	inline bool is_key_down( std::size_t code ) {

		return m_key_states[ code ].m_state == down;

	}

	inline bool is_mouse_down( std::size_t code ) {

		return m_key_states[ code ].m_state == toggled;

	}

	inline bool is_mouse_in_bounds( int x, int y, int width, int height ) {

		return m_mouse.x >= x && m_mouse.y >= y && m_mouse.x <= x + width && m_mouse.y <= y + height;

	}

	inline int get_last_key( ) {  return m_last_key; };
	inline void set_last_key( int key = -1 ) { m_last_key = key; };
	inline int get_mouse_x( ) { return m_mouse.x; }
	inline int get_mouse_y( ) { return m_mouse.y; }

private:

	static long __stdcall wnd_proc( HWND window, UINT message, WPARAM w_param, LPARAM l_param );

	WNDPROC m_original_wnd_proc;

	int m_last_key;

	struct {

		int x, y;

	} m_mouse;

	struct key_states {

		key_state m_state;
		int m_framecount;

	};

	std::array< key_states, 256 > m_key_states = { up };

};

inline input m_input;