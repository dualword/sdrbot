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

#ifndef SETTINGFORM_H_
#define SETTINGFORM_H_

#include <QtGui>
#include <QTranslator>

#include "app/Context.h"
#include "rcv/Receiver.h"

class SettingForm : public QDialog{
	Q_OBJECT

public:
	SettingForm(QWidget *pParent = 0, QTranslator *translator=0, Context *ctx=0);
	virtual ~SettingForm();

private:
	QPushButton *btncancel,*btnsave;
	QComboBox *lang;
	QComboBox *port, *speed, *dbit, *sbit,*parity,*flow;

    QTranslator *translator;
	Context *ctx;

private Q_SLOTS:
	void save();
	void cancel();

};

#endif /* SETTINGFORM_H_ */
