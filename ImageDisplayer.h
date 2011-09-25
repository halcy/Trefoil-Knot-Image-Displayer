#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QtGui>
#include <QtNetwork>
#include "CubeImageDisplay.h"

class ImageDisplayer : public QObject
{
Q_OBJECT

private:
	CubeImageDisplay* to;
	QLineEdit* fromUrl;
	QNetworkAccessManager* manager;

public:
	ImageDisplayer(CubeImageDisplay* displayTo,QLineEdit* urlFrom);

public slots:
	void display(QNetworkReply* fromHandle);
	void download();
};

#endif // IMAGEDISPLAYER_H
