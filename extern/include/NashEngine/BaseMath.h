#pragma once
#include <cmath>

namespace Nash
{
	#define VERYSMALL (1.0E-150)
	#define EPSILON (1.0E-8)
	#define GRAVITY (9.807)
	#define PI (3.14159265359)
	

	inline static float AbsF(const float& value); 
	inline static double AbsD(const double& value);
	inline static bool Compare(const float& value1, const float& value2);
	inline static bool Compare(const double& value1, const double& value2);
	inline static float Sqrt(const float& value) { return std::sqrt(value); }
	inline static double Sqrt(const double& value) { return std::sqrt(value); }
}


float Nash::AbsF(const float & value)
{
	return value > 0 ? value : value * -1;
}
double Nash::AbsD(const double& value)
{
	return value > 0 ? value : value * -1;
}

bool Nash::Compare(const float & value1, const float & value2)
{
	return AbsF(value1 - value2) < EPSILON ? true : false; 
} 

bool Nash::Compare(const double & value1, const double & value2)
{
	return AbsD(value1-value2) < VERYSMALL ?  true: false;
}


