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

#ifndef STEP_H_
#define STEP_H_

class Step {
public:
	Step(double ff);
	virtual ~Step();
	const double getStep();
	void setStep(double);

private:
	double f;

};

#endif /* STEP_H_ */

//50
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
