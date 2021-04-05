#pragma once

inline int bit_byte( int bits ) {

	return ( bits + 7 ) >> 3;

}

struct bf_write {

	void start_writing( void* data, int bytes, int start_bit = 0, int bits = -1 ) {

		bytes &= ~3;

		m_data = ( unsigned char* )data;
		m_data_bytes = bytes;

		if ( bits == -1 )
			m_data_bits = bytes << 3;
		else 
			m_data_bits = bits;

		m_cur_bit = start_bit;
		m_overflow = false;

	}

	inline unsigned char* get_data( ) { 
		
		return m_data;

	}

	inline int get_num_bytes_written( ) const {

		return bit_byte( m_cur_bit );

	}

	unsigned char* m_data;
	int m_data_bytes;
	int m_data_bits;
	int m_cur_bit;

private:

	bool m_overflow;
	bool m_assert_on_overflow;
	const char* m_debug_name;

};