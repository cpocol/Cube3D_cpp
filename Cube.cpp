#include <QPlaneMesh.h>
#include <QTransform.h>
#include <Qt3DExtras/Qt3DExtras>
#include <QRandomGenerator>
#include <QtCore/QtMath>

#include "Cube.h"

using namespace Qt3DExtras;

Cube::Cube(QEntity* parent)
	: QEntity(parent)
{
	//init params of the 6 planes
	float planeTranslations[6][3] = {{      0, -side/2, 0},
									 {      0, +side/2, 0},
									 {-side/2,       0, 0},
									 {+side/2,       0, 0},
									 {      0,       0, -side/2},
									 {      0,       0, +side/2}};
	float planeRotations[6][3] = {{  0,  0, 180},
								  {  0,  0,   0},
								  {  0,  0,  90},
								  {  0,  0, 270},
								  {270,  0,   0},
								  { 90,  0,   0}};

	//build the planes
	for (int i = 0; i < 6; i++)
	{
		QEntity* pPlaneEntity = new QEntity(this);

		QPlaneMesh* pPlaneMesh = new QPlaneMesh();
		pPlaneMesh->setWidth(side);
		pPlaneMesh->setHeight(side);

		Qt3DCore::QTransform* pPlaneTransform = new Qt3DCore::QTransform();
		pPlaneTransform->setRotationX(planeRotations[i][0]);
		pPlaneTransform->setRotationZ(planeRotations[i][2]);
		pPlaneTransform->setTranslation(QVector3D(planeTranslations[i][0], planeTranslations[i][1], planeTranslations[i][2]));

		Qt3DExtras::QPhongMaterial* pMaterial = new Qt3DExtras::QPhongMaterial(this);
		pMaterial->setAmbient(QColor(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256)));

		pPlaneEntity->addComponent(pPlaneMesh);
		pPlaneEntity->addComponent(pPlaneTransform);
		pPlaneEntity->addComponent(pMaterial);
	}

    //initial rotation
    yaw = -15;
    pitch = 15;
    yawSpeed = 0;
    pitchSpeed = 0;
    pCubeTransform = new Qt3DCore::QTransform();
    addComponent(pCubeTransform);
    rotate(0, 0); //trigger the computation of the rotation matrix for the initial rotation
}

void Cube::rotate(float dx, float dy)
{
    //custom rotation order - rotate around Y then around X
    yaw   += dx;
    pitch += dy;
    float a = yaw*3.14/180;
    QMatrix4x4 yawMat(qCos(a),    0, qSin(a),    0,
                            0,    1,       0,    0,
                     -qSin(a),    0, qCos(a),    0,
                            0,    0,       0,    1);
    a = pitch*3.14/180;
    QMatrix4x4 pitchMat(1,       0,        0,    0,
                        0, qCos(a), -qSin(a),    0,
                        0, qSin(a),  qCos(a),    0,
                        0,       0,        0,    1);
    QMatrix4x4 rotMat = pitchMat*yawMat;
    pCubeTransform->setMatrix(rotMat);
}
