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

#include <QApplication>
#include <QTranslator>

#include "Context.h"
#include "gui/MainWindow.h"

int main(int argc, char *argv[])
{
	int ret = 0;
	Context ctx;
	QApplication app(argc, argv);
	QTranslator translator;

	try {
		QString filename = QString(":prog_en");
		translator.load(filename);
		app.installTranslator(&translator);

		MainWindow mainWindow(&ctx, &translator);
		ctx.init();

		mainWindow.show();
		ret = app.exec();
	} catch (exception& e) {
		cout << e.what() << endl;
	}


	return ret;

}


