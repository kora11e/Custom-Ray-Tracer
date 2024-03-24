#include <cstdlib>
#include <cstdio>

bool computePixelCoordinates(
	const Vec3f& pWorld,
	const Matrix44f& cameraToWorld,
	const float& canvasWidth,
	const float& canvasHeight,
	const int& imageWidth,
	const int& imageHeight,
	Vec2i& pRaster
) {
	Vec3f pCamera;
	Matrix44f worldToCamera = cameraToWorld.inverse();
	worldToCamera.multVecMatrix(pWorld, pCamera);

	Vec2f pScreen;
	pScreen.x = pCamera.x / -pCamera.z;
	pScreen.y = pCamera.y / -pCamera.z;

	if (std::abs(pScreen.x) > canvasWidth || std::abs(pScreen.y) > canvasHeight)
		return false;

	Vec2f pNDC;
	pNDC.x = (pScreen.x + canvasWidth / 2) / canvasWidth;
	pNDC.y = (pScreen.y + canvasHeight / 2) / canvasHeight;

	pRaster.x = std::floor(pNDC.x * imageWidth);
	pRaster.y = std::floor((1 - pNDC.y) * imageHeight);

	return true;

}
