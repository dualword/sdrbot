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

#include "Receiver.h"

using namespace std;

Receiver::Receiver(std::string str) {
	_portname = str;
	status = off;
	_name = "sdrBot";
	port = 0;

	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(onTick()));

}

Receiver::~Receiver()
{
	if(port) delete port;
}


void Receiver::setPort(AbstractPort* p){
	port = p;
}

AbstractPort* Receiver::getPort() const{
	return port;
}

void Receiver::setMode(int mode){
	try {
		std::string s1 = "MD";
		std::stringstream t;
		t << mode;
		s1 += t.str();
		string s = port->execute(s1);

		getMode();
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}
}

Receiver::Mode Receiver::getMode(){
	Receiver::Mode mode;
	try {

			string cmd = "MD";
			int m = executeCommand(cmd,2,1);

			switch(m){
				case 0: mode=Receiver::WFM; break;
				case 1: mode=Receiver::NFM; break;
				case 6: mode=Receiver::SFM; break;
				case 7: mode=Receiver::WAM; break;
				case 2: mode=Receiver::AM; break;
				case 8: mode=Receiver::NAM; break;
				case 3: mode=Receiver::USB; break;
				case 4: mode=Receiver::LSB; break;
				case 5: mode=Receiver::CW; break;

			}

		Q_EMIT modeChange(mode);
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}

	return mode;
}

void Receiver::setAtt(int att){
	try {
		std::string s1 = "AT";
		std::stringstream t;
		t << att;
		s1 += t.str();
		string s = port->execute(s1);

		getAtt();
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}
}

Receiver::Att Receiver::getAtt(){
	Receiver::Att att;
	try {
		string cmd = "AT";
		int m = executeCommand(cmd,2,1);

		switch(m){
			case 0: att=Receiver::att_off; break;
			case 1: att=Receiver::att_on; break;
		}

		Q_EMIT AttChangeEvent(att);
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}

	return att;
}

void Receiver::setFrequency(Frequency &frequency)
{
	try {
		std::string s1 = "RF";
		s1 += doubletostring(frequency.getFrequency(),5);
		//cout<< "setFrequency:" << s1 << endl;

		port->execute(s1);
		getFrequency();
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}
}

double Receiver::getFrequency(){
	try {
		std::string s1 = "RX";
		std::string s = port->execute(s1);

		double f=0;
		string ss=s.substr(5,10);
		ss = ss.substr(0,4)+"."+ss.substr(4);
		f = QString::fromStdString(ss).toDouble();
		currentFrequency = f;
		Q_EMIT freqChange(f);
		return f;
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}

	return 0;
}

int Receiver::getLevel()
{

	try {
		std::string cmd = "LM";
		int level = executeCommand(cmd,3,3);

		//cout<< "getLevel:" << ss << endl;

		Q_EMIT levelChange(level);
		return level;
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}

	return 0;
}

Receiver::Status Receiver::getStatus(){
	return status;
}

void Receiver::setStatus(Status s){
	this->status = s;
}

void Receiver::connect(){

	try {
		if(port == 0)
			port=new Port(_portname);

		port->open();

//    	port.send("MC2"); // mc2 squelch forced open?

			//check receiver
			std::string s1 = "VF"; //put in 1-VFO mode : VF
			port->execute(s1);
			s1 = "AU0";
			port->execute(s1); //AU0 auto mode is off

	//response for RX in VFO mode:  VF RF0090040000 ST010000 AU0 MD6 AT0  length 38
			s1 = "RX";
			std::string s = port->execute(s1);

			if(s.length() == 38){
				//cout<<"rcv is ok\n";
			}else{
				//cout<<"rcv is not ok\n";
				port->close();
				throw std::runtime_error("No receiver found at "+port->getName());
				return;
			}
			//add regex to check response?
	//		//rcv is ok
			setStatus(Receiver::on);
			Q_EMIT ConnectEvent();
			refresh();
			timer.start(1000);

	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}
}

void Receiver::disconnect(){

	timer.stop();
	Q_EMIT DisconnectEvent();
	setStatus(Receiver::off);

	try {
		std::string s1 = "EX"; //Terminates remote operation via the RS-232
		this->port->execute(s1);

		this->port->close();
	} catch (exception e) {
		//
	}

}

void Receiver::refresh(){
	//use LC RX?
	getLevel();
	getFrequency();
	getMode();
	getAtt();
	getAudioSquelch();
	getLevelSquelch();

}

void Receiver::handleError(string& e)
{
	disconnect();
	string err = "Problems with: " + _portname + "\n" + e;
	Q_EMIT ErrorEvent(err);
}

std::string Receiver::getName() const {
	return _name;
}

void Receiver::scrollLeft(double step){
	currentFrequency -= step;
	Frequency f(currentFrequency);
	this->setFrequency(f);
	getLevel();
}

void Receiver::scrollRight(double step){
	currentFrequency += step;
	Frequency f(currentFrequency);
	this->setFrequency(f);
	getLevel();
}

string Receiver::doubletostring(const double& d, const int& precision){
	std::stringstream t;
	t.precision(precision);
	t << fixed << d;
	std::string str = t.str();
	return str;

}

void Receiver::onTick()
{
	getLevel();
}


void Receiver::setAudioSquelch(int level)
{
	try {
		std::string s1 = "DA";
		std::stringstream t;
		t << level;
		s1 += t.str();
		string s = port->execute(s1);

		getAudioSquelch();
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}
}
int Receiver::getAudioSquelch()
{
	try {
		std::string cmd = "DA";
		int level = executeCommand(cmd,3,3);

		//cout<< "getLevel:" << ss << endl;

		Q_EMIT audioSquelchChange(level);
		return level;
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}

	return 0;
}

void Receiver::setLevelSquelch(int level)
{
	try {
		std::string s1 = "DB";
		std::stringstream t;
		t << level;
		s1 += t.str();
		string s = port->execute(s1);

		getLevelSquelch();
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}
}
int Receiver::getLevelSquelch()
{
	try {
		std::string cmd = "DB";
		int level = executeCommand(cmd,3,3);

		//cout<< "getLevel:" << ss << endl;

		Q_EMIT levelSquelchChange(level);
		return level;
	} catch (exception& e) {
		std::string err= e.what();
		handleError(err);
	}

	return 0;
}

int Receiver::executeCommand(std::string& str, int strstart, int strend)
{
	string ss = "";
	try {
		string s = port->execute(str);
		ss=s.substr(strstart,strend);
	} catch (exception& e) {
		std::string err= "Corrupted response from the receiver.";
		handleError(err);
	}
	return QString::fromStdString(ss).toInt();
}


