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

#include "Context.h"

Context::Context() {
	start = time(0);
	receiver = 0;
}

Context::~Context() {
	if(receiver) delete receiver;
}

void Context::init() {
	string s = "/dev/ttyS1";
	Receiver* r = new Receiver(s);
	setReceiver(r);
}

void Context::close() {
	//cout << "closing..."<< "uptime:"<< difftime( time(0), start ) <<"\n";

}

Receiver* Context::getReceiver() const{
	return receiver;
}

void Context::setReceiver(Receiver* receiver){
	if(this->receiver != 0){
		delete this->receiver;
		this->receiver = 0;
	}
	this->receiver = receiver;
	Q_EMIT ReceiverChangeEvent();
}

long Context::uptime() {
	return difftime( time(0), start );
}

