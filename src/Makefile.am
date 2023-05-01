AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@

bin_PROGRAMS=sdrbotdesktop

sdrbotdesktop_SOURCES=app/main.cpp app/Context.h app/Context.cpp app/moc_Context.cpp \
	dev/AbstractPort.h dev/AbstractPort.cpp dev/Port.h dev/Port.cpp \
	gui/MainWindow.h gui/MainWindow.cpp gui/SettingForm.h gui/SettingForm.cpp \
	gui/slots.cpp gui/moc_MainWindow.cpp gui/moc_SettingForm.cpp \
	gui/TuneForm.h gui/TuneForm.cpp gui/moc_TuneForm.cpp\
	rcv/Receiver.h rcv/Receiver.cpp rcv/moc_Receiver.cpp \
	rcv/Frequency.h rcv/Frequency.cpp rcv/Step.h rcv/Step.cpp \
	sdrbotdesktop.cpp
			
#TRANSLATIONS = lang/prog_ru.ts \
#       lang/prog_fr.ts \
#       lang/prog_es.ts lang/prog_de.ts

RESOURCES = sdrbotdesktop.qrc images/tray-icon.svg
					
sdrbotdesktop_moc_SOURCES = moc_Context.cpp moc_Receiver.cpp moc_TuneForm.cpp

moc_%.cpp: %.h
	moc $< -o $@

sdrbotdesktop.cpp: 
	rcc sdrbotdesktop.qrc -o sdrbotdesktop.cpp
			
CLEANFILES = $(filter moc_%.cpp,$(sdrbotdesktop_moc_SOURCES))

