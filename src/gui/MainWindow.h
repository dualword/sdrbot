/*
 * Copyright (C) 2012 Alexander Busorgin
 *
 *	This file is part of sdrBot.
 *
 *	sdrBot is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	sdrBot is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with sdrBot.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <functional>
#include <unistd.h>
#include <cstdio>

#include <QMainWindow>
#include <QtGui>

#include "gui/SettingForm.h"
#include "gui/TuneForm.h"

#include "app/Context.h"
#include "rcv/Receiver.h"

const string version = "1.0.0 alpha";

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
	MainWindow(Context *ctx, QTranslator *translator);
	virtual ~MainWindow();


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void disableControls();
    void enableControls();
    void createTrayIcon();
    void closeEvent(QCloseEvent *); // Overriding the window's close event
    void setSlots();
    void scrollLeft();
    void scrollRight();
    void scrollUp();
    void scrollDown();
    void updateEventFilters( QObject* obj );


private:
    QTranslator *translator;
	Context *ctx;
	Receiver *receiver;
	QLineEdit *display;
	QString *buffer;
	QPushButton *btne,*btnc,*btnd,*btnz,*btn1,*btn2,*btn3,*btn4,*btn5,*btn6,
		*btn7,*btn8,*btn9, *sqAleft, *sqAright, *sqLleft, *sqLright;
	QPushButton *createButton(const QString &text, const char *member);
	QAction *btnConnect, *btnTune;
	QProgressBar *progress;
	QComboBox *modeBox, *attBox, *stepBox;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QLabel *mStateRcv, *lblMhz, *lblAudio, *lblLevel, *lblLvl, *lblSqL, *lblSqA;
    QAction *settingsAction, *aboutAction ;
	TuneForm    *tuneForm;
	double step;
	QSlider *audioSquelch, *levelSquelch;
	bool isHidden;

private Q_SLOTS:
	void quit1();
	void buttonClicked();
	void showAboutForm();
	void showSettingForm();
    void showTuneForm ();
    void connectPort();
	void changeMode();
	void changeAtt();
	void changeStep();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
	void changeLevelSquelch(int level);
	void changeAudioSquelch(int level);
	void scrollLevelSquelchLeft();
	void scrollAudioSquelchLeft();
	void scrollLevelSquelchRight();
	void scrollAudioSquelchRight();

	void onFreqChange(const double&);
	void onLevelChange(int level);
	void onModeChange(int mode);
	void onAttChange(int att);
	void onConnect();
	void onDisconnect();
	void onError(std::string& str);
	void onReceiverChange();
	void onLevelSquelchChange(int level);
	void onAudioSquelchChange(int level);


};

#endif /* MAINWINDOW_H_ */
