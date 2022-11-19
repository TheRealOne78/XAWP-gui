LDFLAGS = -lconfig
CC = gcc
CFLAGS = -O2
SRC = ./src/*.c
BIN = xawp-gui
BUILD_DIR = ./build/
INSTALL_DIR = /usr/bin/

$(BIN):
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(BUILD_DIR)$(BIN)

# TODO: refactor this mess
install:
	install -t $(INSTALL_DIR) --owner=$(shell stat -c "%U" $(INSTALL_DIR)) --group=$(shell stat -c "%G" $(INSTALL_DIR)) -m 775 $(BUILD_DIR)$(BIN) # install $(COMPILE_DIR)$(BIN) in $(INSTALL_DIR)

all: $(BIN) install

uninstall:
	rm -f $(INSTALL_DIR)$(BIN)

clean:
	rm -rf $(BUILD_DIR)

TESTDIR = test/
test: $(BIN)
	$(BUILD_DIR)$(BIN)

.PHONY: all install uninstall clean
