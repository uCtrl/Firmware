# uCtrl 
#FRDM-KL25Z specific files
CPU = -mcpu=cortex-m3 -mthumb
ARM_ARCH = TARGET_M3
###############################################################################
#Paths resolution
###############################################################################
LPC1768_PATH = TARGET_NXP/TARGET_LPC176X/
LPC176X_HAL_PATH = $(MBED_PATH)targets/hal/$(LPC1768_PATH)
LPC1768_HAL_PATH = $(LPC176X_HAL_PATH)TARGET_MBED_LPC1768/
CMSIS_PATH = $(MBED_PATH)targets/cmsis
LPC1768_CMSIS_PATH = $(MBED_PATH)targets/cmsis/$(LPC1768_PATH)
###############################################################################
#MBED
###############################################################################
#hal
INCLUDE_PATHS += -I$(LPC176X_HAL_PATH) -I$(LPC1768_HAL_PATH)

OBJECTS += $(LPC176X_HAL_PATH)gpio_irq_api.o
OBJECTS += $(LPC176X_HAL_PATH)ethernet_api.o
OBJECTS += $(LPC176X_HAL_PATH)spi_api.o
OBJECTS += $(LPC176X_HAL_PATH)can_api.o

OBJECTS += $(LPC176X_HAL_PATH)analogin_api.o
OBJECTS += $(LPC176X_HAL_PATH)analogout_api.o
OBJECTS += $(LPC176X_HAL_PATH)gpio_api.o
OBJECTS += $(LPC176X_HAL_PATH)i2c_api.o
OBJECTS += $(LPC176X_HAL_PATH)pinmap.o
OBJECTS += $(LPC176X_HAL_PATH)port_api.o
OBJECTS += $(LPC176X_HAL_PATH)pwmout_api.o
OBJECTS += $(LPC176X_HAL_PATH)rtc_api.o
OBJECTS += $(LPC176X_HAL_PATH)serial_api.o
OBJECTS += $(LPC176X_HAL_PATH)sleep.o
OBJECTS += $(LPC176X_HAL_PATH)us_ticker.o

#cmsis
OBJECTS += $(LPC1768_CMSIS_PATH)cmsis_nvic.o $(LPC1768_CMSIS_PATH)system_LPC17xx.o 

#cmsis toolchain specific files
SYS_OBJECTS += $(LPC1768_CMSIS_PATH)$(ARM_TOOLCHAIN)/startup_LPC17xx.o

INCLUDE_PATHS += -I$(LPC1768_CMSIS_PATH) -I$(LPC1768_CMSIS_PATH)$(ARM_TOOLCHAIN)

LINKER_SCRIPT += $(LPC1768_CMSIS_PATH)$(ARM_TOOLCHAIN)/LPC1768.ld

###############################################################################
#MBED-RTOS
###############################################################################
OBJECTS += $(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)/SVC_Table.o $(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)/HAL_CM3.o

INCLUDE_PATHS += -I$(MBED_RTOS_PATH)rtx/$(ARM_ARCH) -I$(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)

###############################################################################
#lwip
###############################################################################
#Nothing yet

###############################################################################
#Flags
###############################################################################
CC_FLAGS = $(CPU) -c $(CC_OPTIMISATION) -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections
CC_FLAGS += -MMD -MP
CC_SYMBOLS = -DTARGET_LPC1768 -DTARGET_M3 -DTARGET_NXP -DTARGET_LPC176X -DTARGET_MBED_LPC1768 -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -DMBED_BUILD_TIMESTAMP=1393616359.58 -D__MBED__=1 

LD_FLAGS = -mcpu=cortex-m0plus -mthumb -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
