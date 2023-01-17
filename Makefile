LDFLAGS = -lconfig $(shell pkg-config --libs gtk+-3.0 glib-2.0)
CC = gcc
CFLAGS = -O2 $(shell pkg-config --cflags gtk+-3.0 glib-2.0)
SRC = ./src/*.c

BIN = xawp-gui
BUILD_DIR = ./build/
BIN_INSTALL_DIR = /usr/bin/

UI = ./ui/*.ui
ICO = ./images/*.png
USR_SHARE_DIR = /usr/share/
RES_INSTALL_DIR = $(USR_SHARE_DIR)xawp/
UI_INSTALL_DIR = $(RES_INSTALL_DIR)ui/
ICO_INSTALL_DIR = $(RES_INSTALL_DIR)icons/

$(BIN):
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(BUILD_DIR)$(BIN)

install_res_dir:
	# Install resources directory
	install -d --owner=$(shell stat -c "%U" $(USR_SHARE_DIR)) --group=$(shell stat -c "%G" $(USR_SHARE_DIR)) -m 755 $(RES_INSTALL_DIR)

# TODO: refactor this mess
install: install_res_dir
	#install the other resources directories
	install -d --owner=$(shell stat -c "%U" $(RES_INSTALL_DIR)) --group=$(shell stat -c "%G" $(RES_INSTALL_DIR)) -m 755 $(UI_INSTALL_DIR)
	install -d --owner=$(shell stat -c "%U" $(RES_INSTALL_DIR)) --group=$(shell stat -c "%G" $(RES_INSTALL_DIR)) -m 755 $(ICO_INSTALL_DIR)
	install -t $(UI_INSTALL_DIR) --owner=$(shell stat -c "%U" $(RES_INSTALL_DIR)) --group=$(shell stat -c "%G" $(RES_INSTALL_DIR)) -m 775 $(UI)
	install -t $(ICO_INSTALL_DIR) --owner=$(shell stat -c "%U" $(RES_INSTALL_DIR)) --group=$(shell stat -c "%G" $(RES_INSTALL_DIR)) -m 775 $(ICO)
	# Install the binary file
	install -t $(BIN_INSTALL_DIR) --owner=$(shell stat -c "%U" $(BIN_INSTALL_DIR)) --group=$(shell stat -c "%G" $(BIN_INSTALL_DIR)) -m 775 $(BUILD_DIR)$(BIN)

all: $(BIN) install clean

uninstall:
	rm -f $(BIN_INSTALL_DIR)$(BIN)

clean:
	rm -rf $(BUILD_DIR)

TESTDIR = test/
test: $(BIN)
	$(BUILD_DIR)$(BIN)

.PHONY: all install uninstall clean
