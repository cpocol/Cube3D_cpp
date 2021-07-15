#include <QtWidgets/QWidget.h>
#include <QtWidgets/QGridLayout.h>

#include "MainWindow.h"

MainWindow::MainWindow()
{
	//Cube Window
	pCube3DWindow = new Cube3DWindow;
    QWidget* pWidget3D = QWidget::createWindowContainer(pCube3DWindow);

	pButton = new QPushButton("Add Cube");
	connect(pButton, SIGNAL(clicked(bool)), this, SLOT(addCube()));

	QWidget* pCentral_widget = new QWidget;
	QGridLayout* pCentral_widget_layout = new QGridLayout;
	pCentral_widget_layout->addWidget(pButton, 0, 1, 1, 1);
	pCentral_widget_layout->addWidget(pWidget3D, 1, 0, 2, 3);
	pCentral_widget->setLayout(pCentral_widget_layout);

	resize(700, 700);
	setWindowTitle("Application");
	show();
	setCentralWidget(pCentral_widget); //call it after show(), in order to avoid "QOpenGLContext::swapBuffers() called with non-exposed window, behavior is undefined"
}

void MainWindow::addCube()
{
    pButton->setEnabled(false);
	pCube3DWindow->addCube();
}
