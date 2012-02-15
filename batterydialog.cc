//  batterydialog.cc
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

#include "batterydialog.h"
#include "battery.h"
#include <iostream>
#include <time.h>

BatteryDialog::BatteryDialog(Gtk::Main kit)
{
	pDialog = 0;

	//Load the GtkBuilder file and instantiate its widgets:
	refBuilder = Gtk::Builder::create();
	try
	{
		refBuilder->add_from_file("battery-status.glade");
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
	}
	catch(const Glib::MarkupError& ex)
	{
		std::cerr << "MarkupError: " << ex.what() << std::endl;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
	}
  
	//Get the GtkBuilder-instantiated Dialog:
	refBuilder->get_widget("battery_dialog", pDialog);

	if (pDialog)
	{  
		Gtk::Button *pRefreshButton = 0;
		refBuilder->get_widget("refresh_button", pRefreshButton);
		pRefreshButton->signal_clicked().connect(sigc::mem_fun(this, &BatteryDialog::refreshButton_clicked));
	
		Gtk::Button *pQuitButton = 0;
		refBuilder->get_widget("quit_button", pQuitButton);
		pQuitButton->signal_clicked().connect(sigc::mem_fun(this, &BatteryDialog::quitButton_clicked));

		updateBatteryInfo();
	
		kit.run(*pDialog);
	}
	else
	{
		std::cout << "Unable to load main UI." << std::endl;
	}

}

BatteryDialog::~BatteryDialog()
{
}

void BatteryDialog::refreshButton_clicked()
{
	updateBatteryInfo();
}

void BatteryDialog::quitButton_clicked()
{
	pDialog->hide();	
}

void BatteryDialog::updateBatteryInfo()
{
	Battery* pBattery = new Battery();
	if (pBattery->readInfo()==true)
	{
		Gtk::Label *pModelNumberLabel = 0;
		refBuilder->get_widget("modelnumber_label", pModelNumberLabel);
		pModelNumberLabel->set_text(pBattery->getModelNumber());

		Gtk::Label *pSerialNumberLabel = 0;
		refBuilder->get_widget("serialnumber_label", pSerialNumberLabel);
		pSerialNumberLabel->set_text(pBattery->getSerialNumber());

		Gtk::Label *pChargingStateLabel = 0;
		refBuilder->get_widget("chargingstate_label", pChargingStateLabel);
		pChargingStateLabel->set_text(pBattery->getChargingState());

		Gtk::Label *pBatteryTypeLabel = 0;
		refBuilder->get_widget("batterytype_label", pBatteryTypeLabel);
		pBatteryTypeLabel->set_text(pBattery->getBatteryType());

		Gtk::Label *pRemainingCapacityLabel = 0;
		refBuilder->get_widget("remainingcapacity_label", pRemainingCapacityLabel);
		pRemainingCapacityLabel->set_text(pBattery->getRemainingCapacity());

		Gtk::Label *pFullCapacityLabel = 0;
		refBuilder->get_widget("fullcapacity_label", pFullCapacityLabel);
		pFullCapacityLabel->set_text(pBattery->getFullCapacity());

		Gtk::Label *pRemainingTime = 0;
		refBuilder->get_widget("remainingtime_label", pRemainingTime);
		pRemainingTime->set_text(pBattery->getRemainingTime());

		time_t currentTime;
		time(&currentTime);
		Gtk::Label *pCurrentTime = 0;
		refBuilder->get_widget("refreshtime_label", pCurrentTime);
		pCurrentTime->set_text(ctime(&currentTime));

	}

	delete pBattery;
}
