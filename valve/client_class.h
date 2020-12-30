#pragma once

#include "dt_recv.h"

using create_client_class = void* ( __cdecl* )( int index, int serial );
using create_event = void* ( __cdecl* )( );

struct client_class {

	create_client_class m_create;
	create_event m_create_event;
	char* m_network_name;
	recv_table* m_recv_table;
	client_class* m_next;
	int m_class_id;

};