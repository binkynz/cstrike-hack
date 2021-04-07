#include "../hooked.h"

void __fastcall hooked::client_input_fn::cam_think( client_input* ecx, void* edx ) {

	static auto o_cam_think = m_modules.m_client_dll.get< decltype( &cam_think ) >( "CInput::CAM_Think" );

	ecx->m_camera_in_third_person = !m_input.is_key_toggled( m_config.m_esp.thirdperson_key, m_config.m_esp.third_person );

	ecx->m_cam_command = 1;

	return o_cam_think( ecx, edx );

}

void __fastcall hooked::client_input_fn::cam_to_third_person( client_input* ecx, void* edx ) {

	static auto o_cam_to_third_person = m_modules.m_client_dll.get< decltype( &cam_to_third_person ) >( "CInput::CAM_ToThirdPerson" );

	o_cam_to_third_person( ecx, edx );

	ecx->m_camera_offset.z = m_config.m_esp.thirdperson_distance;

}