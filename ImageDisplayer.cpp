#include "ImageDisplayer.h"
#include <stdio.h>

ImageDisplayer::ImageDisplayer(CubeImageDisplay* displayTo,QLineEdit* urlFrom) {
	this->to = displayTo;
	this->fromUrl = urlFrom;
	this->manager = new QNetworkAccessManager();
	QObject::connect(this->manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(display(QNetworkReply*)));
}

void ImageDisplayer::display(QNetworkReply *fromHandle) {
	QImageReader imageReader(fromHandle);
	this->to->setImage(imageReader.read());
}

void ImageDisplayer::download() {
	manager->get(QNetworkRequest(QUrl(this->fromUrl->text())));
}
