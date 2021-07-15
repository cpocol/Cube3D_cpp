#pragma once
#include <qt3dwindow.h>
#include <Qt3DCore/Qt3DCore>
#include <QTimer>
#include <QCamera.h>

#include "Cube.h"

using namespace Qt3DExtras;

class Cube3DWindow :
	public Qt3DWindow
{
   Q_OBJECT
private:
	Cube* pCube;
	QEntity* pRootEntity;
    QPoint mouseDist, mouseLastPos;
	bool mouseDown;
	QTimer* pTimer;

private slots:
	void onTimer();

public:
	Cube3DWindow();

	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void addCube();
};

