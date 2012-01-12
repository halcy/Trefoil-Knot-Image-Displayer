QT += network
QT += opengl

SOURCES += Main.cpp \
    ImageDisplayer.cpp \
    CubeImageDisplay.cpp
HEADERS += ImageDisplayer.h \
    CubeImageDisplay.h \
    shaders.h
OTHER_FILES += shader.vert \
    shader.frag
QMAKE_LIBS_OPENGL = -L. -lglew32s -lglu32 -lopengl32
