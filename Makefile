#-------------------------------------------------------------------- settings
FIND := find
DIR := $(PWD)/examples
CRITERIA := -name "*.pde" -o -name "*.ino"
EACH_EXAMPLE := $(FIND) $(DIR) $(CRITERIA) -exec
BUILD := platformio ci
LIB := .

#--------------------------------------------------------------------- targets
build:
	$(EACH_EXAMPLE) $(BUILD) --board=$(PLATFORMIO_BOARD) --lib=$(LIB) {} \;

.PHONY: build
