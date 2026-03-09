#include "math_u.h"

double deg_to_rad(double deg)
{
    return (deg * M_PI / 180.0);
}

double normalize_angle(double angle) 
{
    const double two_pi = 2.0 * M_PI;

    while (angle < 0.0)
        angle += two_pi;
    while (angle >= two_pi)
        angle -= two_pi;
    return (angle);
}

int sign(double value)
{
    int sign;

    sign = 0;
    if (value < 0)
        sign = -1;
    else if (value > 0)
        sign = 1;
    return (sign); 
}