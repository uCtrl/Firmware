# uCtrl 
#if this line generate an error, it is probably because the target is not supported
#Supported board: FRDM-K64F LPC1768 FRDM-KL25Z
include ./Targets/$(TARGET).mk

#common files
MBED_COMMON_PATH = $(MBED_PATH)common/
CMSIS_PATH = $(MBED_PATH)targets/cmsis
SYS_OBJECTS += $(MBED_COMMON_PATH)retarget.o

#common MBED files
OBJECTS += $(MBED_COMMON_PATH)assert.o
OBJECTS += $(MBED_COMMON_PATH)board.o
OBJECTS += $(MBED_COMMON_PATH)BusIn.o
OBJECTS += $(MBED_COMMON_PATH)BusInOut.o
OBJECTS += $(MBED_COMMON_PATH)BusOut.o
OBJECTS += $(MBED_COMMON_PATH)CallChain.o
OBJECTS += $(MBED_COMMON_PATH)CAN.o
OBJECTS += $(MBED_COMMON_PATH)error.o
OBJECTS += $(MBED_COMMON_PATH)Ethernet.o
OBJECTS += $(MBED_COMMON_PATH)exit.o
OBJECTS += $(MBED_COMMON_PATH)FileBase.o
OBJECTS += $(MBED_COMMON_PATH)FileLike.o
OBJECTS += $(MBED_COMMON_PATH)FilePath.o
OBJECTS += $(MBED_COMMON_PATH)FileSystemLike.o
OBJECTS += $(MBED_COMMON_PATH)FunctionPointer.o
OBJECTS += $(MBED_COMMON_PATH)gpio.o
OBJECTS += $(MBED_COMMON_PATH)I2C.o
OBJECTS += $(MBED_COMMON_PATH)I2CSlave.o
OBJECTS += $(MBED_COMMON_PATH)InterruptIn.o
OBJECTS += $(MBED_COMMON_PATH)InterruptManager.o
OBJECTS += $(MBED_COMMON_PATH)LocalFileSystem.o
OBJECTS += $(MBED_COMMON_PATH)mbed_interface.o
OBJECTS += $(MBED_COMMON_PATH)pinmap_common.o
OBJECTS += $(MBED_COMMON_PATH)RawSerial.o
OBJECTS += $(MBED_COMMON_PATH)retarget.o
OBJECTS += $(MBED_COMMON_PATH)rtc_time.o
OBJECTS += $(MBED_COMMON_PATH)semihost_api.o
OBJECTS += $(MBED_COMMON_PATH)SerialBase.o
OBJECTS += $(MBED_COMMON_PATH)Serial.o
OBJECTS += $(MBED_COMMON_PATH)SPI.o
OBJECTS += $(MBED_COMMON_PATH)SPISlave.o
OBJECTS += $(MBED_COMMON_PATH)Stream.o
OBJECTS += $(MBED_COMMON_PATH)Ticker.o
OBJECTS += $(MBED_COMMON_PATH)Timeout.o
OBJECTS += $(MBED_COMMON_PATH)Timer.o
OBJECTS += $(MBED_COMMON_PATH)TimerEvent.o
OBJECTS += $(MBED_COMMON_PATH)us_ticker_api.o
OBJECTS += $(MBED_COMMON_PATH)wait_api.o

INCLUDE_PATHS += -I. -I$(MBED_COMMON_PATH) -I$(CMSIS_PATH) -I$(MBED_PATH)api -I$(MBED_PATH)hal


#common MBED-RTOS files
OBJECTS += $(MBED_RTOS_PATH)rtx/rt_Task.o $(MBED_RTOS_PATH)rtx/rt_System.o $(MBED_RTOS_PATH)rtx/rt_List.o $(MBED_RTOS_PATH)rtx/rt_Time.o $(MBED_RTOS_PATH)rtx/rt_Semaphore.o $(MBED_RTOS_PATH)rtx/rt_Mailbox.o $(MBED_RTOS_PATH)rtx/rt_CMSIS.o $(MBED_RTOS_PATH)rtx/HAL_CM.o $(MBED_RTOS_PATH)rtx/rt_Robin.o $(MBED_RTOS_PATH)rtx/rt_MemBox.o $(MBED_RTOS_PATH)rtx/RTX_Conf_CM.o $(MBED_RTOS_PATH)rtx/rt_Event.o $(MBED_RTOS_PATH)rtx/rt_Mutex.o $(MBED_RTOS_PATH)rtos/Thread.o $(MBED_RTOS_PATH)rtos/RtosTimer.o $(MBED_RTOS_PATH)rtos/Semaphore.o $(MBED_RTOS_PATH)rtos/Mutex.o
INCLUDE_PATHS += -I./mbed-rtos -I$(MBED_RTOS_PATH)rtx -I$(MBED_RTOS_PATH)rtos
