#pragma once

#include "dt_common.h"

struct recv_table;
struct recv_prop;

struct recv_proxy_data {

	const recv_prop* m_recv_prop;
	d_variant m_value;
	int m_element;
	int m_object_id;

};

using array_length_recv_proxy = void( __cdecl* )( void* ptr, int id, int len );
using recv_var_proxy = void( __cdecl* )( recv_proxy_data* data, void* struct_ptr, void* out );
using data_table_recv_var_proxy = void( __cdecl* )( recv_prop* prop, void** out, void* data, int id );

struct recv_prop {

	char* m_var_name;
	int m_recv_type;
	int m_flags;
	int m_string_buffer_size;
	bool m_inside_array;
	const void* m_extra_data;
	recv_prop* m_array_prop;
	array_length_recv_proxy m_array_length_proxy;
	recv_var_proxy m_proxy_function;
	data_table_recv_var_proxy m_data_table_proxy_function;
	recv_table* m_data_table;
	int m_offset;
	int m_element_stride;
	int m_elements;
	const char* m_parent_array_prop_name;

};

struct recv_table {

	recv_prop* m_props_pointer;
	int m_props;
	void* m_decoder;
	char* m_net_table_name;
	bool m_initialized;
	bool m_in_main_list;

};