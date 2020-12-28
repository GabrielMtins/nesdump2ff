
# Copyright (C) 2020  Gabriel Martins

# This file is part of nesdump2ff.

# nesdump2ff is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# nesdump2ff is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
    
# You should have received a copy of the GNU General Public License
# along with nesdump2ff.  If not, see <https://www.gnu.org/licenses/>
# Contact: gabrielmartinsthe@gmail.com

CC = gcc
EXEC ?= nesdump2ff
MAN_FILE := nesdump2ff.1

CCFLAGS := -Wall -Wextra -O2

LIBFLAGS := -lgffimage -lm

SRC_DIR := source

BUILD_DIR := ./build

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(SRC))
OBJECTS := $(addsuffix .o, $(OBJECTS))

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@ $(CCFLAGS)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CCFLAGS) $(LIBFLAGS) -o $(EXEC)

install:
	cp $(EXEC) /usr/bin/$(EXEC)
	cp $(MAN_FILE) /usr/share/man/man1/

clean:
	rm -r build
	rm $(EXEC)
