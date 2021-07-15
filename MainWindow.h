#pragma once
#include <QtWidgets/QMainWindow.h>
#include <QtWidgets/QPushButton.h>

#include "Cube3DWindow.h"

class MainWindow :
	public QMainWindow
{
   Q_OBJECT
private:
	Cube3DWindow* pCube3DWindow;
	QPushButton* pButton;

private slots:
	void addCube();

public:
	MainWindow();
};

