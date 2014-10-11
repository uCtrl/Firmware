# uCtrl
# This file was based on makefile generated by mbed for generating export to gcc-arm-mbed
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

SYS_OBJECTS = 
INCLUDE_PATHS = 
LIBRARY_PATHS = 
LIBRARIES = 
LINKER_SCRIPT = 
OBJECTS = 

include ./config.mk

TARGET ?= FRDM-KL25Z
MBED_RTOS_PATH ?= ../mbed/libraries/rtos/
MBED_PATH ?= ../mbed/libraries/mbed/
NET_PATH ?= ../mbed/libraries/net/
PLC_PATH ?= ../uPLC/
ETH_PATH = $(NET_PATH)eth/
LWIP_PATH = $(NET_PATH)lwip/

#to be usedf by targets
ARM_TOOLCHAIN = TOOLCHAIN_GCC_ARM
TOOLCHAIN = TOOLCHAIN_GCC
CPU = 

###############################################################################
#Build type
###############################################################################

#default release
CC_OPTIMISATION = -Os
PROJECT = uCtrl_Firmware_Release
CC_SYMBOLS =

ifeq ($(UCTRL_BUILD_TYPE), Debug)
	CC_OPTIMISATION += -g3
	PROJECT = uCtrl_Firmware_Debug
endif

ifeq ($(UCTRL_BUILD_TYPE), DebugPrint)
	CC_OPTIMISATION += -g3
	PROJECT = uCtrl_Firmware_Debug_Print
	CC_SYMBOLS += -DDEBUG_PRINT
endif

###############################################################################
#TARGET_INCLUDE
###############################################################################
include ./Targets/Target.mk

###############################################################################
#uCtrl sources
###############################################################################
INCLUDE_PATHS += -I./Src
INCLUDE_PATHS += -I./Src/Conditions
INCLUDE_PATHS += -I./Src/Controller
INCLUDE_PATHS += -I./Src/Communication
INCLUDE_PATHS += -I./Src/Devices
INCLUDE_PATHS += -I./Src/Devices/Actuators
INCLUDE_PATHS += -I./Src/Devices/Sensors
INCLUDE_PATHS += -I./Src/Events
INCLUDE_PATHS += -I./Src/Tasks
INCLUDE_PATHS += -I./Src/Utils
OBJECTS += ./Src/mainJF.o
OBJECTS += ./Src/Conditions/UCondition.o
OBJECTS += ./Src/Controller/UController.o
OBJECTS += ./Src/Communication/FakeMessageHandler.o
OBJECTS += ./Src/Communication/UComDriver.o
OBJECTS += ./Src/Communication/UMessageHandler.o
OBJECTS += ./Src/Devices/UDevice.o
OBJECTS += ./Src/Devices/Actuators/FakeActuator.o
OBJECTS += ./Src/Devices/Actuators/UActuatorHandler.o
OBJECTS += ./Src/Devices/Sensors/USensor.o
OBJECTS += ./Src/Devices/Sensors/USensorLight.o
OBJECTS += ./Src/Devices/Sensors/USensorTemperature.o
OBJECTS += ./Src/Devices/Sensors/USensorHandler.o
OBJECTS += ./Src/Tasks/UTaskHandler.o
OBJECTS += ./Src/Tasks/UScenery.o
OBJECTS += ./Src/Tasks/UTask.o
OBJECTS += ./Src/Utils/UPinUtils.o
OBJECTS += ./Src/Utils/UMathUtils.o

###############################################################################
#Makefile target build
###############################################################################
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy

#for clearing .d files
OBJECTS_D = $(OBJECTS:.o=.d)

.PHONY: clean configure

all: $(PROJECT).bin
	 cp $(PROJECT).bin /media/MBED;sync;
	 ../enableSerialPort.sh;
#ifeq ($(UCTRL_BUILD_TYPE), Debug)
#	 ../startDBGServer.sh
#endif

clean:
	
	rm -f $(PROJECT).bin $(PROJECT).elf $(OBJECTS) $(OBJECTS_D)
	
configure:
	./configure

.s.o:
	$(AS) $(CPU) -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@
