#pragma once

struct color {

	color( ) : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } { };

	color( int r, int g, int b, int a = 255 ) : r{ r }, g{ g }, b{ b }, a{ a } { };

	int r, g, b, a;

};