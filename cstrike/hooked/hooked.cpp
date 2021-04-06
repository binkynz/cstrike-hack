#include "hooked.h"

bool hooked::setup( ) {

	m_detour.setup( "CHLClient::LevelShutdown", m_signatures.m_level_shutdown, &level_shutdown );

	m_detour.setup( "ClientModeShared::CreateMove", m_signatures.m_create_move, &create_move );

	m_detour.setup( "ClientModeShared::GetViewModelFOV", m_signatures.m_get_view_model_fov, &get_view_model_fov );

	m_detour.setup( "CEngineVGui::Paint", m_signatures.m_paint, &paint );

	m_detour.setup( "C_WeaponCSBase::DrawCrosshair", m_signatures.m_draw_crosshair, &draw_crosshair );

	m_detour.setup( "CCSGOPlayerAnimState::Update", m_signatures.m_update, &update );

	m_detour.setup( "CCSGOPlayerAnimState::ModifyEyePosition", m_signatures.m_modify_eye_position, &modify_eye_position );

	m_detour.setup( "CCSGOPlayerAnimState::DoProceduralFootPlant", m_signatures.m_do_procedural_foot_plant, &do_procedural_foot_plant );

	m_detour.setup( "CCSGOPlayerAnimState::SetUpVelocity", m_signatures.m_setup_velocity, &set_up_velocity );

	m_detour.setup( "CCSGOPlayerAnimState::SetUpMovement", m_signatures.m_setup_movement, &set_up_movement );

	m_detour.setup( "CInput::CAM_Think", m_signatures.m_cam_think, &cam_think );

	m_detour.setup( "CInput::CAM_ToThirdPerson", m_signatures.m_cam_to_third_person, &cam_to_third_person );

	m_detour.setup( "CSchemeManager::ReloadSchemes", m_signatures.m_reload_schemes, &reload_schemes );

	m_detour.setup( "CStudioRenderContext::DrawModel", m_signatures.m_draw_model, &draw_model );

	m_detour.setup( "CMatSystemSurface::LockCursor", m_signatures.m_lock_cursor, &lock_cursor );

	m_detour.setup( "CL_SendMove", m_signatures.m_cl_send_move, &cl_send_move );

	m_detour.setup( "C_CSPlayer::UpdateClientSideAnimation", m_signatures.m_update_client_side_animation, &update_client_side_animation );

	return true;

}

void hooked::unload( ) {

	m_detour.unload( );

}