#ifndef MATH_FUNCTIONS_HEADER
#define MATH_FUNCTIONS_HEADER

class MathFunctions
{
public:
	static float Lerp(const float& aStartValue, const float& anEndValue, const float& aPercentage);

private:
	MathFunctions() {};
};
#endif