#pragma once

struct mem_alloc {

	inline auto alloc( std::size_t size ) {

		return m_utils.get_v_func< void* ( __thiscall* )( void*, std::size_t ) >( this, 1 )( this, size );

	}

};