#include "Matrix3x3.h"

void set_Rotation_OX(Matrix3x3 &m, double angle)
{
    double sin_a, cos_a;
    sin_a = sin(angle * M_PI / 180); // M_PI 0. x20
    cos_a = cos(angle * M_PI / 180);

    m = Matrix3x3({1, 0, 0, 0, cos_a, -sin_a, 0, sin_a, cos_a});
}
void set_Rotation_OY(Matrix3x3 &m, double angle)
{
    double sin_a, cos_a;
    sin_a = sin(angle * M_PI / 180); // M_PI 0. x20
    cos_a = cos(angle * M_PI / 180);

    m = Matrix3x3({cos_a, 0, sin_a, 0, 1, 0, -sin_a, 0, cos_a});
}
void set_Rotation_OZ(Matrix3x3 &m, double angle)
{
    double sin_a, cos_a;
    sin_a = sin(angle * M_PI / 180); // M_PI 0. x20
    cos_a = cos(angle * M_PI / 180);

    m = Matrix3x3({cos_a, -sin_a, 0, sin_a, cos_a, 0, 0, 0, 1});
}