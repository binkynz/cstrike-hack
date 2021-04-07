#include "../hooked.h"

struct cl_msg_move {

	cl_msg_move( ) {

		m_net_message_vtable = m_modules.m_engine_dll.get_address( "CL_SendMove" ).add( 0x76 ).to< std::size_t >( );
		m_cl_msg_move_vtable = m_modules.m_engine_dll.get_address( "CL_SendMove" ).add( 0x82 ).to< std::size_t >( );
		m_allocated_memory = m_modules.m_engine_dll.get_address( "CL_SendMove" ).add( 0x7b ).to< void* >( );

		m_unknown = 15;

		m_flags = 3;

		m_unknown1 = 0;
		m_unknown2 = 0;
		m_unknown3 = 0;
		m_unknown4 = 0;
		m_unknown5 = 0;

	}

	~cl_msg_move( ) {

		static auto function = m_modules.m_engine_dll.get_address( "CCLCMsg_Move::Deconstuctor" ).as< void( __thiscall* )( void* ) >( );

		function( this );

	}

	inline auto set_num_backup_commands( int backup_commands ) {

		m_backup_commands = backup_commands;

	}

	inline auto set_num_new_commands( int new_commands ) {

		m_new_commands = new_commands;

	}

	inline auto set_data( unsigned char* data, int num_bytes_written ) {

		m_flags |= 4;

		if ( m_allocated_memory == m_modules.m_engine_dll.get_address( "CL_SendMove" ).add( 0x7b ).to< void* >( ) ) {

			address new_memory = address( m_interfaces.m_mem_alloc->alloc( 24 ) );
			if ( new_memory ) {

				new_memory.add( 0x14 ).set( 15 );
				new_memory.add( 0x10 ).set( 0 );
				new_memory.set< unsigned char >( 0 );

			}

			m_allocated_memory = new_memory;

		}

		static auto function = m_modules.m_engine_dll.get_address( "CCLCMsg_Move::set_data" ).as< void* ( __thiscall* )( void*, unsigned char*, std::size_t ) >( );

		return function( m_allocated_memory, data, num_bytes_written );

	}

	int m_net_message_vtable; // 0x58
	int m_cl_msg_move_vtable; // 0x54
	int m_unknown1; // 0x4c
	int m_backup_commands; // 0x4c
	int m_new_commands; // 0x48
	void* m_allocated_memory; // 0x44
	int m_unknown2; // 0x40
	int m_flags; // 0x3c
	char m_unknown3; // 0x38
	char _pad0[ 0x3 ]; // 0x37
	char m_unknown4; // 0x34
	char _pad1[ 0xf ]; // 0x33
	int m_unknown5; // 0x24
	int m_unknown; // 0x20
	bf_write m_data_out; // 0x1c

};

void __cdecl hooked::cl_main_fn::cl_send_move( ) {

	// gtfo with the split screen bullshit

	int nextcommandnr = m_interfaces.m_client_state->m_lastoutgoingcommand + m_interfaces.m_client_state->m_chokedcommands + 1;
	int choked_commands = m_interfaces.m_client_state->m_chokedcommands;

	byte data[ 4000 /* MAX_CMD_BUFFER */ ];
	cl_msg_move move_msg;

	move_msg.m_data_out.start_writing( data, sizeof( data ) );

	int cl_cmdbackup = 2;
	int backup_commands = std::clamp( cl_cmdbackup, 0, 7 /* MAX_BACKUP_COMMANDS */ );

	int new_commands = std::clamp( choked_commands + 1, 0, 15 /* MAX_NEW_COMMANDS */ );

	move_msg.set_num_backup_commands( backup_commands );
	move_msg.set_num_new_commands( new_commands );

	int numcmds = new_commands + backup_commands;
	int from = -1;
	bool ok = true;

	for ( int to = nextcommandnr - numcmds + 1; to <= nextcommandnr; ++to ) {

		bool isnewcmd = to >= ( nextcommandnr - new_commands + 1 );

		ok = ok && m_interfaces.m_client->write_usercmd_delta_to_buffer( 0, &move_msg.m_data_out, from, to, isnewcmd );
		from = to;

	}

	if ( ok ) {

		move_msg.set_data( move_msg.m_data_out.get_data( ), move_msg.m_data_out.get_num_bytes_written( ) );

		m_interfaces.m_client_state->m_net_channel->send_net_msg( &move_msg );

	}

}