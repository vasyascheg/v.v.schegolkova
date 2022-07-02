QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/include" \
    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/atlmfc/include" \
    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS/include" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/ucrt" \
    "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS/UnitTest/include" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/um" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/shared" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/winrt" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/cppwinrt" \
    "C:/Program Files (x86)/Windows Kits/NETFXSDK/4.8/Include/um" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/km/crt" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/km" \
    "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/shared"

LIBS += \
    # "C:/Program Files (x86)/Windows Kits/10/lib/10.0.22000.0/km/x64/ntoskrnl.lib" \
    # "C:/Program Files (x86)/Windows Kits/10/lib/10.0.22000.0/km/x64/hal.lib" \
    # "C:/Program Files (x86)/Windows Kits/10/lib/10.0.22000.0/km/x64/wmilib.lib" \
    # "C:/Program Files (x86)/Windows Kits/10/lib/10.0.22000.0/km/x64/fltMgr.lib" \
    "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/um/x64/fltLib.lib" \
    "Advapi32.lib"

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

MOC_DIR = build_tmp/moc
RCC_DIR = build_tmp/rcc
#UI_DIR = build_tmp/ui
win32:OBJECTS_DIR = build_tmp/o/win32

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

RESOURCES += \
    resources.qrc
