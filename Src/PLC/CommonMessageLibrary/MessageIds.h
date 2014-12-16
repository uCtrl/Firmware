#pragma once
/*
enum MessageIds
{
	Data_Transfer_Id = 0x00,
	Get_System_Info_Id = 0x01,
	Get_PHY_PIB_Id = 0x02,
	Get_MAC_PIB_Id = 0x03,
	Set_Info_Id = 0x04,
	Shut_Down_Id = 0x05,
	Setup_Alarm_Id = 0x06,
	Alarm_Id = 0x07,
	Network_Register_Id = 0x08,
	Network_Start_Id = 0x08,
	Network_Unregister_Id = 0x09,
	Connect_Id = 0x0A,
	Disconnect_Id = 0x0B, 
	Load_System_Config_Id = 0x0C,
	Set_MAC_PIB_Id = 0x0D,
	Clear_PHY_PIB_Id = 0x0E,
	Clear_MAC_PIB_Id = 0x0F,
	Attach_Id = 0x10,
	Detach_Id = 0x11,
	Discover_Id = 0x12,
	Firmware_UpGrade_Id = 0x13
};
*/
enum Unique_Ids
{
	Data_Transfer_UID = 100,
	Data_Transfer_UID_Request,
	Data_Transfer_UID_Confirm,
	Data_Transfer_UID_Indication,
	Get_System_Info_UID = 200,
	Get_PHY_PIB_UID = 300,
	Get_MAC_PIB_UID = 400,
	Set_Info_UID = 500,
	Shut_Down_UID = 600,
	Setup_Alarm_UID = 700,
	Alarm_UID = 800,
	Network_Register_UID = 900,
	Network_Start_UID = 1000,
	Network_Unregister_UID = 1100,
	Connect_UID = 1200,
	Disconnect_UID = 1300, 
	Load_System_Config_UID = 1400,
	Set_MAC_PIB_UID = 1500,
	Set_MAC_PSK_PIB_UID = 1501,
	Clear_PHY_PIB_UID = 1600,
	Clear_MAC_PIB_UID = 1700,

	Attach_UID = 1800,
	Attach_UID_Request = 1801,
	Attach_UID_Confirm = 1802,
	Attach_UID_Indication = 1803,

	Detach_UID = 1900,
	Detach_UID_Request = 1901,
	Detach_UID_Confirm = 1902,
	Detach_UID_Indication = 1903,

	Discover_UID = 2000,
	Route_Discover_UID = 2010,
	Route_Discover_Status_UID = 2011,
	Path_Discover_UID = 2012,
	Path_Discover_Confirm_UID = 2013,

	Firmware_UpGrade_UID = 2100
};

enum Ports
{
	SCI_A = 0,
	SCI_B = 1
};

enum NodeType
{
	Service_Node = 0,
	PAN_Coordinator = 1
};

enum DiscoverType
{
	NetworkDiscover = 0x00,
	RouteDiscover = 0x01,
	PathDiscover = 0x02
};

enum ResetType
{
	SoftReset = 0x0000,
	SoftShutdown = 0x0001
};

enum G3_TX_Modulation
{
	ROBO = 0,
	BPSK = 1,
	QPSK = 2,
	Eight_PSK = 3
};
