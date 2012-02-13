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
		pRefreshButton->signal_clicked().connect(sigc::mem_fun(this, &BatteryDialog::RefreshButton_clicked));
	
		Gtk::Button *pQuitButton = 0;
		refBuilder->get_widget("quit_button", pQuitButton);
		pQuitButton->signal_clicked().connect(sigc::mem_fun(this, &BatteryDialog::QuitButton_clicked));

		UpdateBatteryInfo();
	
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

void BatteryDialog::RefreshButton_clicked()
{
	UpdateBatteryInfo();
}

void BatteryDialog::QuitButton_clicked()
{
	pDialog->hide();	
}

void BatteryDialog::UpdateBatteryInfo()
{
	Battery* pBattery = new Battery();
	if (pBattery->ReadInfo()==true)
	{
		Gtk::Label *pModelNumberLabel = 0;
		refBuilder->get_widget("modelnumber_label", pModelNumberLabel);
		pModelNumberLabel->set_text(pBattery->GetModelNumber());

		Gtk::Label *pSerialNumberLabel = 0;
		refBuilder->get_widget("serialnumber_label", pSerialNumberLabel);
		pSerialNumberLabel->set_text(pBattery->GetSerialNumber());

		Gtk::Label *pChargingStateLabel = 0;
		refBuilder->get_widget("chargingstate_label", pChargingStateLabel);
		pChargingStateLabel->set_text(pBattery->GetChargingState());

		Gtk::Label *pRemainingCapacityLabel = 0;
		refBuilder->get_widget("remainingcapacity_label", pRemainingCapacityLabel);
		pRemainingCapacityLabel->set_text(pBattery->GetRemainingCapacity());

		Gtk::Label *pFullCapacityLabel = 0;
		refBuilder->get_widget("fullcapacity_label", pFullCapacityLabel);
		pFullCapacityLabel->set_text(pBattery->GetFullCapacity());
	}

	delete pBattery;
}
