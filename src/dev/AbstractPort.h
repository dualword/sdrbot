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

#ifndef ABSTRACTPORT_H_
#define ABSTRACTPORT_H_

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <exception>

#include <QReadWriteLock>

class port_exception: public std::runtime_error
{
public:
	port_exception(const std::string& arg): runtime_error(arg) {}
};

class AbstractPort {

public:
	AbstractPort(const std::string& port);
	virtual ~AbstractPort();
	virtual void open();
	virtual void close();
	std::string getName() const;
	virtual std::string execute(const std::string &s);

protected:
	int fd;
	std::string _portname;
	QReadWriteLock *lock;

private:


};

#endif /* ABSTRACTPORT_H_ */
