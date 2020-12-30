#pragma once

struct detour {

	bool hook( void* function, void* custom_function );

	void unload( );

	template< typename t > inline t get( ) {

		return ( t )m_original;

	}

private:

	void* m_normal = nullptr;
	void* m_original = nullptr;

};