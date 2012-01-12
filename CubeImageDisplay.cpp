#define GLEW_STATIC
#include "GL/glew.h"
#include "shaders.h"

#include "CubeImageDisplay.h"
#include <QtGui>
#include <QtDebug>

#include <gl/gl.h>
#include <gl/glu.h>

CubeImageDisplay::CubeImageDisplay() {
	QGLFormat myFormat = QGLFormat::defaultFormat();
	myFormat.setSampleBuffers(true);
	this->setFormat(myFormat);
	this->updateTimer = new QTimer(this);
	QObject::connect( this->updateTimer, SIGNAL(timeout()), this, SLOT(update()) );
	this->updateTimer->start( 15 );
	angle = 0;
}

CubeImageDisplay::~CubeImageDisplay() {
	this->updateTimer->stop();
	delete(this->updateTimer);
}

void CubeImageDisplay::initializeGL() {
	glewInit();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glGenTextures( 1, &this->displayTexture );
	/*this->shader = new QGLShaderProgram(this);
	if(!this->shader->addShaderFromSourceFile(QGLShader::Vertex,"shader.vert")){
		qDebug() << "Problem adding vertex shader: " << this->shader->log();
		exit(0);
	}*/
	/*if(!this->shader->addShaderFromSourceFile(QGLShader::Fragment,"shader.frag")) {
		qDebug() << "Problem adding fragment shader: " << this->shader->log();
		exit(0);
	}*/
	/*QGLShader vertShader(QGLShader::Vertex,this);
	vertShader.compileSourceCode("void main(){ }");
	this->shader->addShaderFromSourceCode(QGLShader::Vertex, "void main(){ }");*/

	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vv = VERT_SH;
	const char* ff = FRAG_SH;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);


	glCompileShader(v);
	glCompileShader(f);

	shaderp = glCreateProgram();

	glAttachShader(shaderp,v);
	glAttachShader(shaderp,f);

	glLinkProgram(shaderp);
}

void CubeImageDisplay::setImage(QImage image) {
	QImage t = QGLWidget::convertToGLFormat( image );
	glBindTexture( GL_TEXTURE_2D, this->displayTexture );
	float maximumAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
}

void CubeImageDisplay::resizeGL(int width, int height) {
	height = height?height:1;

	glViewport(0,0,(GLint)width,(GLint)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CubeImageDisplay::update() {
	this->angle += 0.5;
	this->glDraw();
}

void makeCube() {
	glBegin(GL_QUADS);
		glNormal3f(0,0,-1);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0f,1.0f,-1.0f);

		glNormal3f(0,0,1);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f(-1.0f,-1.0f, 1.0f);

		glNormal3f(-1,0,0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f(-1.0f, 1.0f,-1.0f);

		glNormal3f(1,0,0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0f,-1.0f,-1.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f(1.0f,-1.0f,1.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f(1.0f,1.0f,1.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f(1.0f,1.0f,-1.0f);

		glNormal3f(0,-1,0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(1.0f,-1.0f,1.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f(-1.0f,-1.0f,1.0f);

		glNormal3f(0,1,0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-1.0f,1.0f,-1.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f( 1.0f,1.0f,-1.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f(1.0f,1.0f,1.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f(-1.0f,1.0f,1.0f);
	glEnd();
}

void CubeImageDisplay::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

		/*if(!this->shader->bind()) {
		qDebug() << this->shader->log();
		exit(0);
		}*/
	glUseProgram(shaderp);

	glCullFace(GL_BACK);
	glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glTexCoord2f(-1,-1);
		glVertex3f(-1,-1,-1);
		glTexCoord2f(1,-1);
		glVertex3f( 1,-1,-1);
		glTexCoord2f(1,1);
		glVertex3f( 1, 1,-1);
		glTexCoord2f(-1,1);
		glVertex3f(-1, 1,-1);
	glEnd();
	glClear(GL_DEPTH_BUFFER_BIT);

	glTranslatef(0.0f,0.0f,-5.0f);

	glLineWidth(4.0);

	glColor3f(0.1,0.1,0.1);
	for( int i = 0; i < 20; i++ ) {
		float u = (i/20.0) * 2.0 * M_PI - (angle*0.004);

		float x =
			41.0 * cos(u) -
			18.0 * sin(u) -
			83.0 * cos(2.0 * u) -
			83.0 * sin(2.0 * u) -
			11.0 * cos(3.0 * u) +
			27.0 * sin(3.0 * u);
		x /= 100.0;

		float y =
				36.0 * cos(u) +
				27.0 * sin(u) -
				113.0 * cos(2.0 * u) +
				30.0 * sin(2.0 * u) +
				11.0 * cos(3.0 * u) -
				27.0 * sin(3.0 * u);
		y /= 100;

		float z =
				45.0 * sin(u) -
				30.0 * cos(2.0 * u) +
				113.0 * sin(2.0 * u) -
				11.0 * cos(3.0 * u) +
				27.0 * sin(3.0 * u);
		z /= 100;

		u -= 0.0001;
		float px =
			41.0 * cos(u) -
			18.0 * sin(u) -
			83.0 * cos(2.0 * u) -
			83.0 * sin(2.0 * u) -
			11.0 * cos(3.0 * u) +
			27.0 * sin(3.0 * u);
		px /= 100.0;

		float py =
				36.0 * cos(u) +
				27.0 * sin(u) -
				113.0 * cos(2.0 * u) +
				30.0 * sin(2.0 * u) +
				11.0 * cos(3.0 * u) -
				27.0 * sin(3.0 * u);
		py /= 100;

		float pz =
				45.0 * sin(u) -
				30.0 * cos(2.0 * u) +
				113.0 * sin(2.0 * u) -
				11.0 * cos(3.0 * u) +
				27.0 * sin(3.0 * u);
		pz /= 100;

		glPushMatrix();
		glTranslatef(x,y-0.2,z);

		QVector3D dir(x-px,y-py,z-pz);
		dir.normalize();
		QVector3D axis = QVector3D::crossProduct(dir,QVector3D(0,1,0));
		axis.normalize();
		double theta = acos(QVector3D::dotProduct(dir,QVector3D(0,1,0)));

		glRotatef(-theta*180.0/3.14,axis.x(),axis.y(),axis.z());
		glScalef(0.24,0.24,0.24);
		glRotatef(this->angle-i*200.0,0,1,0);
		// glRotatef(this->angle*1.3,1,0,0);
		makeCube();
		glPopMatrix();

	}

	glCullFace(GL_FRONT);
	glColor3f(1.0,1.0,1.0);
	glBindTexture( GL_TEXTURE_2D, this->displayTexture );

	for( int i = 0; i < 20; i++ ) {
		float u = (i/20.0) * 2.0 * M_PI - (angle*0.004);

		float x =
			41.0 * cos(u) -
			18.0 * sin(u) -
			83.0 * cos(2.0 * u) -
			83.0 * sin(2.0 * u) -
			11.0 * cos(3.0 * u) +
			27.0 * sin(3.0 * u);
		x /= 100.0;

		float y =
				36.0 * cos(u) +
				27.0 * sin(u) -
				113.0 * cos(2.0 * u) +
				30.0 * sin(2.0 * u) +
				11.0 * cos(3.0 * u) -
				27.0 * sin(3.0 * u);
		y /= 100;

		float z =
				45.0 * sin(u) -
				30.0 * cos(2.0 * u) +
				113.0 * sin(2.0 * u) -
				11.0 * cos(3.0 * u) +
				27.0 * sin(3.0 * u);
		z /= 100;

		u -= 0.0001;
		float px =
			41.0 * cos(u) -
			18.0 * sin(u) -
			83.0 * cos(2.0 * u) -
			83.0 * sin(2.0 * u) -
			11.0 * cos(3.0 * u) +
			27.0 * sin(3.0 * u);
		px /= 100.0;

		float py =
				36.0 * cos(u) +
				27.0 * sin(u) -
				113.0 * cos(2.0 * u) +
				30.0 * sin(2.0 * u) +
				11.0 * cos(3.0 * u) -
				27.0 * sin(3.0 * u);
		py /= 100;

		float pz =
				45.0 * sin(u) -
				30.0 * cos(2.0 * u) +
				113.0 * sin(2.0 * u) -
				11.0 * cos(3.0 * u) +
				27.0 * sin(3.0 * u);
		pz /= 100;

		glPushMatrix();
		glTranslatef(x,y-0.2,z);

		QVector3D dir(x-px,y-py,z-pz);
		dir.normalize();
		QVector3D axis = QVector3D::crossProduct(dir,QVector3D(0,1,0));
		axis.normalize();
		double theta = acos(QVector3D::dotProduct(dir,QVector3D(0,1,0)));

		glRotatef(-theta*180.0/3.14,axis.x(),axis.y(),axis.z());
		glScalef(0.22,0.22,0.22);
		glRotatef(this->angle-i*200.0,0,1,0);
		// glRotatef(this->angle*1.3,1,0,0);
		makeCube();
		glPopMatrix();

	}

	glDisable(GL_CULL_FACE);
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBegin(GL_QUADS);
	float px;
	float py;
	float pz;
	for( int i = 0; i < 200; i++ ) {
		float u = (i/200.0) * 2.0 * M_PI - (angle*0.004);
		glColor3f(0.6,0.0,0.8+sin(u)/5.0);

		float x =
			41.0 * cos(u) -
			18.0 * sin(u) -
			83.0 * cos(2.0 * u) -
			83.0 * sin(2.0 * u) -
			11.0 * cos(3.0 * u) +
			27.0 * sin(3.0 * u);
		x /= 100.0;

		float y =
				36.0 * cos(u) +
				27.0 * sin(u) -
				113.0 * cos(2.0 * u) +
				30.0 * sin(2.0 * u) +
				11.0 * cos(3.0 * u) -
				27.0 * sin(3.0 * u);
		y /= 100;

		float z =
				45.0 * sin(u) -
				30.0 * cos(2.0 * u) +
				113.0 * sin(2.0 * u) -
				11.0 * cos(3.0 * u) +
				27.0 * sin(3.0 * u);
		z /= 100;

		if( i > 0 ) {
			glVertex3f(px+0.025,py-0.2,pz);
			glVertex3f(px-0.025,py-0.2,pz);
			glVertex3f(x-0.025,y-0.2,z);
			glVertex3f(x+0.025,y-0.2,z);
		}

		px = x;
		py = y;
		pz = z;
	}
	glEnd();
	glEnable(GL_CULL_FACE);

}

