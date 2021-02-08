#pragma once

#include <corecrt_math.h>

struct mathlib_base {

	inline float anglemod( float a ) {

		// c casting :)
		a = ( 360.f / 65536 ) * ( ( int )( a * ( 65536.f / 360.f ) ) & 65535 );

		// references? lol cmon valve
		return a;

	}

	inline float angle_normalize( float angle ) {

		angle = std::fmodf( angle, 360.f );

		if ( angle > 180.f )
			angle -= 360.f;

		if ( angle < -180.f )
			angle += 360.f;

		return angle;

	}

	inline float approach_angle( float target, float value, float speed ) {

		target = anglemod( target );
		value = anglemod( value );

		float delta = target - value;

		if ( speed < 0 )
			speed = -speed;

		if ( delta < -180 )
			delta += 360;
		else if ( delta > 180 )
			delta -= 360;

		if ( delta > speed )
			value += speed;
		else if ( delta < -speed )
			value -= speed;
		else
			value = target;

		return value;
	}

	inline float angle_diff( float dest, float source ) {

		float delta = std::fmodf( dest - source, 360.f );

		if ( dest > source ) {

			if ( delta >= 180 )
				delta -= 360;

		} else {

			if ( delta <= -180 )
				delta += 360;

		}

		return delta;

	}

	inline float bias( float x, float bias_amt ) {

		static float last_amt = -1;
		static float last_exponent = 0;

		if ( last_amt != bias_amt ) 
			last_exponent = std::log( bias_amt ) * -1.4427f;

		return std::pow( x, last_exponent );

	}

};

inline mathlib_base m_mathlib_base;