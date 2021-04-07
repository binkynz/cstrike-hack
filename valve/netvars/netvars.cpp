#include "netvars.h"

#include "../interfaces/interfaces.h"

#include "../../other/console/console.h"
#include "../../other/hash/hash.h"

bool netvars::setup( ) {

	auto list = m_interfaces.m_client->get_all_classes( );

	if ( !list )
		return false;

	m_file.open( "netvars.txt", std::ios::out | std::ios::trunc );

	while ( list != nullptr ) {

		store( list->m_recv_table->m_net_table_name, list->m_recv_table );

		list = list->m_next;

	}

	m_file.close( );

	m_console.log( "dumped netvars in CSGO directory" );

	return true;

}

void netvars::store( std::string_view name, recv_table* table, std::size_t offset ) {

	for ( auto i = 0; i < table->m_props; ++i ) {

		recv_prop* prop = &table->m_props_pointer[ i ];
		recv_table* child = prop->m_data_table;

		if ( child && child->m_props > 0 )
			store( name, child, prop->m_offset + offset );

		auto variable = prop->m_var_name;

		std::string netvar = std::string( name.data( ) ) + "->" + variable;
		std::size_t hash = m_hash.get( netvar );

		if ( !m_offsets[ hash ] ) {

			m_offsets[ hash ] = prop->m_offset + offset;

			m_file << netvar << " = 0x" << std::hex << m_offsets[ hash ] << std::endl;

		}

	}

}