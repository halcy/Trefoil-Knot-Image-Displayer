QT += network
QT += opengl
SOURCES += Main.cpp \
    ImageDisplayer.cpp \
    CubeImageDisplay.cpp
HEADERS += ImageDisplayer.h \
    CubeImageDisplay.h
OTHER_FILES += shader.vert \
    shader.frag
