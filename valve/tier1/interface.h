#pragma once

using instantiate_interface_fn = void* ( __cdecl* )( );

struct interface_reg {
public:

	instantiate_interface_fn m_create_function;
	const char* m_name;
	interface_reg* m_next;

};