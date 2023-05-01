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

#include "SettingForm.h"

SettingForm::SettingForm(QWidget *pParent, QTranslator *translator, Context *ctx) : QDialog(pParent)
{
	this->translator = translator;
	this->ctx = ctx;

	lang = new QComboBox();
	lang->addItem("English","en");
//	lang->addItem(QString::fromUtf8("Deutsch"),"de");
//	lang->addItem(QString::fromUtf8("Español"),"es");
//	lang->addItem(QString::fromUtf8("Français"),"fr");
//	lang->addItem(QString::fromUtf8("\u0420\u0443\u0441\u0441\u043A\u0438\u0439"),"ru");

	QComboBox *receiver = new QComboBox();
	receiver->addItem("AR8200");
	receiver->addItem("AR8600");

	port = new QComboBox();
	speed = new QComboBox();
	dbit = new QComboBox();
	sbit = new QComboBox();
	parity = new QComboBox();
	flow = new QComboBox();

    QGridLayout *grid = new QGridLayout;

    btnsave = new QPushButton(tr("Save"), this);
    grid->addWidget(btnsave,0,0);
	QObject::connect(btnsave,SIGNAL(clicked()), this, SLOT(save()));

    btncancel = new QPushButton(tr("Cancel"), this);
    grid->addWidget(btncancel,0,1);
	QObject::connect(btncancel,SIGNAL(clicked()), this, SLOT(cancel()));

	//language
	//receiver
	//port
	//speed
	//data bits
	//stop bits
	//parity
	//flow control


    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(lang);
    lay->addWidget(receiver);



    QDir dir("/dev");
    QStringList filters;
    filters << "ttyS*" << "ttyUSB*";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files | QDir::System);
    QFileInfoList list = dir.entryInfoList();
    for (int i=0; i< list.size(); i++)
    {
    	port->addItem(list.at(i).canonicalFilePath (),i);
    }

    lay->addWidget(port);
    lay->addWidget(speed);
    //speed->addItem("4800");
   // speed->addItem("9600");
    speed->addItem("19200");

    lay->addWidget(dbit);
    dbit->addItem("8");

    lay->addWidget(sbit);
    sbit->addItem("2");

    lay->addWidget(parity);
    parity->addItem("None");

    lay->addWidget(flow);
    flow->addItem("Xon/Xoff");

    lay->addLayout(grid);

	//this->setExtension(lay);

}

SettingForm::~SettingForm() {

}

void SettingForm::save() {

	//change language
	translator->load(":prog_"+lang->itemData(lang->currentIndex()).toString());
	//update gui

	//change receiver
	std::string s = port->itemText(port->currentIndex()).toStdString();
	Receiver* receiver = new Receiver(s);

	//receiver->reconnect();
	ctx->setReceiver(receiver);

	//save settings

	QDialog::accept();

}


void SettingForm::cancel() {
	QDialog::reject();
}
