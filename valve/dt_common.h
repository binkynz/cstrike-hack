#pragma once

enum send_prop_type {

	dpt_int = 0,
	dpt_float,
	dpt_vector,
	dpt_string,
	dpt_array,
	dpt_datatable

};

struct d_variant {

	union {

		float m_float;
		long m_int;
		char* m_string;
		void* m_data;
		float m_vector[ 3 ];
		long long m_int_64;

	};

	send_prop_type m_type;

};