#pragma once

struct client_input {

	char _pad0[ 0xad ];
	bool m_camera_in_third_person;
	char _pad1[ 0x2 ];
	vector_3d m_camera_offset;
	char _pad2[ 0x48 ];
	int m_cam_command;

};