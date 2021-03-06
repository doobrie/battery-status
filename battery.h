//  battery.h
//
//  Copyright 2012 doobrie (daveyem@live.com)
//
//	This file is part of battery-status.
//
//  battery-status is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  battery-status is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with battery-status.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BATTERY_H
#define BATTERY_H

#include <string>
class Battery
{

public:
	Battery();
	~Battery();

	bool readInfo();
	std::string getBatteryType();
	std::string getDischargeRate();
	std::string getModelNumber();
	std::string getSerialNumber();
	std::string getState();
	std::string getChargingState();
	std::string getRemainingCapacity();
	std::string getRemainingTime();
	std::string getFullCapacity();
	std::string getRate();

private:
	std::string batteryType;
	std::string dischargeRate;
	std::string serialNumber;
	std::string modelNumber;
	std::string state;
	std::string chargingState;
	std::string remainingCapacity;
	std::string fullCapacity;
	std::string rate;
};

#endif // BATTERY_H
