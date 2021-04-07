#pragma once

#include "base_player.h"

#include "../studio.h"

struct base_animating : base_player {

	inline auto set_sequence( int sequence ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int ) >( this, 218 )( this, sequence );

	}

	inline auto frame_advance( float interval ) {

		return m_utils.get_v_func< float( __thiscall* )( void*, float ) >( this, 220 )( this, interval );

	}

	inline auto lookup_bone( const char* name ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseAnimating::LookupBone" ).as< int( __thiscall* )( void*, const char* ) >( );

		return function( this, name );

	}

	inline auto get_bone_position( int bone_id, vector_3d& origin ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseAnimating::GetBonePosition" ).as< void( __thiscall* )( void*, int, vector_3d* ) >( );

		vector_3d vectors[ 4 ];
		function( this, bone_id, vectors );
		origin = { vectors[ 1 ].x, vectors[ 2 ].y, vectors[ 3 ].z };

	}

	inline auto get_model_ptr( ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseAnimating::GetModelPtr" ).as< studio_hdr* ( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto get_first_sequence_anim_tag( int sequence, int desired_tag ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseAnimating::GetFirstSequenceAnimTag" ).as< float( __thiscall* )( void*, int, int, int ) >( );

		return function( this, sequence, desired_tag, 0 );

	}

	inline auto get_sequence_activity( int sequence ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseAnimating::GetSequenceActivity" ).as< int( __thiscall* )( void*, int ) >( );

		return function( this, sequence );

	}

	inline auto lookup_pose_parameter( const char* name ) {

		static auto function = m_modules.m_client_dll.get_address( "C_BaseAnimating::LookupPoseParameter" ).as< int( __thiscall* )( void*, studio_hdr*, const char* name ) >( );

		return function( this, get_model_ptr( ), name );

	}

	inline auto set_pose_parameter( int parameter, float value ) {

		static auto address = m_modules.m_client_dll.get_address( "Studio_SetPoseParameter" );

		studio_hdr* studio_hdr = get_model_ptr( );
		if ( !studio_hdr )
			return value;

		if ( parameter >= 0.f ) {

			float new_value;
			
			__asm {

				pushad

				movss xmm2, [ value ]
				lea ecx, [ new_value ]
				push ecx
				mov edx, parameter
				mov ecx, studio_hdr
				call address
				pop ecx

				popad

			}

			get_pose_parameter( )[ parameter ] = new_value;

		}

		return value;

	}

	inline auto draw_server_hitboxes( float duration = 0.f, int /*bool*/ monocolor = 0 ) {

		static auto address = m_modules.m_server_dll.get_address( "CBaseAnimating::DrawServerHitboxes" );

		base_player* player = base_player::util_player_by_index( get_client_networkable( )->get_index( ) );
		if ( !player )
			return;

		__asm {

			pushad

			movss xmm1, duration
			push monocolor
			mov ecx, player
			call address

			popad
		}

	}

};