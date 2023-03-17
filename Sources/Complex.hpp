#ifndef Complex_hpp
#define Complex_hpp

#include <math.h>

struct Complex{ float re,im; };

Complex operator+(Complex a,Complex b);
Complex operator-(Complex a,Complex b);
Complex operator*(float a,Complex b);
Complex operator*(Complex a,float b);
Complex operator*(Complex a,Complex b);
Complex operator/(Complex a,float b);
Complex operator/(Complex a,int b);
Complex mkComplex(float x, float y);
Complex mkComplexExp(float r, float theta_deg);
Complex rotate(Complex a, float x, float y, float angle_deg);
Complex rotate(Complex a, Complex b, float angle_deg);
Complex scale(Complex a,float x,float y,float lamda);
Complex lerp(Complex a,Complex b,float t);
Complex normalize(Complex c);

#endif
