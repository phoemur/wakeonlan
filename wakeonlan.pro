TEMPLATE = app
TARGET = wakeonlan
INCLUDEPATH += .
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += MainWindow.h \
           3rdparty/ClientSocket.h \
           3rdparty/Socket.h \
           3rdparty/SocketException.h
FORMS += MainWindow.ui
SOURCES += main.cpp MainWindow.cpp 3rdparty/ClientSocket.cpp 3rdparty/Socket.cpp
RESOURCES += icons/icons.qrc

# Custom config
QT += widgets
QMAKE_CXXFLAGS += -std=c++14
CONFIG += release
QMAKE_POST_LINK=$(STRIP) $(TARGET)
target.path = /usr/local/bin/wakeonlan_dir
INSTALLS += target 

link_com.path = /usr/local/bin
link_com.commands = ln -s /usr/local/bin/wakeonlan_dir/wakeonlan /usr/local/bin/wakeonlan
link_com.depends = install_target

QMAKE_EXTRA_TARGETS += link_com
INSTALLS += link_com
