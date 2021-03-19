#pragma once

struct q_angle {

	q_angle( ) : x{ }, y{ }, z{ } { }

	q_angle( float pitch, float yaw, float roll ) : x{ pitch }, y{ yaw }, z{ roll } { }

	inline q_angle& operator+=( const q_angle& a ) {

		x += a.x;
		y += a.y;
		z += a.z;

		return *this;

	}

	inline q_angle& operator-=( const q_angle& a ) {

		x -= a.x;
		y -= a.y;
		z -= a.z;

		return *this;

	}

	inline q_angle& operator*=( const q_angle& a ) {

		x *= a.x;
		y *= a.y;
		z *= a.z;

		return *this;

	}

	inline q_angle& operator/=( const q_angle& a ) {

		x /= a.x;
		y /= a.y;
		z /= a.z;

		return *this;

	}

	inline q_angle& operator+=( float fl ) {

		x += fl;
		y += fl;
		z += fl;

		return *this;

	}

	inline q_angle& operator-=( float fl ) {

		x -= fl;
		y -= fl;
		z -= fl;

		return *this;

	}


	inline q_angle& operator*=( float fl ) {

		x *= fl;
		y *= fl;
		z *= fl;

		return *this;

	}

	inline q_angle& operator/=( float fl ) {

		x /= fl;
		y /= fl;
		z /= fl;

		return *this;

	}

	inline q_angle operator+( const q_angle& a ) const {

		q_angle result = *this;

		return result += a;

	}

	inline q_angle operator-( const q_angle& a ) const {

		q_angle result = *this;

		return result -= a;

	}

	inline q_angle operator*( const q_angle& a ) const {

		q_angle result = *this;

		return result *= a;

	}

	inline q_angle operator/( const q_angle& a ) const {

		q_angle result = *this;

		return result /= a;

	}

	inline q_angle operator+( float fl ) const {

		q_angle result = *this;

		return result += fl;

	}

	inline q_angle operator-( float fl ) const {

		q_angle result = *this;

		return result -= fl;

	}

	inline q_angle operator*( float fl ) const {

		q_angle result = *this;

		return result *= fl;

	}

	inline q_angle operator/( float fl ) const {

		q_angle result = *this;

		return result /= fl;

	}

	float x, y, z;

};