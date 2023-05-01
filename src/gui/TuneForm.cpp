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

#include "TuneForm.h"

TuneForm::TuneForm(QWidget *pParent) : QDialog(pParent)
{
	this->setWindowTitle("Search");

    QVBoxLayout *lay = new QVBoxLayout(this);

	QLineEdit *vfo1 = new QLineEdit;
	QLineEdit *vfo2 = new QLineEdit;
	QLineEdit *freq = new QLineEdit;
	QPushButton *btnStart = new QPushButton("Start");
	QPushButton *btnPause = new QPushButton("Pause");
	QPushButton *btnStop = new QPushButton("Stop");
	QPushButton *btnSkip = new QPushButton("Skip");
	QPushButton *btnPass = new QPushButton("Pass");

    lay->addWidget(vfo1);
    lay->addWidget(freq);
    lay->addWidget(vfo2);
    lay->addWidget(btnStart);
    lay->addWidget(btnPause);
    lay->addWidget(btnStop);
    lay->addWidget(btnSkip);
    lay->addWidget(btnPass);


}

TuneForm::~TuneForm() {

}

