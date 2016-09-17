#-------------------------------------------------------------------- settings
FIND := find -E
DIR := $(PWD)/examples
CRITERIA := -regex ".*(pde|ino)"
EACH_EXAMPLE := $(FIND) $(DIR) $(CRITERIA) -exec
BUILD := platformio ci
LIB := .

#--------------------------------------------------------------------- targets
# update .travis.yml if target boards added
all: uno due huzzah genuino101 teensy31

uno due huzzah genuino101 teensy31:
	PLATFORMIO_BOARD=$@ $(MAKE) build

build:
	$(EACH_EXAMPLE) $(BUILD) --board=$(PLATFORMIO_BOARD) --lib=$(LIB) {} \;

.PHONY: all uno due huzzah genuino101 teensy31 build
