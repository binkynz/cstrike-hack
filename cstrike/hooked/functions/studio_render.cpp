#include "../hooked.h"

void __fastcall hooked::draw_model( studio_render_context* ecx, void* edx, void* results, const draw_model_info& info, void* bone_to_world, float* flex_weights, float* flex_delayed_rates, const vector_3d& origin, int flags ) {

	static auto o_draw_model = m_detour.get< decltype( &draw_model ) >( "CStudioRenderContext::DrawModel" );

	if ( !m_config.m_esp.chams || !m_cstrike.m_local_player || !info.m_client_entity )
		return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

	base_entity* entity = reinterpret_cast< base_entity* >( info.m_client_entity - 0x4 );
	if ( entity
		&& entity->is_player( )
		&& entity->get_team( ) != m_cstrike.m_local_player->get_team( ) ) {

		ecx->set_color( color( 109, 114, 195 ) );

		// ecx->set_alpha( 1.f );

		static auto material = m_interfaces.m_material_system->find_material( "debug/debugdrawflat", "Model textures" );
		ecx->set_material( material );

		o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

		ecx->set_color( color( 221, 115, 115 ) );

		ecx->set_material( material, false );

		o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

		ecx->set_material( nullptr );

		return;

	}

	return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

}