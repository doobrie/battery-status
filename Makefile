#  Makefile
#
#  Copyright 2012 doobrie (daveyem@live.com)
#
#  This file is part of battery-status.
#
#  battery-status is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  battery-status is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with battery-status.  If not, see <http://www.gnu.org/licenses/>.

NAME=battery-status
CFLAGS=-g -Wall -o $(NAME)
GTKFLAGS=`pkg-config --cflags --libs gtkmm-3.0`
SRCS=battery.cc main.cc batterydialog.cc
CC=g++
 
# Do all
all: main
 
# Compile
main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS)
 
# Clean
clean:
	rm -f $(NAME)
	rm -f *.h~
	rm -f *.cc~
	rm -f Makefile~
	rm -f *.glade~
