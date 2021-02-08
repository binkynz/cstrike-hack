#pragma once

#include "base_player.h"

#include "../studio.h"

struct base_animating : base_player {

	inline auto set_sequence( int sequence ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int ) >( this, 218 )( this, sequence );

	}

	inline auto lookup_bone( const char* name ) {

		auto function = m_signatures.m_lookup_bone.as< int( __thiscall* )( void*, const char* ) >( );

		return function( this, name );

	}

	inline auto get_bone_position( int bone_id, vector_3d& origin ) {

		auto function = m_signatures.m_get_bone_position.as< void( __thiscall* )( void*, int, vector_3d* ) >( );

		vector_3d vectors[ 4 ];
		function( this, bone_id, vectors );
		origin = { vectors[ 1 ].x, vectors[ 2 ].y, vectors[ 3 ].z };

	}

	inline auto get_model_ptr( ) {

		auto function = m_signatures.m_get_model_ptr.as< studio_hdr* ( __thiscall* )( void* ) >( );

		return function( this );

	}

	inline auto get_first_sequence_anim_tag( int sequence, int desired_tag ) {

		auto function = m_signatures.m_get_first_sequence_anim_tag.as< float( __thiscall* )( void*, int, int, int ) >( );

		return function( this, sequence, desired_tag, 0 );

	}

	inline auto lookup_pose_parameter( const char* name ) {

		auto function = m_signatures.m_lookup_pose_parameter.as< int( __thiscall* )( void*, studio_hdr*, const char* name ) >( );

		return function( this, get_model_ptr( ), name );

	}

	inline auto set_pose_parameter( int parameter, float value ) {

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
				call m_signatures.m_studio_set_pose_parameter
				pop ecx

				popad

			}

			get_pose_parameter( )[ parameter ] = new_value;

		}

		return value;

	}

};