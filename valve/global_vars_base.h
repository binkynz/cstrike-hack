#pragma once

struct global_vars_base {

	float m_realtime;
	int m_framecount;
	float m_absoluteframetime;
	float m_absoluteframestarttime;
	float m_curtime;
	float m_frametime;
	int m_max_clients;
	int m_tickcount;
	float m_interval_per_tick;
	float m_interpolation_amount;
	int m_sim_ticks_this_frame;
	int m_network_protocol;
	void* m_save_data;
	bool m_client;
	bool m_remote_client;
	int m_time_stamp_networking_base;
	int m_time_stamp_randomize_window;

};