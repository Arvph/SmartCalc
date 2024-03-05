.PHONY: all clean install uninstall

TARGET = SmartCalc

all: clean install

clean: 
	@rm -rf ./build/*.app
	@rm -rf ./src/qt/*.app

install: 
	@clear
	@echo ">>>  Installation has started  <<<"
	@cd src/qt/ && qmake && make && make clean && rm -rf Makefile && mv $(TARGET).app ../../build
	@rm -rf ./src/qt/*.app
# @cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo ">>>  SmartCalc application installed  <<<"


uninstall:
	@rm -rf ./build/$(TARGET).app
# @rm -rf ~/Desktop/$(TARGET).app
	@echo ">>>  SmartCalc removed  <<<"



format: 
	@clang-format -i src/modules/*.c src/modules/*.h
	@clang-format -i src/qt/*.cpp src/qt/*.h
