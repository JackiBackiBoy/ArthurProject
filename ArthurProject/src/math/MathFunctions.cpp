#include "MathFunctions.h"

float MathFunctions::Lerp(const float& aStartValue, const float& anEndValue, const float& aPercentage)
{
	return ((1.0f - aPercentage) * aStartValue) + (aPercentage * anEndValue);
}