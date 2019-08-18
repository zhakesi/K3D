#pragma once
#include "KCore/KDef.h"

namespace KMath 
{
	#define K_PI 3.1415926f

	class KLIB_EXPORT KMK 
	{
	private:
		KMK() {};
	public:
		static float Angle2Radian(float angle);
		static float ClampCircleVal(float val, float start, float end);
	};
}