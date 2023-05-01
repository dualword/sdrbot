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

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <QObject>
#include <QTimer>

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <time.h>
#include <iomanip>

#include "dev/Port.h"
#include "rcv/Frequency.h"

class Frequency;

class Receiver : public QObject{
	 Q_OBJECT

public:
	enum Mode {WFM=0,NFM=1,SFM=6,WAM=7,AM=2,NAM=8,USB=3,LSB=4,CW=5};
	enum Status{on,off};
	enum Att{att_off=0,att_on=1};

	enum Step {s50Hz=50, s100Hz=100, s100kHz=100000};

	//50 0.05
	//100
	//200
	//500
	//1000
	//2000
	//5000
	//6.250
	//8.330
	//9.000
	//10.000
	//12.500
	//20.000
	//25.000
	//30.000
	//50.000
	//100.000


	Receiver (std::string str);
	virtual ~Receiver();
	void connect();
	void disconnect();
	void refresh();

	//void setError(std::string& str);

	void setPort(AbstractPort *p);
	AbstractPort* getPort() const;

	void setFrequency(Frequency &frequency);
	double getFrequency();

	void setMode(int mode);
	Mode getMode();

	void setAtt(int att);
	Att getAtt();

	int getLevel();

	void setAudioSquelch(int level);
	int getAudioSquelch();

	void setLevelSquelch(int level);
	int getLevelSquelch();

	std::string getName() const;

	Status getStatus();
	void setStatus(Status s);

	void scrollLeft(double);
	void scrollRight(double);

	string doubletostring(const double& d, const int& precision);

private:
	void handleError(std::string& e);
	int executeCommand(std::string& str, int strstart, int strend);

signals:
	void freqChange(const double&);
	void levelChange(int level);
	void levelSquelchChange(int level);
	void audioSquelchChange(int level);
	void modeChange(int mode);
	void AttChangeEvent(int att);
	void ConnectEvent();
	void DisconnectEvent();
	void ErrorEvent(std::string& str);

private slots:
	void onTick();

protected:
	AbstractPort* port;
	Status status;
	std::string _name, _portname;
	double currentFrequency;
	QTimer timer;


};

#endif /* RECEIVER_H_ */
