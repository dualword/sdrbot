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

#ifndef PORT_H_
#define PORT_H_

#include <iostream>
#include <cstdlib>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "AbstractPort.h"

using namespace std;

class Port : public AbstractPort
{
public:
	Port(const std::string& port);
	void open();
	void close();
	std::string execute(const std::string &s);

private:
	void write(const char *s);
	string read();

private:
	termios oldtio,newtio;

};

#endif /*PORT_H_*/
