# uCtrl 
# PLC
# dependancies mbed, mbed rtos
PLC_PATH ?= ./Src/PLC/

INCLUDE_PATHS += -I$(PLC_PATH)
INCLUDE_PATHS += -I$(PLC_PATH)PlcNode/
INCLUDE_PATHS += -I$(PLC_PATH)G3_NetworkManagementLayer/
INCLUDE_PATHS += -I$(PLC_PATH)PlcSerialDriver/
INCLUDE_PATHS += -I$(PLC_PATH)G3_Host_Message_Library/
INCLUDE_PATHS += -I$(PLC_PATH)SharedHostMessageLibrary/
INCLUDE_PATHS += -I$(PLC_PATH)UtilityLibrary/
INCLUDE_PATHS += -I$(PLC_PATH)CommonMessageLibrary/

OBJECTS += $(PLC_PATH)UPlcHandler.o
OBJECTS += $(PLC_PATH)UPlcConfigFile.o
OBJECTS += $(PLC_PATH)PlcNode/G3DecentralizedNode.o
OBJECTS += $(PLC_PATH)G3_NetworkManagementLayer/ServiceNode.o
OBJECTS += $(PLC_PATH)PlcSerialDriver/UPlcDriverIn.o
OBJECTS += $(PLC_PATH)PlcSerialDriver/UPlcDriverOut.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/PathRequest.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Data_Transfer_Confirm.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Discover.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Alarm.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/RouteRequest.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Network_Start.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Get_System_Info.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Data_Transfer_Request.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/G3_MessageFactory.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Data_Transfer_Indication.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Attach.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Load_System_Config.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Set_Info.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/PathConfirm.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Set_PSK_PIB.o
OBJECTS += $(PLC_PATH)G3_Host_Message_Library/Detach.o
OBJECTS += $(PLC_PATH)SharedHostMessageLibrary/SwapOrder.o
OBJECTS += $(PLC_PATH)SharedHostMessageLibrary/StatusMessage.o
OBJECTS += $(PLC_PATH)SharedHostMessageLibrary/LoadSystemConfiguration.o
OBJECTS += $(PLC_PATH)SharedHostMessageLibrary/DataTransfer.o
OBJECTS += $(PLC_PATH)SharedHostMessageLibrary/SharedUtilities.o
OBJECTS += $(PLC_PATH)UtilityLibrary/WordArray.o
OBJECTS += $(PLC_PATH)UtilityLibrary/CriticalSection.o
OBJECTS += $(PLC_PATH)UtilityLibrary/CRC16.o
OBJECTS += $(PLC_PATH)UtilityLibrary/ByteArray.o
OBJECTS += $(PLC_PATH)UtilityLibrary/Log.o
OBJECTS += $(PLC_PATH)UtilityLibrary/Message.o
OBJECTS += $(PLC_PATH)UtilityLibrary/LinkedList.o
OBJECTS += $(PLC_PATH)UtilityLibrary/TextString.o
OBJECTS += $(PLC_PATH)CommonMessageLibrary/Shut_Down_Message.o
OBJECTS += $(PLC_PATH)CommonMessageLibrary/HostMessage.o
OBJECTS += $(PLC_PATH)CommonMessageLibrary/HostMessageFactory.o
OBJECTS += $(PLC_PATH)CommonMessageLibrary/MessageHeader.o
OBJECTS += $(PLC_PATH)CommonMessageLibrary/TLV.o
OBJECTS += $(PLC_PATH)CommonMessageLibrary/Status_Message.o