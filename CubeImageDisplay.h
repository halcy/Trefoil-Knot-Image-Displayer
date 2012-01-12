#ifndef CUBEIMAGEDISPLAY_H
#define CUBEIMAGEDISPLAY_H

#include <QGLWidget>
#include <QObject>
#include <QGLShaderProgram>

class CubeImageDisplay : public QGLWidget {
Q_OBJECT

public:
    CubeImageDisplay();
	~CubeImageDisplay();
	void paintGL();
	void initializeGL();
	void setImage(QImage image);
	void resizeGL(int width, int height);

private:
	GLuint displayTexture;
	QTimer* updateTimer;
	float angle;
	QGLShaderProgram* shader;
	GLuint shaderp;

private slots:
	void update();

};

#endif // CUBEIMAGEDISPLAY_H
