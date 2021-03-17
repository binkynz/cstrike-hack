#pragma once

#include <cmath>

struct vector_3d {

	vector_3d( ) : x{ }, y{ }, z{ } { }

	vector_3d( float x, float y, float z ) : x{ x }, y{ y }, z{ z } { }

	inline vector_3d& operator+=( const vector_3d& v ) {

		x += v.x;
		y += v.y;
		z += v.z;

		return *this;

	}

	inline vector_3d& operator-=( const vector_3d& v ) {

		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;

	}

	inline vector_3d& operator*=( const vector_3d& v ) {

		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;

	}

	inline vector_3d& operator/=( const vector_3d& v ) {

		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;

	}

	inline vector_3d& operator+=( float fl ) {

		x += fl;
		y += fl;
		z += fl;

		return *this;

	}

	inline vector_3d& operator-=( float fl ) {

		x -= fl;
		y -= fl;
		z -= fl;

		return *this;

	}


	inline vector_3d& operator*=( float fl ) {

		x *= fl;
		y *= fl;
		z *= fl;

		return *this;

	}

	inline vector_3d& operator/=( float fl ) {

		x /= fl;
		y /= fl;
		z /= fl;

		return *this;

	}

	inline vector_3d operator+( const vector_3d& v ) {

		vector_3d result;

		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;

		return result;

	}

	inline vector_3d operator-( const vector_3d& v ) {

		vector_3d delta;

		delta.x = x - v.x;
		delta.y = y - v.y;
		delta.z = z - v.z;

		return delta;

	}

	inline vector_3d operator*( const vector_3d& v ) {

		vector_3d result;

		result.x = x * v.x;
		result.y = y * v.y;
		result.z = z * v.z;

		return result;

	}

	inline vector_3d operator/( const vector_3d& v ) {

		vector_3d result;

		result.x = x / v.x;
		result.y = y / v.y;
		result.z = z / v.z;

		return result;

	}

	inline vector_3d operator+( float fl ) {

		return {

			x + fl,
			y + fl,
			z + fl

		};

	}

	inline vector_3d operator-( float fl ) {

		return {

			x - fl,
			y - fl,
			z - fl

		};

	}

	inline vector_3d operator*( float fl ) {

		return {

			x * fl,
			y * fl,
			z * fl

		};

	}

	inline vector_3d operator/( float fl ) {

		return {

			x / fl,
			y / fl,
			z / fl
		
		};

	}

	inline float length( ) {

		return std::sqrtf( std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 ) );

	}

	inline float length_sqr( ) {

		return std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 );

	}

	inline float vector_normalize( vector_3d& v ) {

		float radius = std::sqrtf( std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 ) );
		radius = 1.f / ( radius + FLT_EPSILON );

		v *= radius;

		return radius;

	}

	inline vector_3d normalized( ) {

		vector_3d v = *this;
		vector_normalize( v );
		return v;

	}

	float x, y, z;

};