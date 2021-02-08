#pragma once

struct mstudioseqdesc {

	char _pad0[ 0xc4 ]; // 0
	int numanimtags; // 196

};

struct studio_hdr {

	inline auto seqdesc( int seq ) {

		auto function = m_signatures.m_seqdesc.as< mstudioseqdesc& ( __thiscall* )( void*, int ) >( );

		return function( this, seq );

	}

};