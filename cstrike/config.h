#pragma once

struct config {

	bool m_menu_open = true;

	struct {



	} m_legit;

	struct {



	} m_hvh;

	struct {

		bool active = true;
		bool player_box = true;
		bool player_health = true;
		bool player_name = true;
		bool player_weapon = true;

		bool chams = true;
		bool third_person = false;
		int thirdperson_key = 0x56;
		int thirdperson_distance = 100;

	} m_esp;

	struct {

		int viewmodel_fov = 90;

		bool server_hitboxes = false;

	} m_misc;

};

inline config m_config;