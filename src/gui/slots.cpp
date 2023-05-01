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


#include "MainWindow.h"

void MainWindow::setSlots()
{

	//context events
	QObject::connect(ctx, SIGNAL(ReceiverChangeEvent()),
	        this, SLOT(onReceiverChange()));

	//receiver


	//toolbar
	QObject::connect(btnConnect,SIGNAL(triggered()), this, SLOT(connectPort()));

	//menu
	QObject::connect(settingsAction,SIGNAL(triggered()), this, SLOT(showSettingForm()));
	QObject::connect(aboutAction,SIGNAL(triggered()), this, SLOT(showAboutForm()));

	//actions
    QObject::connect(modeBox, SIGNAL(activated(int)),this, SLOT(changeMode()));
    QObject::connect(attBox, SIGNAL(activated(int)),this, SLOT(changeAtt()));
    QObject::connect(stepBox, SIGNAL(activated(int)),this, SLOT(changeStep()));
    QObject::connect(levelSquelch, SIGNAL(valueChanged(int)),this, SLOT(changeLevelSquelch(int)));
    QObject::connect(audioSquelch, SIGNAL(valueChanged(int)),this, SLOT(changeAudioSquelch(int)));

    QObject::connect(sqAleft, SIGNAL(clicked()), this, SLOT(scrollAudioSquelchLeft()));
    QObject::connect(sqAright, SIGNAL(clicked()), this, SLOT(scrollAudioSquelchRight()));
    QObject::connect(sqLleft, SIGNAL(clicked()), this, SLOT(scrollLevelSquelchLeft()));
    QObject::connect(sqLright, SIGNAL(clicked()), this, SLOT(scrollLevelSquelchRight()));

    	//forms
	QObject::connect(btnTune, SIGNAL(triggered()), SLOT(showTuneForm()));






}

