#include <cstdlib>
#include <cstdio>

float focalLength = 35;
// 35mm Full Aperture
float filmApertureWidth = 0.980;
float filmApertureHeight = 0.735;
static const float inchToMm = 25.4;
float nearClippingPlane = 0.1;
float farClipingPlane = 1000;

int main(int argc, char** argv)
{
#if 0
    // First method. Compute the horizontal angle of view first
    float angleOfViewHorizontal = 2 * atan((filmApertureWidth * inchToMm / 2) / focalLength);
    float right = tan(angleOfViewHorizontal / 2) * nearClippingPlane;
#else
    // Second method. Compute the right coordinate directly
    float right = ((filmApertureWidth * inchToMm / 2) / focalLength) * nearClippingPlane;
    float top = ((filmApertureHeight * inchToMm / 2) / focalLength) * nearClippingPlane;

#endif

    float left = -right;
    float bottom = -top;

    printf("Screen window left/right coordinates %f %f\n", left, right);
}