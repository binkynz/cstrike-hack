#pragma once

struct easing {

	// lots of functions i know

	inline double in_cubic( double seconds ) {

		return seconds * seconds * seconds;

	}

};

inline easing m_easing;