# uCtrl 
#FRDM-KL25Z specific files
CPU = -mcpu=cortex-m0plus -mthumb
ARM_ARCH = TARGET_M0P
###############################################################################
#Paths resolution
###############################################################################
FRDM_KL25Z_PATH = TARGET_Freescale/TARGET_KLXX/TARGET_KL25Z/
FRDM_KLXX_HAL_PATH = $(MBED_PATH)targets/hal/TARGET_Freescale/TARGET_KLXX/
FRDM_KL25Z_HAL_PATH = $(MBED_PATH)targets/hal/$(FRDM_KL25Z_PATH)
CMSIS_PATH = $(MBED_PATH)targets/cmsis
FRDM_KL25Z_CMSIS_PATH = $(MBED_PATH)targets/cmsis/$(FRDM_KL25Z_PATH)
FRDM_KL25Z_MBED_RTOS_RX_PATH = $(MBED_RTOS_PATH)rtx/$(FRDM_KL25Z_ARM_ARCH)/$(ARM_TOOLCHAIN)/
###############################################################################
#MBED
###############################################################################
#hal
INCLUDE_PATHS += -I$(FRDM_KLXX_HAL_PATH) -I$(FRDM_KL25Z_HAL_PATH)

OBJECTS += $(FRDM_KL25Z_HAL_PATH)gpio_irq_api.o $(FRDM_KL25Z_HAL_PATH)mbed_overrides.o
OBJECTS += $(FRDM_KL25Z_HAL_PATH)PeripheralPins.o $(FRDM_KL25Z_HAL_PATH)spi_api.o

OBJECTS += $(FRDM_KLXX_HAL_PATH)analogin_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)analogout_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)gpio_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)i2c_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)pinmap.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)port_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)pwmout_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)rtc_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)serial_api.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)sleep.o
OBJECTS += $(FRDM_KLXX_HAL_PATH)us_ticker.o

#cmsis
OBJECTS += $(FRDM_KL25Z_CMSIS_PATH)cmsis_nvic.o $(FRDM_KL25Z_CMSIS_PATH)system_MKL25Z4.o 

#cmsis toolchain specific files
SYS_OBJECTS += $(FRDM_KL25Z_CMSIS_PATH)$(ARM_TOOLCHAIN)/startup_MKL25Z4.o

INCLUDE_PATHS += -I$(FRDM_KL25Z_CMSIS_PATH) -I$(FRDM_KL25Z_CMSIS_PATH)$(ARM_TOOLCHAIN)

LINKER_SCRIPT += $(FRDM_KL25Z_CMSIS_PATH)$(ARM_TOOLCHAIN)/MKL25Z4.ld

###############################################################################
#MBED-RTOS
###############################################################################
OBJECTS += $(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)/SVC_Table.o $(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)/HAL_CM0.o

INCLUDE_PATHS += -I$(MBED_RTOS_PATH)rtx/$(ARM_ARCH) -I$(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)

###############################################################################
#lwip
###############################################################################
#Nothing yet

###############################################################################
#Flags
###############################################################################
CC_FLAGS = $(CPU) -c $(CC_OPTIMISATION) -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections
CC_SYMBOLS += -DTARGET_KL25Z -DTARGET_M0P -DTARGET_Freescale -DTARGET_KLXX -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M0PLUS -DARM_MATH_CM0PLUS -DMBED_BUILD_TIMESTAMP=1393616359.58 -D__MBED__=1 

LD_FLAGS = -mcpu=cortex-m0plus -mthumb -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
