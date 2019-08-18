#include "KMath/KMK.h"

namespace KMath 
{
	float KMK::Angle2Radian(float angle) 
	{
		return angle / 180.0f * K_PI;
	}

	float KMK::ClampCircleVal(float val, float start, float end)
	{
		float period = end - start;
		val = val - start;
		if (val >= 0.0f)
			val = val - (int)(val / period) * period;
		else
			val = val - ((int)(val / period) - 1) * period;

		return start + val;
	}
}