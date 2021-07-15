#include "Cube3DWindow.h"

Cube3DWindow::Cube3DWindow()
{
	//Root entity
	pRootEntity = new QEntity();
	setRootEntity(pRootEntity);
	pCube = NULL;

	//Camera
    Qt3DRender::QCamera* pCamera = camera();
	pCamera->lens()->setPerspectiveProjection(45, 16 / 9, 0.1, 1000);
	pCamera->setPosition(QVector3D(0, 0, 40));
	pCamera->setViewCenter(QVector3D(0, 0, 0));

	mouseDown = false;
	pTimer = new QTimer(this);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

void Cube3DWindow::addCube()
{
	pCube = new Cube(pRootEntity);
}

void Cube3DWindow::mouseMoveEvent(QMouseEvent *event)
{
	QPoint mousePos = event->pos();
	if (pCube)
		if (mouseDown)
		{
			pTimer->stop();
			if (mousePos != mouseLastPos)
			{
				mouseDist = mousePos - mouseLastPos;
				pCube->rotate(mouseDist.x()/10.f, mouseDist.y()/10.f);
				mouseLastPos = mousePos;
			}
		}
}

void Cube3DWindow::mousePressEvent(QMouseEvent *event)
{
	if (pCube)
	{
		mouseDown = true;
		mouseLastPos = event->pos();
		pTimer->stop();
	}
}

void Cube3DWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (pCube)
	{
		if (mouseDown == true)
		{
			mouseDown = false;
			pCube->yawSpeed   = mouseDist.x(); //inertial rotation
			pCube->pitchSpeed = mouseDist.y();
		}
		pTimer->start(20); //start animation for inertial rotation
	}
}

void Cube3DWindow::onTimer()
{
    if (pCube->yawSpeed == 0 && pCube->pitchSpeed == 0)
        pTimer->stop(); //stop animation
    else
	{ //slow down the rotation
		if (pCube->yawSpeed >= 1)
			pCube->yawSpeed -= 1;
		else if (pCube->yawSpeed <= -1)
			pCube->yawSpeed += 1;
		else
			pCube->yawSpeed = 0;

		if (pCube->pitchSpeed >= 1)
			pCube->pitchSpeed -= 1;
		else if (pCube->pitchSpeed <= -1)
			pCube->pitchSpeed += 1;
		else
			pCube->pitchSpeed = 0;

        pCube->rotate(pCube->yawSpeed, pCube->pitchSpeed);
	}
}
