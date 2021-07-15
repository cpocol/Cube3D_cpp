#pragma once
#include <QEntity.h>
#include <Qt3DCore/Qt3DCore>
#include <Qt3DCore/QTransform.h>

using namespace Qt3DCore;

class Cube : public QEntity
{
private:
	float side = 15;
	float yaw;
	float pitch;
	Qt3DCore::QTransform* pCubeTransform;

public:
	Cube(QEntity* parent);

	void rotate(float dx, float dy);

	float yawSpeed;
	float pitchSpeed;
};

