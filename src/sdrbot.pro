
HEADERS = app/Context.h \
		dev/AbstractPort.h dev/Port.h \
		gui/MainWindow.h gui/SettingForm.h gui/TuneForm.h \
		rcv/Receiver.h rcv/Frequency.h rcv/Step.h
		
SOURCES = app/main.cpp app/Context.cpp  \
	dev/AbstractPort.cpp dev/Port.cpp \
	gui/MainWindow.cpp gui/SettingForm.cpp \
	gui/slots.cpp   \
	gui/TuneForm.cpp \
	rcv/Receiver.cpp  \
	rcv/Frequency.cpp rcv/Step.cpp
	
QMAKE_MOC_SRC=app/moc_Context.cpp gui/moc_MainWindow.cpp \
				gui/moc_SettingForm.cpp gui/moc_TuneForm.cpp \
				rcv/moc_Receiver.cpp
				
CONFIG += qt

RESOURCES = sdrbotdesktop.qrc

TARGET = sdrbotdesktop

QMAKE_CXXFLAGS = -std=c++0x

