#include "../hooked.h"

float __fastcall hooked::get_view_model_fov( void* ecx, void* edx ) {

	return 95.f;

}