#include "../hooked.h"

void __fastcall hooked::cs_player_fn::update_client_side_animation( cs_player* ecx, void* edx ) {

	if ( ecx->get_use_new_animstate( ) ) {

		ecx->get_player_anim_state_csgo( )->update( ecx->eye_angles( ).y, ecx->eye_angles( ).x );

	} else {

		if ( ecx->get_sequence( ) != -1 )
			ecx->frame_advance( 0.f );

		if ( ecx->is_local_player( ) )
			ecx->get_player_anim_state_csgo( )->update( ecx->eye_angles( ).y, ecx->eye_angles( ).x );
		else
			ecx->get_player_anim_state_csgo( )->update( ecx->get_eye_angles( ).y, ecx->get_eye_angles( ).x );

	}

	if ( ecx->get_sequence( ) != -1 )
		ecx->on_latch_interpolated_variables( 1 /* LATCH_ANIMATION_VAR */ );

	if ( ecx->get_killed_by_taser( ) )
		ecx->handle_taser_animation( );

	if ( ecx->is_local_player( ) ) {

		weapon_cs_base* weapon = m_interfaces.m_entity_list->get< weapon_cs_base* >( ecx->get_active_weapon( ) );
		if ( weapon ) {

			base_view_model* view_model = ecx->get_view_model( weapon->get_view_model_index( ) );
			if ( view_model )
				view_model->update_all_viewmodel_addons( );

		} else {

			for ( int i = 0; i < 3 /* MAX_VIEWMODELS */; i++ ) {

				base_view_model* view_model = ecx->get_view_model( i );
				if ( view_model ) {

					view_model->remove_viewmodel_arm_models( );
					view_model->remove_viewmodel_label( );
					view_model->remove_viewmodel_stat_track( );
					view_model->remove_viewmodel_stickers( );

				}

			}

		}

	}

}