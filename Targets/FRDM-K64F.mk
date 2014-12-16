# uCtrl 
#FRDM-K64F specific files
CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
ARM_ARCH = TARGET_M4
#/mbed/targets/hal/TARGET_Freescale/TARGET_KPSDK_MCUS/TARGET_MCU_K64F/TARGET_FRDM
###############################################################################
#Paths resolution
###############################################################################
FRDM_K64F_PATH = TARGET_Freescale/TARGET_MCU_K64F/
FRDM_K64F_MCU_HAL_PATH = $(MBED_PATH)targets/hal/TARGET_Freescale/TARGET_KPSDK_MCUS/TARGET_MCU_K64F/
FRDM_K64F_HAL_PATH = $(FRDM_K64F_MCU_HAL_PATH)TARGET_FRDM/
FRDM_K64F_CMSIS_PATH = $(MBED_PATH)targets/cmsis/$(FRDM_K64F_PATH)
KPSDK_PATH = $(MBED_PATH)targets/hal/TARGET_Freescale/TARGET_KPSDK_MCUS/
###############################################################################
#MBED
###############################################################################
#KPSDK
include ./Targets/TargetsExtension/KPSDK.mk

INCLUDE_PATHS += -I$(MBED_PATH)targets/hal/TARGET_Freescale/
#hal
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)
INCLUDE_PATHS += -I$(FRDM_K64F_HAL_PATH)
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)device/
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)device/device/
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)device/device/MK64F12/
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)device/MK64F12/
INCLUDE_PATHS += -I$(FRDM_K64F_MCU_HAL_PATH)MK64F12/

OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)MK64F12/fsl_sim_hal_K64F12.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)MK64F12/fsl_clock_K64F12.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)TARGET_FRDM/mbed_overrides.o
OBJECTS += $(FRDM_K64F_MCU_HAL_PATH)TARGET_FRDM/PeripheralPins.o

#cmsis
INCLUDE_PATHS += -I$(MBED_PATH)targets/cmsis/TARGET_Freescale/
INCLUDE_PATHS += -I$(FRDM_K64F_CMSIS_PATH)
OBJECTS += $(FRDM_K64F_CMSIS_PATH)system_MK64F12.o
OBJECTS += $(FRDM_K64F_CMSIS_PATH)cmsis_nvic.o

#cmsis toolchain specific files
INCLUDE_PATHS += -I$(FRDM_K64F_CMSIS_PATH)$(ARM_TOOLCHAIN)/
OBJECTS += $(FRDM_K64F_CMSIS_PATH)$(ARM_TOOLCHAIN)/startup_MK64F12.o

LINKER_SCRIPT += $(FRDM_K64F_CMSIS_PATH)$(ARM_TOOLCHAIN)/K64FN1M0xxx12.ld

###############################################################################
#MBED-RTOS
###############################################################################
INCLUDE_PATHS += -I$(MBED_RTOS_PATH)rtx/TARGET_CORTEX_M/$(ARM_ARCH)/
INCLUDE_PATHS += -I$(MBED_RTOS_PATH)rtx/TARGET_CORTEX_M/$(ARM_ARCH)/$(TOOLCHAIN)/

OBJECTS += $(MBED_RTOS_PATH)rtx/TARGET_CORTEX_M/$(ARM_ARCH)/$(TOOLCHAIN)/SVC_Table.o
OBJECTS += $(MBED_RTOS_PATH)rtx/TARGET_CORTEX_M/$(ARM_ARCH)/$(TOOLCHAIN)/HAL_CM4.o



###############################################################################
#net
###############################################################################
INCLUDE_PATHS += -I$(ETH_PATH)lwip-eth/arch/TARGET_Freescale/

OBJECTS += $(ETH_PATH)lwip-eth/arch/TARGET_Freescale/fsl_enet_driver.o
OBJECTS += $(ETH_PATH)lwip-eth/arch/TARGET_Freescale/hardware_init_MK64F12.o
OBJECTS += $(ETH_PATH)lwip-eth/arch/TARGET_Freescale/k64f_emac.o

#common net files
include ./Targets/TargetsExtension/eth.mk
include ./Targets/TargetsExtension/lwip.mk
###############################################################################
#Flags
###############################################################################
CC_FLAGS = $(CPU) -c $(CC_OPTIMISATION) -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer
CC_FLAGS += -MMD -MP
CC_SYMBOLS = -DTARGET_K64F -DTARGET_M4 -DTARGET_CORTEX_M -DTARGET_Freescale -DTARGET_KPSDK_MCUS -DTARGET_KPSDK_CODE -DTARGET_MCU_K64F -DTARGET_FRDM -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DMBED_BUILD_TIMESTAMP=1418693951.51 -D__MBED__=1 -DCPU_MK64FN1M0VMD12 -DFSL_RTOS_MBED -DTARGET_FF_ARDUINO 

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float
LD_FLAGS += -Wl,-Map=$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
