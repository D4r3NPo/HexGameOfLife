#include "Complex.hpp"

Complex mkComplex(float re, float im)
{
	return {re, im};
}
Complex mkComplexExp(float r, float theta_deg)
{
	float theta_rad = theta_deg * M_PI / 180;
	return {r * cos(theta_rad) , r * sin(theta_rad)};
}
Complex operator+(Complex a,Complex b)
{
	return {a.re+b.re,a.im+b.im};
}
Complex operator-(Complex a,Complex b)
{
	return {a.re-b.re,a.im-b.im};
}
Complex operator*(float a,Complex b)
{
	return {b.re*a,b.im*a};
}
Complex operator*(Complex a,float b)
{
	return b * a;
}
Complex operator/(Complex a,float b)
{
	return {a.re/b,a.im/b};
}
Complex operator/(Complex a,int b)
{
	return {a.re/b,a.im/b};
}
Complex operator*(Complex a,Complex b)
{
	return {a.re * b.re - a.im*b.im,
		a.re*b.im + a.im*b.re};
}
Complex rotate(Complex a, Complex b, float angle_deg)
{
	Complex rot = mkComplexExp(1, angle_deg);
	return (a-b) * rot + b;
}
Complex rotate(Complex a, float re, float im, float angle_deg)
{
	return rotate(a, mkComplex(re, im), angle_deg);
}
Complex scale(Complex a,Complex b,float lamda)
{
	return (a - b) * lamda + b;
}
Complex scale(Complex a,float re,float im,float lamda)
{
	return scale(a, mkComplex(re, im),lamda);
}
Complex lerp(Complex a,Complex b,float t)
{
	return (1-t) * a + t * b;
}
Complex normalize(Complex c)
{
	float norm = sqrt(c.re*c.re+c.im*c.im);
	return mkComplex(c.re/norm, c.im/norm);
}
