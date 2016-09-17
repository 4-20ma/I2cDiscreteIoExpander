# Program settings
PIO := platformio ci
LIB := .

# Examples - add an array item for each example
SRC[1] := examples/BareMinimum/BareMinimum.ino
SRC[2] := examples/MultipleDevices/MultipleDevices.ino

build:
	# add a line item for each element in SRC array
	$(PIO) --board=${PLATFORMIO_BOARD} --lib=$(LIB) $(SRC[1])
	$(PIO) --board=${PLATFORMIO_BOARD} --lib=$(LIB) $(SRC[2])
