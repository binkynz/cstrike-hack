#include "../hooked.h"

void __fastcall hooked::draw_model( studio_render_context* ecx, void* edx, void* results, const draw_model_info& info, void* bone_to_world, float* flex_weights, float* flex_delayed_rates, const vector_3d& origin, int flags ) {

	static auto o_draw_model = m_detour.get< decltype( &draw_model ) >( "CStudioRenderContext::DrawModel" );

	if ( !m_cstrike.m_local_player || !info.m_client_entity )
		return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

	base_entity* entity = reinterpret_cast< base_entity* >( info.m_client_entity - 0x4 );
	if ( entity
		&& entity->is_player( )
		&& entity->get_team( ) != m_cstrike.m_local_player->get_team( ) ) {

		float color[ 3 ] = { 255.f, 110.f / 255.f, 144.f / 255.f };
		ecx->set_colour_modulation( color );

		ecx->set_alpha_modulation( 0.8f );

		return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

	}

	return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

}