#include "modules.h"

bool modules::setup( ) {

	if ( !get( ) )
		return false;

	get_addresses( );

	if ( !got_addresses( ) )
		return false;

	return true;

}

bool modules::get( ) {

	m_client_dll = m_pe.get( "client.dll" );
	if ( !m_client_dll.get_module( ) )
		return false;

	m_engine_dll = m_pe.get( "engine.dll" );
	if ( !m_engine_dll.get_module( ) )
		return false;

	m_server_dll = m_pe.get( "server.dll" );
	if ( !m_server_dll.get_module( ) )
		return false;

	m_gameoverlayrenderer_dll = m_pe.get( "gameoverlayrenderer.dll" );
	if ( !m_gameoverlayrenderer_dll.get_module( ) )
		return false;

	m_vgui2_dll = m_pe.get( "vgui2.dll" );
	if ( !m_vgui2_dll.get_module( ) )
		return false;

	m_vguimatsurface_dll = m_pe.get( "vguimatsurface.dll" );
	if ( !m_vguimatsurface_dll.get_module( ) )
		return false;

	m_studiorender_dll = m_pe.get( "studiorender.dll" );
	if ( !m_studiorender_dll.get_module( ) )
		return false;

	m_localize_dll = m_pe.get( "localize.dll" );
	if ( !m_localize_dll.get_module( ) )
		return false;

	m_datacache_dll = m_pe.get( "datacache.dll" );
	if ( !m_datacache_dll.get_module( ) )
		return false;

	m_materialsystem_dll = m_pe.get( "materialsystem.dll" );
	if ( !m_materialsystem_dll.get_module( ) )
		return false;

	m_tier0 = m_pe.get( "tier0.dll" );
	if ( !m_tier0.get_module( ) )
		return false;

	return true;

}

void modules::get_addresses( ) {

	m_client_dll.add_address( "g_pNetGraphPanel", "89 1D ? ? ? ? 8B C3" );

	m_client_dll.add_address( "C_BaseAnimating::LookupBone", "E8 ? ? ? ? 89 44 24 5C", true );
	m_client_dll.add_address( "C_BaseAnimating::GetBonePosition", "E8 ? ? ? ? 8D 14 24", true );
	m_client_dll.add_address( "C_BaseAnimating::GetModelPtr", "E8 ? ? ? ? 8B 55 38", true );
	m_client_dll.add_address( "C_BaseAnimating::GetFirstSequenceAnimTag", "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB", true );
	m_client_dll.add_address( "C_BaseAnimating::LookupPoseParameter", "E8 ? ? ? ? 85 C0 79 08", true );
	m_client_dll.add_address( "C_BaseAnimating::GetSequenceActivity", "E8 ? ? ? ? 33 C9 3B F0", true );
	m_client_dll.add_address( "Studio_SetPoseParameter", "E8 ? ? ? ? 0F 28 D8 83 C4 04", true );

	m_client_dll.add_address( "C_BaseEntity->m_vecAbsVelocity", "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" );
	m_client_dll.add_address( "C_BaseEntity->m_nAnimOverlay", "8B 80 ? ? ? ? 03 C1 74 15" );
	m_client_dll.add_address( "C_BaseEntity::GetGroundEntity", "E8 ? ? ? ? 8B 4C 24 14 85 C0", true );
	m_client_dll.add_address( "C_BaseEntity::InvalidatePhysicsRecursive", "E8 ? ? ? ? 89 5E 18", true );
	m_client_dll.add_address( "C_BaseEntity::SetAbsAngles", "E8 ? ? ? ? 53 8D 45 F0", true );
	m_client_dll.add_address( "C_BaseEntity::CalcAbsoluteVelocity", "E8 ? ? ? ? 83 7B 30 00", true );

	m_client_dll.add_address( "C_BasePlayer::GetViewModel", "E8 ? ? ? ? 8B F8 8B 47 04", true );
	m_client_dll.add_address( "C_BasePlayer::IsLocalPlayer", "56 8B F1 85 F6 74 16" );

	m_client_dll.add_address( "C_CSPlayer->m_PlayerAnimStateCSGO", "8B 8E ? ? ? ? EB 39" );
	m_client_dll.add_address( "C_CSPlayer->m_bUseNewAnimstate", "80 BE ? ? ? ? ? 74 36 8B 06" );
	m_client_dll.add_address( "C_CSPlayer::UpdateClientSideAnimation", "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" );
	m_client_dll.add_address( "C_CSPlayer::HandleTaserAnimation", "E8 ? ? ? ? 8B 06 8B CE 8B 80 ? ? ? ? FF D0 84 C0 0F 84 ? ? ? ?", true );

	m_client_dll.add_address( "CHLClient::LevelShutdown", "55 8B EC 83 E4 F8 83 EC 30 C6 05 ? ? ? ? ?" );

	m_client_dll.add_address( "ClientModeShared::CreateMove", "55 8B EC 8B 0D ? ? ? ? 85 C9 75 06" );
	m_client_dll.add_address( "ClientModeShared::GetViewModelFOV", "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" );

	m_client_dll.add_address( "C_WeaponCSBase::DrawCrosshair", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" );

	m_client_dll.add_address( "CCSGOPlayerAnimState::Update", "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::ModifyEyePosition", "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::DoProceduralFootPlant", "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpVelocity", "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpMovement", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpAimMatrix", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpWeaponAction", "55 8B EC 51 53 56 57 8B F9 8B 77 60" );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpMovement", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpAliveloop", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpWholeBodyAction", "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpFlinch", "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::SetUpLean", "E8 ? ? ? ? 33 C0 89 44 24 0C", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::CacheSequences", "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::IncrementLayerCycle", "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?", true );
	m_client_dll.add_address( "CCSGOPlayerAnimState::IncrementLayerWeight", "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?", true );

	m_client_dll.add_address( "CStudioHdr::pSeqdesc", "E8 ? ? ? ? 03 40 04", true );

	m_client_dll.add_address( "CInput::CAM_Think", "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" );
	m_client_dll.add_address( "CInput::CAM_ToThirdPerson", "55 8B EC 83 EC 0C 8D 55 F4" );

	m_client_dll.add_address( "C_BaseViewModel::UpdateAllViewmodelAddons", "E8 ? ? ? ? 8B 16 8B CE 6A 20", true );
	m_client_dll.add_address( "C_BaseViewModel::RemoveViewmodelArmModels", "E8 ? ? ? ? 46 83 FE 03 7C E7 85 DB", true );
	m_client_dll.add_address( "C_BaseViewModel::RemoveViewmodelLabel", "E8 ? ? ? ? 8B CB E8 ? ? ? ? 8B CB E8 ? ? ? ? 5F", true );
	m_client_dll.add_address( "C_BaseViewModel::RemoveViewmodelStatTrak", "E8 ? ? ? ? 56 FF 74 24 10", true );
	m_client_dll.add_address( "C_BaseViewModel::RemoveViewmodelStickers", "E8 ? ? ? ? 43 83 FB 03 7C CC", true );

	m_engine_dll.add_address( "CEngineVGui::Paint", "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" );

	m_engine_dll.add_address( "CL_SendMove", "E8 ? ? ? ? 84 DB 0F 84 ? ? ? ? 8B 8F ? ? ? ?", true );

	m_engine_dll.add_address( "CCLCMsg_Move::set_data", "E8 ? ? ? ? 8D 7E 18", true );
	m_engine_dll.add_address( "CCLCMsg_Move::Deconstuctor", "E8 ? ? ? ? 5F 5E 5B 8B E5 5D C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 81 EC ? ? ? ?", true );

	m_vguimatsurface_dll.add_address( "CMatSystemSurface::StartDrawing", "55 8B EC 83 E4 C0 83 EC 38" );
	m_vguimatsurface_dll.add_address( "CMatSystemSurface::FinishDrawing", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );
	m_vguimatsurface_dll.add_address( "CMatSystemSurface::LockCursor", "80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 55" );

	m_vgui2_dll.add_address( "CSchemeManager::ReloadSchemes", "55 8B EC 83 EC 08 53 56 8B F1 6A 00" );

	m_studiorender_dll.add_address( "CStudioRenderContext::DrawModel", "55 8B EC 83 E4 F8 83 EC 54" );

	m_gameoverlayrenderer_dll.add_address( "GameOverlayRenderer::HookFunc", "55 8B EC 51 8B 45 10 C7" );
	m_gameoverlayrenderer_dll.add_address( "GameOverlayRenderer::UnhookFunc", "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?", true );

	m_server_dll.add_address( "CBaseAnimating::DrawServerHitboxes", "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF", true );
	m_server_dll.add_address( "UTIL_PlayerByIndex", "85 C9 7E 2A A1 ? ? ? ?" );
	m_server_dll.add_address( "CCSGOPlayerAnimState::SetUpVelocity", "55 8B EC 83 E4 F8 83 EC 28 56 57 8B 3D ? ? ? ? 8B F1 8B CF" );

}

bool modules::got_addresses( ) {

	if ( !m_client_dll.valid_addresses( ) )
		return false;

	if ( !m_engine_dll.valid_addresses( ) )
		return false;

	if ( !m_server_dll.valid_addresses( ) )
		return false;

	if ( !m_gameoverlayrenderer_dll.valid_addresses( ) )
		return false;

	if ( !m_vgui2_dll.valid_addresses( ) )
		return false;

	if ( !m_vguimatsurface_dll.valid_addresses( ) )
		return false;

	if ( !m_studiorender_dll.valid_addresses( ) )
		return false;

	if ( !m_localize_dll.valid_addresses( ) )
		return false;

	if ( !m_datacache_dll.valid_addresses( ) )
		return false;

	if ( !m_materialsystem_dll.valid_addresses( ) )
		return false;

	if ( !m_tier0.valid_addresses( ) )
		return false;

	return true;

}