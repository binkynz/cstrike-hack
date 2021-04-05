#pragma once

struct net_channel;

struct client_state {

	char _pad0[ 0x9c ]; // 0
	net_channel* m_net_channel; // 156
	char _pad1[ 0x4c8c ]; // 160
	int m_lastoutgoingcommand; // 19756
	int m_chokedcommands; // 19760

};