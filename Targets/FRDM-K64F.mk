# uCtrl 
#FRDM-K64F specific files
CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
ARM_ARCH = TARGET_M4
###############################################################################
#Paths resolution
###############################################################################
FRDM_K64F_PATH = TARGET_Freescale/TARGET_MCU_K64F/
FRDM_K64F_MCU_HAL_PATH = $(MBED_PATH)targets/hal/TARGET_Freescale/TARGET_KPSDK_MCUS/TARGET_MCU_K64F/
FRDM_K64F_HAL_PATH = $(FRDM_K64F_MCU_HAL_PATH)TARGET_FRDM/
FRDM_K64F_CMSIS_PATH = $(MBED_PATH)targets/cmsis/$(FRDM_K64F_PATH)
KPSDK_PATH = $(MBED_PATH)targets/hal/TARGET_Freescale/TARGET_KPSDK_MCUS/TARGET_KPSDK_CODE/
###############################################################################
#MBED
###############################################################################
#KPSDK
include ./Targets/TargetsExtension/KPSDK.mk

#hal
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH) -I$(FRDM_K64F_HAL_PATH)
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)device/ -I$(FRDM_K64F_MCU_HAL_PATH)device/MK64F12/

OBJECTS += $(FRDM_K64F_HAL_PATH)mbed_overrides.o
OBJECTS += $(FRDM_K64F_HAL_PATH)PeripheralPins.o 

OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)analogin_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)analogout_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)gpio_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)gpio_irq_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)i2c_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)pinmap.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)port_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)pwmout_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)rtc_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)serial_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)sleep.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)spi_api.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)us_ticker.o

#cmsis
OBJECTS += $(FRDM_K64F_CMSIS_PATH)cmsis_nvic.o $(FRDM_K64F_CMSIS_PATH)system_MK64F12.o 

#cmsis toolchain specific files
OBJECTS += $(FRDM_K64F_CMSIS_PATH)$(ARM_TOOLCHAIN)/startup_MK64F12.o

INCLUDE_PATHS += -I$(FRDM_K64F_CMSIS_PATH) -I$(FRDM_K64F_CMSIS_PATH)$(ARM_TOOLCHAIN)

LINKER_SCRIPT += $(FRDM_K64F_CMSIS_PATH)$(ARM_TOOLCHAIN)/K64FN1M0xxx12.ld

###############################################################################
#MBED-RTOS
###############################################################################
OBJECTS += $(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)/SVC_Table.o $(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)/HAL_CM4.o

INCLUDE_PATHS += -I$(MBED_RTOS_PATH)rtx/$(ARM_ARCH) -I$(MBED_RTOS_PATH)rtx/$(ARM_ARCH)/$(TOOLCHAIN)

###############################################################################
#net
###############################################################################
INCLUDE_PATHS += -I$(ETH_PATH)lwip-eth/arch/TARGET_Freescale/

OBJECTS += $(ETH_PATH)lwip-eth/arch/TARGET_Freescale/fsl_enet_driver.o
OBJECTS += $(ETH_PATH)lwip-eth/arch/TARGET_Freescale/k64f_emac.o
OBJECTS += $(ETH_PATH)lwip-eth/arch/TARGET_Freescale/hardware_init_MK64F12.o
###############################################################################
#Flags
###############################################################################
CC_FLAGS = $(CPU) -c $(CC_OPTIMISATION) -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections
CC_SYMBOLS = -DTARGET_K64F -DTARGET_M4 -DTARGET_Freescale -DTARGET_KPSDK_MCUS -DTARGET_KPSDK_CODE -DTARGET_FRDM -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DMBED_BUILD_TIMESTAMP=1409670100.47 -D__MBED__=1 -DCPU_MK64FN1M0VMD12 -DFSL_RTOS_MBED -DTARGET_FF_ARDUINO 

LD_FLAGS = -mcpu=cortex-m4 -mthumb -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
