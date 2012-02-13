//  battery.cc
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

#include "battery.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

Battery::Battery()
{
}

Battery::~Battery()
{
}

bool Battery::readInfo()
{
	FILE* fpInfo;
	FILE* fpState;
	char fileInfoBuffer[4096];
	char fileStateBuffer[4096];
	char lineBuffer[4096];
	size_t bytes_read;
	char* match;

	/* Read in the information data. */
	fpInfo = fopen("/proc/acpi/battery/BAT0/info", "r");
	bytes_read = fread(fileInfoBuffer, 1, sizeof(fileInfoBuffer), fpInfo);
	fclose(fpInfo);
	if ((bytes_read == 0) || (bytes_read==sizeof(fileInfoBuffer)))
		return false;

	/* Read in the state data. */
	fpState = fopen("/proc/acpi/battery/BAT0/state", "r");
	bytes_read = fread(fileStateBuffer, 1, sizeof(fileStateBuffer), fpState);
	fclose(fpState);
	if ((bytes_read == 0) || (bytes_read==sizeof(fileStateBuffer)))
		return false;


	match = strstr(fileInfoBuffer, "model number");
	sscanf(match, "model number: %s", lineBuffer);
	modelNumber = lineBuffer;

	match = strstr(fileInfoBuffer, "serial number");
	sscanf(match, "serial number: %s", lineBuffer);
	serialNumber = lineBuffer;

	match = strstr(fileStateBuffer, "remaining capacity");
	sscanf(match, "remaining capacity: %s", lineBuffer);
	remainingCapacity = lineBuffer;

	match = strstr(fileInfoBuffer, "last full capacity");
	sscanf(match, "last full capacity: %s", lineBuffer);
	fullCapacity = lineBuffer;

	match = strstr(fileStateBuffer, "charging state");
	sscanf(match, "charging state: %s", lineBuffer);
	lineBuffer[0] = toupper(lineBuffer[0]);
	chargingState = lineBuffer;

	match = strstr(fileInfoBuffer, "battery type");
	sscanf(match, "battery type: %s", lineBuffer);
	batteryType = lineBuffer;

	return true;
}

std::string Battery::getBatteryType()
{
	if (batteryType == "LION")
		return "Lithium Ion";
	else
		return batteryType;	
}

std::string Battery::getModelNumber()
{
	return modelNumber;
}

std::string Battery::getSerialNumber()
{
	return serialNumber;
}

std::string Battery::getChargingState()
{
	return chargingState;
}

std::string Battery::getFullCapacity()
{
	return fullCapacity + " mWh";
}

std::string Battery::getRemainingCapacity()
{
	float remain = atof(remainingCapacity.c_str());
	float full = atof(fullCapacity.c_str());
	int percent = 100.0 * remain / full;
	char szBuffer[256];
	sprintf(szBuffer, "%s mWh (%d %%)", remainingCapacity.c_str(), percent);
	return szBuffer;
}