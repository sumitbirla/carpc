#############################################################################
# Makefile for building: carpc-qt
# Generated by qmake (1.05a) (Qt 3.1.2) on: Sat Nov  6 09:33:59 2004
# Project:  carpc-qt.pro
# Template: app
# Command: $(QMAKE) -o Makefile carpc-qt.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2  -DQT_NO_DEBUG
CXXFLAGS = -pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2  -DQT_NO_DEBUG
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I$(QTDIR)/mkspecs/default -I. -I. -I$(QTDIR)/include
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS)  -Wl,-rpath,$(QTDIR)/lib -L$(QTDIR)/lib -lqte-mt
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY) -p
COPY_DIR = $(COPY) -pR
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = fft.h \
		flatbutton.h \
		GPSSensor.hpp \
		id3tag.h \
		mainwidget.h \
		mp3widget.h \
		musicbutton.h \
		photowidget.h \
		radiowidget.h \
		visualizer.h \
		VolumeControl.h \
		volumedisplay.h
SOURCES = fft.cpp \
		flatbutton.cpp \
		GPSSensor.cpp \
		hello.cpp \
		id3tag.cpp \
		mainwidget.cpp \
		mp3widget.cpp \
		musicbutton.cpp \
		photowidget.cpp \
		radiowidget.cpp \
		visualizer.cpp \
		VolumeControl.cpp \
		volumedisplay.cpp
OBJECTS = fft.o \
		flatbutton.o \
		GPSSensor.o \
		hello.o \
		id3tag.o \
		mainwidget.o \
		mp3widget.o \
		musicbutton.o \
		photowidget.o \
		radiowidget.o \
		visualizer.o \
		VolumeControl.o \
		volumedisplay.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = moc_flatbutton.cpp \
		moc_id3tag.cpp \
		moc_mainwidget.cpp \
		moc_mp3widget.cpp \
		moc_musicbutton.cpp \
		moc_photowidget.cpp \
		moc_radiowidget.cpp \
		moc_visualizer.cpp \
		moc_VolumeControl.cpp \
		moc_volumedisplay.cpp
OBJMOC = moc_flatbutton.o \
		moc_id3tag.o \
		moc_mainwidget.o \
		moc_mp3widget.o \
		moc_musicbutton.o \
		moc_photowidget.o \
		moc_radiowidget.o \
		moc_visualizer.o \
		moc_VolumeControl.o \
		moc_volumedisplay.o
DIST	   = carpc-qt.pro
QMAKE_TARGET = carpc-qt
DESTDIR  = 
TARGET   = carpc-qt

first: all
####### Implicit rules

.SUFFIXES: .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

mocables: $(SRCMOC)

$(MOC): 
	( cd $(QTDIR)/src/moc ; $(MAKE) )

Makefile: carpc-qt.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile carpc-qt.pro
qmake: 
	@$(QMAKE) -o Makefile carpc-qt.pro

dist: 
	@mkdir -p .tmp/carpc-qt && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/carpc-qt/ && ( cd `dirname .tmp/carpc-qt` && $(TAR) carpc-qt.tar carpc-qt && $(GZIP) carpc-qt.tar ) && $(MOVE) `dirname .tmp/carpc-qt`/carpc-qt.tar.gz . && $(DEL_FILE) -r .tmp/carpc-qt

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:

yaccclean:
lexclean:
clean: mocclean
	-$(DEL_FILE) $(OBJECTS) 
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

fft.o: fft.cpp fft.h

flatbutton.o: flatbutton.cpp flatbutton.h

GPSSensor.o: GPSSensor.cpp GPSSensor.hpp

hello.o: hello.cpp mainwidget.h \
		VolumeControl.h \
		volumedisplay.h \
		radiowidget.h \
		mp3widget.h \
		photowidget.h \
		visualizer.h \
		flatbutton.h \
		fft.h \
		musicbutton.h

id3tag.o: id3tag.cpp id3tag.h

mainwidget.o: mainwidget.cpp mainwidget.h \
		flatbutton.h \
		VolumeControl.h \
		volumedisplay.h \
		radiowidget.h \
		mp3widget.h \
		photowidget.h \
		visualizer.h \
		fft.h \
		musicbutton.h

mp3widget.o: mp3widget.cpp mp3widget.h \
		id3tag.h \
		musicbutton.h \
		flatbutton.h

musicbutton.o: musicbutton.cpp musicbutton.h

photowidget.o: photowidget.cpp photowidget.h \
		flatbutton.h

radiowidget.o: radiowidget.cpp radiowidget.h \
		visualizer.h \
		flatbutton.h \
		fft.h

visualizer.o: visualizer.cpp visualizer.h \
		fft.h

VolumeControl.o: VolumeControl.cpp VolumeControl.h

volumedisplay.o: volumedisplay.cpp volumedisplay.h

moc_flatbutton.o: moc_flatbutton.cpp flatbutton.h 

moc_id3tag.o: moc_id3tag.cpp id3tag.h 

moc_mainwidget.o: moc_mainwidget.cpp mainwidget.h VolumeControl.h \
		volumedisplay.h \
		radiowidget.h \
		mp3widget.h \
		photowidget.h \
		visualizer.h \
		flatbutton.h \
		fft.h \
		musicbutton.h

moc_mp3widget.o: moc_mp3widget.cpp mp3widget.h musicbutton.h \
		flatbutton.h

moc_musicbutton.o: moc_musicbutton.cpp musicbutton.h 

moc_photowidget.o: moc_photowidget.cpp photowidget.h flatbutton.h

moc_radiowidget.o: moc_radiowidget.cpp radiowidget.h visualizer.h \
		flatbutton.h \
		fft.h

moc_visualizer.o: moc_visualizer.cpp visualizer.h fft.h

moc_VolumeControl.o: moc_VolumeControl.cpp VolumeControl.h 

moc_volumedisplay.o: moc_volumedisplay.cpp volumedisplay.h 

moc_flatbutton.cpp: $(MOC) flatbutton.h
	$(MOC) flatbutton.h -o moc_flatbutton.cpp

moc_id3tag.cpp: $(MOC) id3tag.h
	$(MOC) id3tag.h -o moc_id3tag.cpp

moc_mainwidget.cpp: $(MOC) mainwidget.h
	$(MOC) mainwidget.h -o moc_mainwidget.cpp

moc_mp3widget.cpp: $(MOC) mp3widget.h
	$(MOC) mp3widget.h -o moc_mp3widget.cpp

moc_musicbutton.cpp: $(MOC) musicbutton.h
	$(MOC) musicbutton.h -o moc_musicbutton.cpp

moc_photowidget.cpp: $(MOC) photowidget.h
	$(MOC) photowidget.h -o moc_photowidget.cpp

moc_radiowidget.cpp: $(MOC) radiowidget.h
	$(MOC) radiowidget.h -o moc_radiowidget.cpp

moc_visualizer.cpp: $(MOC) visualizer.h
	$(MOC) visualizer.h -o moc_visualizer.cpp

moc_VolumeControl.cpp: $(MOC) VolumeControl.h
	$(MOC) VolumeControl.h -o moc_VolumeControl.cpp

moc_volumedisplay.cpp: $(MOC) volumedisplay.h
	$(MOC) volumedisplay.h -o moc_volumedisplay.cpp

####### Install

install: all 

uninstall: 

