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

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <time.h>

#include "rcv/Receiver.h"

class Receiver;

class Context : public QObject{
	 Q_OBJECT

public:
	Context();
	virtual ~Context();
	void init();
	void close();
	long uptime();//uptime in seconds
	Receiver* getReceiver() const;
	void setReceiver(Receiver* receiver);

Q_SIGNALS:
	void ReceiverChangeEvent();

private:
	time_t start;
	Receiver *receiver;

};

#endif /* CONTEXT_H_ */
