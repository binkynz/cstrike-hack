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

	inline vector_3d operator+( const vector_3d& v ) const {

		vector_3d result = *this;

		return result += v;

	}

	inline vector_3d operator-( const vector_3d& v ) const {

		vector_3d result = *this;

		return result -= v;

	}

	inline vector_3d operator*( const vector_3d& v ) const {

		vector_3d result = *this;

		return result *= v;

	}

	inline vector_3d operator/( const vector_3d& v ) const {

		vector_3d result = *this;

		return result /= v;

	}

	inline vector_3d operator+( float fl ) const {

		vector_3d result = *this;

		return result += fl;

	}

	inline vector_3d operator-( float fl ) const {

		vector_3d result = *this;

		return result -= fl;

	}

	inline vector_3d operator*( float fl ) const {

		vector_3d result = *this;

		return result *= fl;

	}

	inline vector_3d operator/( float fl ) const {

		vector_3d result = *this;

		return result /= fl;

	}

	inline float length_sqr( ) const {

		return std::powf( x, 2 ) + std::powf( y, 2 ) + std::powf( z, 2 );

	}

	inline float length( ) const {

		return std::sqrtf( length_sqr( ) );

	}

	inline float vector_normalize( vector_3d& v ) const {

		float radius = length( );
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