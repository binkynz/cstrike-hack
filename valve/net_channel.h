#pragma once

struct net_channel {

	inline auto send_net_msg( void* msg, bool force_reliable = false, bool voice = false ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, void*, bool, bool ) >( this, 40 )( this, msg, force_reliable, voice );

	}

};