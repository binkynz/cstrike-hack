#pragma once

struct studio_render_context {

	char _pad0[ 0x240 ]; // 0
	float m_color_mod[ 3 ]; // 576
	float m_alpha_mod; // 588
	material* m_forced_material[ 4 ]; // 592
	int m_forced_material_type; // 608
	int m_forced_material_index[ 4 ]; // 612
	int m_forced_material_index_count; // 628

	inline auto set_color( const color& color ) {

		m_color_mod[ 0 ] = static_cast< float >( color.r ) / 255.f;
		m_color_mod[ 1 ] = static_cast< float >( color.g ) / 255.f;
		m_color_mod[ 2 ] = static_cast< float >( color.b ) / 255.f;

	}

	inline auto set_alpha( float alpha ) {

		m_alpha_mod = alpha;

	}

	inline auto set_material( material* material, bool ignore_z = true ) {

		m_forced_material_type = 0;
		m_forced_material[ 0 ] = material;
		m_forced_material_index[ 0 ] = -1;
		m_forced_material_index_count = 0;

		if ( !m_forced_material[ 0 ] )
			return;

		m_forced_material[ 0 ]->set_material_var_flag( 1 << 15, ignore_z );

	}

};