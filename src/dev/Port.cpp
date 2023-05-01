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

#include "Port.h"

Port::Port(const std::string& port): AbstractPort(port)
{
	lock = new QReadWriteLock(QReadWriteLock::Recursive);
}

void Port::open()
{
	fd = ::open(_portname.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1){
		throw port_exception("Unable to open " + _portname);
	}
	fcntl(fd, F_SETFL, 0);

	tcgetattr(fd,&oldtio);
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = B19200;
	newtio.c_cflag |= CS8;
	newtio.c_cflag |= CREAD;
	newtio.c_cflag |= CLOCAL;
	newtio.c_iflag = IGNPAR | IGNBRK;

	newtio.c_oflag = 0;
	newtio.c_lflag = 0;

	newtio.c_cc[VTIME] = 10;

    tcsetattr(fd,TCSANOW,&newtio);
    tcflush(fd, TCOFLUSH);
    tcflush(fd, TCIFLUSH);
}

void Port::close(){
	tcsetattr(fd, TCSANOW, &oldtio);
    tcflush(fd, TCOFLUSH);
    tcflush(fd, TCIFLUSH);
    ::close(fd);
    fd = -1;
}

std::string Port::read(){
	char buffer[255];
	char *bufptr;
	int  nbytes;

	bufptr = buffer;
	while ((nbytes = ::read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0)
	{
	  bufptr += nbytes;
	  if (bufptr[-1] == '\n' || bufptr[-1] == '\r')
		break;
	}

	*bufptr = '\0';

	return std::string (buffer);
}

void Port::write(const char *s){
	int length = strlen(s);
	int n = ::write(fd, s, length );

    if (n < 0)
    	throw port_exception("");

	n = ::write(fd, "\r\n", 2);
	return;
}

std::string Port::execute(const std::string &s){
	lock->lockForWrite();

	string str;
	try {
		write(const_cast<char *>(s.c_str()));
		str= read();
	} catch (exception& e) {
		lock->unlock();
		throw port_exception("Unable to send commands to " + _portname);
	}

	lock->unlock();

	return str;
}
