#pragma once

struct global_vars_base {

	float m_realtime; // 0
	int m_framecount; // 4
	float m_absoluteframetime; // 8
	float m_absoluteframestarttime; // 12
	float m_curtime; // 16
	float m_frametime; // 20
	int m_max_clients; // 24
	int m_tickcount; // 28
	float m_interval_per_tick; // 32
	float m_interpolation_amount; // 36
	int m_sim_ticks_this_frame; // 40
	int m_network_protocol; // 44
	void* m_save_data; // 48
	bool m_client; // 52
	bool m_remote_client; // 53
	int m_time_stamp_networking_base; // 54
	int m_time_stamp_randomize_window; // 58

};