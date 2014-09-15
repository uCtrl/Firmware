# uCtrl 
#FKPSDK
KPSDK_PATH ?= ./

#mbed hal
INCLUDE_PATHS += -I$(KPSDK_PATH)utilities
INCLUDE_PATHS += -I$(KPSDK_PATH)utilities/src
INCLUDE_PATHS += -I$(KPSDK_PATH)hal
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/edma
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/wdog
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/uart
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/can
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/osc
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/dmamux
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/enet
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/i2c
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/adc
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/sai
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/sim
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/gpio
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/flextimer
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/dspi
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/rtc
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/pit
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/mcg
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/port
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/pmc
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/smc
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/sdhc
INCLUDE_PATHS += -I$(KPSDK_PATH)hal/sdhc/src
INCLUDE_PATHS += -I$(KPSDK_PATH)common
INCLUDE_PATHS += -I$(KPSDK_PATH)common/phyksz8081
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/enet
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/enet/src
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/interrupt
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/interrupt/src
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/clock
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/clock/src
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/pit
INCLUDE_PATHS += -I$(KPSDK_PATH)drivers/pit/src

OBJECTS += $(KPSDK_PATH)utilities/src/sw_timer.o
OBJECTS += $(KPSDK_PATH)utilities/src/fsl_os_abstraction_mbed.o
OBJECTS += $(KPSDK_PATH)hal/edma/fsl_edma_hal.o
OBJECTS += $(KPSDK_PATH)hal/wdog/fsl_wdog_hal.o
OBJECTS += $(KPSDK_PATH)hal/uart/fsl_uart_hal_common_configurations.o
OBJECTS += $(KPSDK_PATH)hal/uart/fsl_uart_hal_transfer_functions.o
OBJECTS += $(KPSDK_PATH)hal/uart/fsl_uart_hal_special_feature_configurations.o
OBJECTS += $(KPSDK_PATH)hal/uart/fsl_uart_hal_fifo_configurations.o
OBJECTS += $(KPSDK_PATH)hal/uart/fsl_uart_hal_status_flags.o
OBJECTS += $(KPSDK_PATH)hal/uart/fsl_uart_hal_interrupts_and_dma.o
OBJECTS += $(KPSDK_PATH)hal/can/fsl_flexcan_hal.o
OBJECTS += $(KPSDK_PATH)hal/osc/fsl_osc_hal.o
OBJECTS += $(KPSDK_PATH)hal/dmamux/fsl_dmamux_hal.o
OBJECTS += $(KPSDK_PATH)hal/enet/fsl_enet_hal.o
OBJECTS += $(KPSDK_PATH)hal/i2c/fsl_i2c_hal.o
OBJECTS += $(KPSDK_PATH)hal/adc/fsl_adc_hal.o
OBJECTS += $(KPSDK_PATH)hal/sai/fsl_sai_hal.o
OBJECTS += $(KPSDK_PATH)hal/sim/fsl_sim_hal.o
OBJECTS += $(KPSDK_PATH)hal/sim/fsl_sim_clock_module_names_K64F12.o
OBJECTS += $(KPSDK_PATH)hal/gpio/fsl_gpio_hal.o
OBJECTS += $(KPSDK_PATH)hal/flextimer/fsl_ftm_hal.o
OBJECTS += $(KPSDK_PATH)hal/dspi/fsl_dspi_hal.o
OBJECTS += $(KPSDK_PATH)hal/rtc/fsl_rtc_hal.o
OBJECTS += $(KPSDK_PATH)hal/pit/fsl_pit_hal.o
OBJECTS += $(KPSDK_PATH)hal/mcg/fsl_mcg_hal.o
OBJECTS += $(KPSDK_PATH)hal/port/fsl_port_hal.o
OBJECTS += $(KPSDK_PATH)hal/smc/fsl_smc_hal.o
OBJECTS += $(KPSDK_PATH)hal/sdhc/src/fsl_sdhc_hal.o
OBJECTS += $(KPSDK_PATH)common/phyksz8081/fsl_phy_driver.o
OBJECTS += $(KPSDK_PATH)drivers/enet/src/fsl_enet_irq.o
OBJECTS += $(KPSDK_PATH)drivers/interrupt/src/fsl_interrupt_manager.o
OBJECTS += $(KPSDK_PATH)drivers/clock/src/fsl_clock_manager.o
OBJECTS += $(KPSDK_PATH)drivers/pit/src/fsl_pit_irq.o
OBJECTS += $(KPSDK_PATH)drivers/pit/src/fsl_pit_driver.o

#mbed cmsis
