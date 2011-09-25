#include <QtGui>
#include <QtNetwork>
#include <QtOpenGL>

#include "ImageDisplayer.h"
#include "CubeImageDisplay.h"

int main(int argc, char** argv) {
	QApplication app(argc,argv);

	QWidget window;
	window.show();
	window.setWindowTitle(
		QApplication::translate("maintitle", "Trefoil Knot Image Displayer (tm)")
	);

	QHBoxLayout* labelLayoutA = new QHBoxLayout();
	labelLayoutA->addWidget(new QLabel("Image to retrieve: "));

	QLineEdit* urlText = new QLineEdit();
	labelLayoutA->addWidget(urlText);

	QPushButton* goButton = new QPushButton("Grab");
	labelLayoutA->addWidget(goButton);

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addLayout(labelLayoutA);

	CubeImageDisplay* cubeImage = new CubeImageDisplay();
	mainLayout->addWidget(cubeImage);

	ImageDisplayer* disp = new ImageDisplayer(cubeImage,urlText);
	QObject::connect(goButton,SIGNAL(clicked()),disp,SLOT(download()));
	QObject::connect(urlText,SIGNAL(returnPressed()),disp,SLOT(download()));

	window.setLayout(mainLayout);
	window.resize(640,480);

	return app.exec();
}

