#  Software License Agreement (BSD License)
#  Copyright (c) 2003-2016, CHAI3D.
#  (www.chai3d.org)
#
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  * Redistributions of source code must retain the above copyright
#  notice, this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above
#  copyright notice, this list of conditions and the following
#  disclaimer in the documentation and/or other materials provided
#  with the distribution.
#
#  * Neither the name of CHAI3D nor the names of its contributors may
#  be used to endorse or promote products derived from this software
#  without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#
#  $Author: seb $
#  $Date: 2014-05-01 18:49:45 +1200 (Thu, 01 May 2014) $
#  $Rev: 1316 $


# shared settings headers
QT          += core gui widgets opengl

INCLUDEPATH += ../Libraries/chai3d-3.2.0/src
INCLUDEPATH += ../Libraries/chai3d-3.2.0/external/Eigen
INCLUDEPATH += ../Libraries/chai3d-3.2.0/external/glew/include
INCLUDEPATH += ../Libraries/chai3d-release/
DEPENDPATH  += .

# platform-specific settings
unix {
  SYSTEM = $$system(uname -s)
  contains (SYSTEM, Linux) {
    OS = lin
  }
  contains (SYSTEM, Darwin) {
    OS = mac
  }

  TEMPLATE        = app
  TARGET          =   CI_TRAC_GUI
  #PRE_TARGETDEPS +=   ../../lib/$$CFG/$$OS-$$ARCH-$$COMPILER/libchai3d.a
  #LIBS           += ../Libraries/chai3d-3.2.0/lib/$$CFG/$$OS-$$ARCH-$$COMPILER -lchai3d

  LIBS           += -L/home/telerobotics/src/Libraries/chai3d-release -lchai3d
  #LIBS           += ../Libraries/chai3d-3.2.0/external/DHD/lib/$$OS-$$ARCH -ldrd
  LIBS           += -L/home/telerobotics/src/Libraries/chai3d-3.2.0/external/DHD/lib/lin-x86_64 -ldrd


  contains (SYSTEM, Linux) {
    DEFINES        += LINUX
    QMAKE_CXXFLAGS += -std=c++0x -Wno-deprecated -Wno-unused-parameter -Wno-uninitialized -Wno-unused-local-typedefs
    LIBS           += -lusb-1.0 -lrt -ldl -lpng -lGLU -lX11 -ljsoncpp  -llapack -lblas
    ICON            = chai3d.ico
    CONFIG         += qt c++11
  }
  contains (SYSTEM, Darwin) {
    DEFINES        += MACOSX
    QMAKE_CXXFLAGS += -std=c++0x -stdlib=libc++
    QMAKE_LFLAGS   += -stdlib=libc++
    LIBS           += -framework CoreFoundation -framework IOKit -framework CoreServices -framework CoreAudio -framework AudioToolbox -framework AudioUnit
    CONFIG         += app_bundle
    ICON            = chai3d.icns
    OSXVER = $$system('sw_vers -productVersion | cut -d . -f 1,2')
    QMAKE_MACOSX_DEPLOYMENT_TARGET = $$OSXVER
    QMAKE_MAC_SDK                  = macosx$$OSXVER
  }
}

# sources
SOURCES   += application.cpp \
    Interface.cpp \
    main.cpp \
    guidedtool.cpp \
    cochleapath.cpp

HEADERS   += Application.h \
    Interface.h \
    ../Libraries/PolarisSpectra/PolarisSpectra.h \
    cornerviews.h \
    ../Libraries/json/allocator.h \
    ../Libraries/json/assertions.h \
    ../Libraries/json/autolink.h \
    ../Libraries/json/config.h \
    ../Libraries/json/forwards.h \
    ../Libraries/json/json.h \
    ../Libraries/json/json_features.h \
    ../Libraries/json/reader.h \
    ../Libraries/json/value.h \
    ../Libraries/json/version.h \
    ../Libraries/json/writer.h \
    APIStructures.h \
    polaristransformmatrix.h \
    guidedtool.h \
    cochleapath.h


    # HEADERS FOR THE CHAI3d LIBRARY


FORMS     += Interface.ui
RESOURCES += Application.qrc \
    application.qrc

INCLUDEPATH += ../Libraries/json
INCLUDEPATH += ../Libraries

unix:!macx: LIBS += -L$$PWD/../Libraries/PolarisSpectra/ -lPolarisSpectraLinux

INCLUDEPATH += $$PWD/../Libraries/PolarisSpectra
DEPENDPATH += $$PWD/../Libraries/PolarisSpectra


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/armadillo/release/ -larmadillo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/armadillo/debug/ -larmadillo
else:unix: LIBS += -L$$PWD/../Libraries/armadillo/ -larmadillo

INCLUDEPATH += $$PWD/../Libraries/armadillo
DEPENDPATH += $$PWD/../Libraries/armadillo
INCLUDEPATH += $$PWD/../Libraries/armadillo/include
INCLUDEPATH += $$PWD/../Libraries/armadillo/include/armadillo_bits
INCLUDEPATH += $$PWD/../Libraries/armadillo/src



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/chai3d-release/release/ -lchai3d
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/chai3d-release/debug/ -lchai3d
#else:unix: LIBS += -L$$PWD/../Libraries/chai3d-release/ -lchai3d

#INCLUDEPATH += $$PWD/../Libraries
#DEPENDPATH += $$PWD/../Libraries

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Libraries/chai3d-release/release/libchai3d.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Libraries/chai3d-release/debug/libchai3d.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Libraries/chai3d-release/release/chai3d.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Libraries/chai3d-release/debug/chai3d.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../Libraries/chai3d-release/libchai3d.a

DISTFILES += \
    json_files/omnimag_settings.json \
    rom_files/8700339.rom \
    rom_files/8700340.rom \
    rom_files/8700449.rom \
    rom_files/CubeOmnimagCenter_8700339.rom \
    stl_devices/CochleaHolder_ROM_STL_TXT/CenterOfCochlea.rom \
    stl_devices/CochleaHolder_ROM_STL_TXT/RoundWindow.rom \
    stl_devices/InsertionDevice_ROM_STL_TXT/AIT_06-29-2017.rom \
    stl_devices/OmniMag_ROM_STL_TXT/OmniMagCenter.rom \
    stl_devices/CochleaHolder_ROM_STL_TXT/cochleaHolderSetup.stl \
    stl_devices/CochleaHolder_ROM_STL_TXT/CochleaTransformation.txt \
    stl_devices/OmniMag_ROM_STL_TXT/Omni_cube_core.STL \
    stl_devices/OmniMag_ROM_STL_TXT/OmniTransformation.txt \
    stl_devices/OmniMag_ROM_STL_TXT/OmniWTracker.stl
