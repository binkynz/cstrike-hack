#pragma once

struct mstudioseqdesc {

	char _pad0[ 0xc4 ]; // 0
	int numanimtags; // 196

};

struct studio_hdr {

	inline auto seqdesc( int seq ) {

		static auto function = m_modules.m_client_dll.get_address( "CStudioHdr::pSeqdesc" ).as< mstudioseqdesc& ( __thiscall* )( void*, int ) >( );

		return function( this, seq );

	}

};