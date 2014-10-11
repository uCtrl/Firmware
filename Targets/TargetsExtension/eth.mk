# uCtrl 
#eth
ETH_PATH ?= $(NET_PATH)eth/

INCLUDE_PATHS += -I$(NET_PATH)
INCLUDE_PATHS += -I$(ETH_PATH)lwip-eth/
INCLUDE_PATHS += -I$(ETH_PATH)lwip-eth/arch/
INCLUDE_PATHS += -I$(ETH_PATH)lwip-eth/arch/TARGET_Freescale/
INCLUDE_PATHS += -I$(ETH_PATH)lwip-eth/arch/TARGET_NXP/
INCLUDE_PATHS += -I$(ETH_PATH)EthernetInterface/

OBJECTS += $(ETH_PATH)EthernetInterface/EthernetInterface.o