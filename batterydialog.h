//  batterydialog.h
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

#ifndef _BATTERYDIALOG_H
#define _BATTERYDIALOG_H

#include <gtkmm.h>
class BatteryDialog : public Gtk::Window
{
	public:
		BatteryDialog(Gtk::Main kit);
		virtual ~BatteryDialog();
  

	protected:

	private:
		Gtk::Dialog* pDialog;
		Glib::RefPtr<Gtk::Builder> refBuilder;

		void UpdateBatteryInfo();
		void RefreshButton_clicked();
		void QuitButton_clicked();
};

#endif // _BATTERYDIALOG_H
