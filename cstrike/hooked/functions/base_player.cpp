#include "../hooked.h"

bool __fastcall hooked::functions::create_move( base_player* ecx, void* edx, float input_sample_time, user_cmd* cmd ) {

	static auto o_create_move = m_create_move.get< decltype( &create_move ) >( );

	m_cstrike.m_local_player = ecx;

	cmd->m_buttons |= in_bull_rush;

	return o_create_move( ecx, edx, input_sample_time, cmd );

}