#include "hooked.h"

bool hooked::setup( ) {

	// cdll_client_fn
	if ( !m_modules.m_client_dll.hook_function( "CHLClient::LevelShutdown", &cdll_client_fn::level_shutdown ) )
		return false;

	// cl_main_fn
	if ( !m_modules.m_engine_dll.hook_function( "CL_SendMove", &cl_main_fn::cl_send_move ) )
		return false;

	// client_input_fn
	if ( !m_modules.m_client_dll.hook_function( "CInput::CAM_Think", &client_input_fn::cam_think ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( "CInput::CAM_ToThirdPerson", &client_input_fn::cam_to_third_person ) )
		return false;

	// client_mode_shared_fn
	if ( !m_modules.m_client_dll.hook_function( "ClientModeShared::CreateMove", &client_mode_shared_fn::create_move ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( "ClientModeShared::GetViewModelFOV", &client_mode_shared_fn::get_view_model_fov ) )
		return false;

	// cs_player_fn
	if ( !m_modules.m_client_dll.hook_function( "C_CSPlayer::UpdateClientSideAnimation", &cs_player_fn::update_client_side_animation ) )
		return false;

	// csgo_player_anim_state_fn
	if ( !m_modules.m_client_dll.hook_function( "CCSGOPlayerAnimState::Update", &csgo_player_anim_state_fn::update ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( "CCSGOPlayerAnimState::ModifyEyePosition", &csgo_player_anim_state_fn::modify_eye_position ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( "CCSGOPlayerAnimState::DoProceduralFootPlant", &csgo_player_anim_state_fn::do_procedural_foot_plant ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( "CCSGOPlayerAnimState::SetUpVelocity", &csgo_player_anim_state_fn::set_up_velocity ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( "CCSGOPlayerAnimState::SetUpMovement", &csgo_player_anim_state_fn::set_up_movement ) )
		return false;

	// mat_system_surface_fn
	if ( !m_modules.m_vguimatsurface_dll.hook_function( "CMatSystemSurface::LockCursor", &mat_system_surface_fn::lock_cursor ) )
		return false;

	// prediction_fn
	if ( !m_modules.m_client_dll.hook_function( "CPrediction::RunCommand", &prediction_fn::run_command ) )
		return false;

	// scheme_manager_fn
	if ( !m_modules.m_vgui2_dll.hook_function( "CSchemeManager::ReloadSchemes", &scheme_manager_fn::reload_schemes ) )
		return false;

	// studio_render_fn
	if ( !m_modules.m_studiorender_dll.hook_function( "CStudioRenderContext::DrawModel", &studio_render_fn::draw_model ) )
		return false;

	// vgui_baseui_fn
	if ( !m_modules.m_engine_dll.hook_function( "CEngineVGui::Paint", &vgui_baseui_fn::paint ) )
		return false;

	// weapon_cs_base_fn
	if ( !m_modules.m_client_dll.hook_function( "C_WeaponCSBase::DrawCrosshair", &weapon_cs_base_fn::draw_crosshair ) )
		return false;

	return true;

}

void hooked::unload( ) {

	m_modules.m_client_dll.unload_functions( );
	m_modules.m_engine_dll.unload_functions( );
	m_modules.m_server_dll.unload_functions( );
	m_modules.m_gameoverlayrenderer_dll.unload_functions( );
	m_modules.m_vgui2_dll.unload_functions( );
	m_modules.m_vguimatsurface_dll.unload_functions( );
	m_modules.m_studiorender_dll.unload_functions( );
	m_modules.m_localize_dll.unload_functions( );
	m_modules.m_datacache_dll.unload_functions( );
	m_modules.m_materialsystem_dll.unload_functions( );
	m_modules.m_tier0.unload_functions( );

}