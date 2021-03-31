#pragma once

#include "../../input/input.h"
#include "../../render/render.h"

struct object {

	object( std::string_view name, int x, int y );

	virtual void draw( ) = 0;

	virtual void think( ) = 0;

	virtual int get_height( ) = 0;

protected:

	std::string m_name;

	int m_gap = 5;

	struct {

		int x, y;

	} m_size;

};