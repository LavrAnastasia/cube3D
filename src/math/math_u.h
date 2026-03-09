#ifndef MATH_U_H
# define MATH_U_H

#include <math.h>

// TODO: CHECK
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

double	deg_to_rad(double deg);
double	normalize_angle(double a);
int		sign(double value);

#endif