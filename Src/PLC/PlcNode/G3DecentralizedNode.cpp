/*
 * G3DecentralizedNode.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: uctrl
 */

#include "G3DecentralizedNode.h"

//#include "G3_ServiceNodeManagement.h"
//#include "Network_Start.h"
#include "Data_Transfer_Request.h"
#include "Data_Transfer_Indication.h"
#include "Data_Transfer_Confirm.h"
#include "Status_Message.h"
#include "Get_System_Info.h"
#include "Load_System_Config.h"
#include "Shut_Down_Message.h"
#include "Set_Info.h"
/*
#include "Set_PSK_PIB.h"

#include "Status_Message.h"
#include "Attach.h"
#include "MessageIds.h"
#include "Get_System_Info.h"
#include "Load_System_Config.h"
#include "Discover.h"
#include "Detach.h"
#include "Shut_Down_Message.h"
#include "Set_Info.h"
#include "ByteArray.h"
#include "WordArray.h"
#include "Log.h"
*/
#include "UPlcHandler.h"

extern Serial usbSerial;
//extern ByteArray * ToneMasks[];

G3DecentralizedNode::G3DecentralizedNode(UPlcHandler *uplcHandler):
_ShortAddress(0),
_PAN_Id(0),
_LBA_Address(0),
_LastBytesSent(0),
_AutoMode(true),
_ServiceNode(),
//_HostMessageCallBackList(),
timeoutTimer(),
_InitState(UNINITIALIZED)
{
	memset(_ExtendedAddress, 0, sizeof(_ExtendedAddress));
	memset(_IPv6_Address, 0, sizeof(_IPv6_Address));

	//srand(RANDOM_SEED);

	_PlcHandler = uplcHandler;
}

void G3DecentralizedNode::SendMessage(HostMessage &hostMessage)
{
	_PlcHandler->sendMessage(hostMessage);
}

void G3DecentralizedNode::WaitForMessage(HostMessage *hostMessage, uint32_t responseTimeout, G3DecentralizedNodeFctPtr fctPtr)
{
	/*
	HostMessageCallBack callback;
	callback.hostMessagePtr = hostMessage;
	callback.callBackTimeout = responseTimeout;
	callback.g3DecentralizedNodeFctPtr = fctPtr;
	if(_HostMessageCallBackList.empty())
	{
		//start timer to handle callback/message timeout
		timeoutTimer.start();
		//set message queue timeout to this timeout
		_PlcHandler->msgTimeDelay = responseTimeout;
	}
	_HostMessageCallBackList.push_back(callback);*/
}

G3DecentralizedNode::~G3DecentralizedNode()
{
}


void G3DecentralizedNode::HandleMessage(HostMessage *hostMessage)
{
	//CheckCallBackList(hostMessage);
	usbSerial.printf("Inside node with host message id: %d\r\n",hostMessage->GetUniqueId());
	
	if(hostMessage->GetUniqueId() == Data_Transfer_UID_Confirm)
	{
		usbSerial.printf("Confirmation message");
		return;
	}
	
	if (hostMessage->GetUniqueId() == Data_Transfer_UID_Indication)
	{
		//send it to the interface
		usbSerial.printf("Received some data");
		
		
		//this is a test for replying the message
		
		_LastBytesSent = 0;
		Data_Transfer_Indication *dti = (Data_Transfer_Indication *)hostMessage;

		_ServiceNode._BytesReceived += dti->Get_UDP_Length()-8;
		_ServiceNode._PacketsReceived++;
		//
		// Echo back the data.
		//
		Data_Transfer_Request dtr;
		
		dtr.Set_Destination_Add(dti->Get_Source_Add());
		dtr.Set_DestinationPort(dti->Get_SourcePort());
		dtr.Set_Source_Add(dti->Get_Destination_Add());
		dtr.Set_SourcePort(dti->Get_DestinationPort());
		
		//dtr.Set_SEC_Flag(dti->Get_SEC_Flag());
		dtr.Set_HopLimit(dti->Get_HopLimit());
		
		dtr.Set_NSDU(0x0);
	
		//dtr.Set_QOS_Flag(1);
		dtr.Set_SEC_Flag(1);
		dtr.Set_DiscoveryRoute_Flag(1);

		Message * payload = dti->Get_Data();

		dtr.Set_Data(payload->_MessageSize, payload->_Message);
		delete payload;

		SendMessage(dtr);
		_LastBytesSent = dtr.Get_UDP_Length() - 8;
	}
	else
	{
		usbSerial.printf("Inside node with host message id: not recognized: %d\r\n",hostMessage->GetUniqueId());
	}
	usbSerial.printf("quit g3 plc node.\r\n",hostMessage->GetUniqueId());

	//handle unsollicited message such as data request

	/*
	HostMessage * hm = (HostMessage *)pointer;
	if (hm->GetUniqueId() == Detach_UID_Confirm)
	{
		_ServiceNode._TotalSuccessfullDisconnects++;
		_ServiceNode._Connected = false;

		Detach_Confirm * dc = (Detach_Confirm *)pointer;
		BYTE * extendedAddress = dc->Get_ExtendedAddress();
		ByteArray ba (8, extendedAddress);
		Log::Write("Received Detach Confirm..: %s\r\n\r\n", (char *)ba.ToString());
		//
		// Ok, so we've been detached. Lets re-attach to the network..
		//
		if (_AutoMode == true)
		{
			CreateThread(NULL, 0, Reattach, this, 0,NULL);
		}
	}
	else if (hm->GetUniqueId() == Detach_UID_Indication)
	{
		_ServiceNode._TotalDisconnects++;
		_ServiceNode._TotalSuccessfullDisconnects++;
		_ServiceNode._Connected = false;

		Detach_Indication * di = (Detach_Indication *)pointer;
		BYTE * extendedAddress = di->Get_ExtendedAddress();
		ByteArray ba (8, extendedAddress);
		Log::Write("Received Detach Indication..: %s\r\n\r\n", (char *)ba.ToString());
		//
		// Ok, so we've been detached. Lets re-attach to the network..
		//
		if (_AutoMode == true)
		{
			CreateThread(NULL, 0, Reattach, this, 0,NULL);
		}
	}
	else if (hm->GetUniqueId() == Attach_UID_Confirm)
	{
		_ServiceNode._Connected = true;
		_ServiceNode._TotalSuccessfullConnects++;

		if (CommandLineArguments::CmdArg()->Exists("testdetach"))
		{
			// run the detach test....
			CreateThread(NULL, 0, DetachTest, this, 0,NULL);
		}
	}
	else if (hm->GetUniqueId() == Attach_UID_Indication)
	{
		Attach_Indication * ai = (Attach_Indication *)pointer;
		BYTE * extendedAddress = ai->Get_ExtendedAddress();
		ByteArray ba (8, extendedAddress);
		Log::Write("Received unexpected attach indication..: %s\r\n", (char *)ba.ToString());
	}
	else if (hm->GetUniqueId() == Data_Transfer_UID_Confirm)
	{
		Data_Transfer_Confirm * dtc = (Data_Transfer_Confirm*)hm;

		if(dtc->Get_Status() == 0)
		{
			_ServiceNode._PacketsSent++;
			_ServiceNode._BytesSent += _LastBytesSent;
			_LastBytesSent = 0;
		}
	}
	else if (hm->GetUniqueId() == Data_Transfer_UID_Indication && _TunTap == NULL)
	{
		_LastBytesSent = 0;
		Data_Transfer_Indication * dti = (Data_Transfer_Indication *) hm;

		_ServiceNode._BytesReceived += dti->Get_UDP_Length()-8;
		_ServiceNode._PacketsReceived++;
		//
		// Echo back the data.
		//
		Data_Transfer_Request dtr;

		dtr.Set_Destination_Add(dti->Get_Source_Add());
		dtr.Set_DestinationPort(dti->Get_SourcePort());
		dtr.Set_Source_Add(dti->Get_Destination_Add());
		dtr.Set_SourcePort(dti->Get_DestinationPort());
		dtr.Set_DiscoveryRoute_Flag(1);
		dtr.Set_SEC_Flag(dti->Get_SEC_Flag());
		dtr.Set_HopLimit(8);

		Message * payload = dti->Get_Data();
		dtr.Set_Data(payload->_MessageSize, payload->_Message);
		delete payload;

		SendMessage(dtr);
		_LastBytesSent = dtr.Get_UDP_Length() - 8;
	}
	*/
}

int G3DecentralizedNode::CheckCallBackList(HostMessage *hostMessage)
{
	
	int rtnCallBackHandled = 0;
/*
	if(!_HostMessageCallBackList.empty())
	{
		timeoutTimer.stop();
		uint32_t timeDelay = timeoutTimer.read_ms();

		std::list<HostMessageCallBack>::iterator callBackIterator = _HostMessageCallBackList.begin();
		while(callBackIterator != _HostMessageCallBackList.end())
		{
			// we have received the corresponding response message for the callback
			if(callBackIterator->hostMessagePtr->GetUniqueId() == hostMessage->GetUniqueId())
			{
				// 0 mean there is no error
				hostMessage->CopyTo(callBackIterator->hostMessagePtr);
				(this->*(callBackIterator->g3DecentralizedNodeFctPtr))(callBackIterator->hostMessagePtr,0);
				callBackIterator = _HostMessageCallBackList.erase(callBackIterator);
				rtnCallBackHandled = true;
			}
			// sort of status message
			else if(hostMessage->GetUniqueId() == 0)
			{
				if (hostMessage->GetId() == callBackIterator->hostMessagePtr->GetId() &&
					hostMessage->GetORG() == callBackIterator->hostMessagePtr->GetORG())
				{
					hostMessage->CopyTo(callBackIterator->hostMessagePtr);
					(this->*(callBackIterator->g3DecentralizedNodeFctPtr))(callBackIterator->hostMessagePtr,0);
					callBackIterator = _HostMessageCallBackList.erase(callBackIterator);
					rtnCallBackHandled = true;
				}
			}
			// the callback as timed out
			else if(callBackIterator->callBackTimeout <= timeDelay)
			{
				// call the function pointer with the waited hostMessageResponse
				// -1 mean message error
				(this->*(callBackIterator->g3DecentralizedNodeFctPtr))(hostMessage,-1);
				callBackIterator = _HostMessageCallBackList.erase(callBackIterator);
			}
			else
			{
				callBackIterator->callBackTimeout -= timeDelay;
				callBackIterator++;
			}
		}
		if(!_HostMessageCallBackList.empty())
		{
			timeoutTimer.start();
		}
	}*/
	return rtnCallBackHandled;
}

void G3DecentralizedNode::Reattach()
{
	/*
	//TODO JF thread for handling reconnection
	G3DecentralizedNode * snm = (G3DecentralizedNode *) para;
	int status = 0;
	while (status == 0)
	{
		status = snm->DiscoverNetwork();
		if (status != 0)
		{
			status = snm->Attach();
		}
	}
	return 0;
	*/
}

int G3DecentralizedNode::DiscoverNetwork()
{
	/*
	int status = 0;
	//
	// set the psk key before the network discover
	//
	Set_PSK_PIB pib;

	//TODO JF, checker si le panid est ok
	pib.SetPIB_Id(0x1f);
	pib.SetPIB_Index(0);
	pib.SetPIB_Key(PSK_TS);

	_plcHandler->sendMessage(pib);

	Set_PIB_Reply spr;
	status = WaitForMessage(spr, 3000);
	if (status != 0)
	{
		Log::Write("Set PSK Reply Timed Out..Status= 0x%4.4X\r\n\r\n", status);
	}
	if (spr.Get_Status() != 0)
	{
		Log::Write("Set PSK Failed..Status= 0x%4.4X\r\n\r\n", spr.Get_Status());
		status = spr.Get_Status();
	}

	while (status == 0)
	{
		int delayTime = (rand() % 30000);

		Log::Write("DiscoverNetwork: Sleep for %d\r\n", delayTime);

		Sleep(delayTime);

		Discover_Network_Request dr;

		int duration = CommandLineArguments::CmdArg()->GetIntValue("discover");
		if (duration == 0)
		{
			dr.SetDuration(5);
		}
		else
		{
			dr.SetDuration((BYTE)duration);
		}
		SendMessage(dr);

		Discover_Network_Confirm dc;
		status = WaitForMessage(dc, 10000);

		if (status == 0 && dc.GetStatus() == 0 && dc.Get_PAN_Count() > 0)
		{
			_PAN_Id = dc.Get_PAN_Version54(0)->_Coord_PAN_Address;
			_LBA_Address = dc.Get_PAN_Version54(0)->_ShortAddress;
			status = 1;
			break;
		}
		status = 0;
	}
	return status;
	*/
	return 0;
}

int G3DecentralizedNode::Attach()
{
	/*
	AddMessageCallBack(this, MessageHandler);

	_ServiceNode._TotalConnects++;

	Attach_Request ar;
	ar.Set_LBA_Address(_LBA_Address);
	ar.Set_PAN_Id(_PAN_Id);

	SendMessage(ar);

	Attach_Confirm ac;
	int status = WaitForMessage(ac, 10000);

	if (status != 0 || ac.Get_Status() != 0)
	{
		//
		// Return zero for failure..
		//
		status = 0;
	}
	else
	{
		_ServiceNode._ShortAddress = ac.Get_NetworkAddress();
		if (CommandLineArguments::CmdArg()->Exists("tuntap"))
		{
			SetTunTapAddress(_ServiceNode._ShortAddress);
		}

		status = 1;
	}
	return status;
	*/
	return 0;
}

void G3DecentralizedNode::Network()
{
	/*
	int status = 0;
	while(status == 0)
	{
		status = DiscoverNetwork();
		//
		// Status == 1 means we found a network..
		//
		if (status != 0)
		{
			status = Attach();
		}

		if (status != 0)
		{
			//
			// Do something here...
			//
			Sleep(10000);
		}

		int delayTime = rand() % 30000;
		Sleep(delayTime);
	}
	*/
}

void G3DecentralizedNode::Init(HostMessage *hostMessage, ResponseStatus status)
{
	usbSerial.printf("Trying to initialize:");
	//delete hostMessage;

	
	static Get_System_Info *gsi = NULL;

	//if hostMessahe == null, check if state is at uninitialized
	if(status != RECEIVED)
	{
		delete hostMessage;
		usbSerial.printf("Something went wrong duriong initialization");
		_InitState = UNINITIALIZED;
	}

	//It is important to change the state before sending the message
	switch(_InitState)
	{
		case UNINITIALIZED:
		{
			usbSerial.printf("UNINITIALIZED\r\n");
			Get_System_Info_Request gsir;

			_InitState = LOAD_SYSTEM_CONFIG_DATA_PORT;
			WaitForMessage(new Get_System_Info(), 3000, &G3DecentralizedNode::Init);
			SendMessage(gsir);
			break;
		}

		case LOAD_SYSTEM_CONFIG_DATA_PORT:
		{
			usbSerial.printf("LOAD_SYSTEM_CONFIG_DATA_PORT");
			//handle GSI return
			//clear old gsi
			//if(gsi != NULL)
			//{
			//	delete gsi;
			//}
			gsi = (Get_System_Info*)hostMessage;

			// set port
			Load_System_Config port;
			port.Set_DataPort(SCI_A);
			port.Set_DiagPort(SCI_A);

			_InitState = LOAD_SYSTEM_CONFIG_DEVICE_MODE;
			WaitForMessage(new Status_Message(Load_System_Config_Id), 3000, &G3DecentralizedNode::Init);
			SendMessage(port);
			break;
		}

		case LOAD_SYSTEM_CONFIG_DEVICE_MODE:
		{
			usbSerial.printf("LOAD_SYSTEM_CONFIG_DEVICE_MODE");
			
			Load_System_Config deviceMode;
			deviceMode.Set_DeviceMode(0);
			_InitState = LOAD_SYSTEM_CONFIG_G3_CONFIG;
			//reuse Status_Message(Load_System_Config_Id)
			WaitForMessage(hostMessage, 3000, &G3DecentralizedNode::Init);
			SendMessage(deviceMode);
			break;
		}

		case LOAD_SYSTEM_CONFIG_G3_CONFIG:
		{
			usbSerial.printf("LOAD_SYSTEM_CONFIG_G3_CONFIG");
			
			Load_System_Config g3Config;
			BYTE * longAddress = gsi->Get_LongAddress();

			if (EXTENDED_ADDRESS.GetLength() > 0)
			{
				ParseExtendedAddress(EXTENDED_ADDRESS, longAddress);
			}
			//
			// save the service node address
			//
			memcpy(_ServiceNode._ExtendedAddress, longAddress, 8);

			g3Config.Set_LongAddress(longAddress);

			_InitState = SHUT_DOWN_MESSAGE;
			//hostmessage is status message, reuse it
			WaitForMessage(hostMessage, 3000, &G3DecentralizedNode::Init);
			SendMessage(g3Config);
			break;
		}

		case SHUT_DOWN_MESSAGE:
		{
			usbSerial.printf("SHUT_DOWN_MESSAGE");
			
			//should do status validation before deleting
			delete hostMessage;

			Shut_Down_Message sdm;
			sdm.SetResetType(SoftReset);
			_InitState = SLEEP_SHUTDOWN;
			//hostmessage is status message, reuse it
			WaitForMessage(new Status_Message(Shut_Down_Id), 3000, &G3DecentralizedNode::Init);
			SendMessage(sdm);
			break;
		}

		case SLEEP_SHUTDOWN:
		{
			usbSerial.printf("SLEEP_SHUTDOWN");
			
			_InitState = GET_SYSTEM_INFO_AFTER_REBOOT;
			//reuse waiting host message to timeout after 10 seconds
			WaitForMessage(hostMessage, 10000, &G3DecentralizedNode::Init);
			break;
		}

		case GET_SYSTEM_INFO_AFTER_REBOOT:
		{
			usbSerial.printf("GET_SYSTEM_INFO_AFTER_REBOOT");
			
			Get_System_Info_Request gsir;
			_InitState = SET_VENDOR_PRODUCT_INFO;
			WaitForMessage(gsi, 3000, &G3DecentralizedNode::Init);
			SendMessage(gsir);
			break;
		}

		case SET_VENDOR_PRODUCT_INFO:
		{
			usbSerial.printf("SET_VENDOR_PRODUCT_INFO");
			
			delete hostMessage;
			gsi = NULL;

			UINT16 vendorId = VENDOR_ID;
			if (vendorId == 0)
			{
				vendorId = 123;
			}
			TextString productId = PRODUCT_ID;
			if (productId.GetLength() == 0)
			{
				productId = "0987654321";
			}

			Set_VendorProduct_Info svpi;
			svpi.Set_VendorId(vendorId);
			svpi.Set_ProductId((char*)productId);

			_InitState = SLEEP_VENDOR_PRODUCT_INFO;
			WaitForMessage(new Status_Message(Set_Info_Id), 3000, &G3DecentralizedNode::Init);
			SendMessage(svpi);
			break;
		}

		case SLEEP_VENDOR_PRODUCT_INFO:
		{
			_InitState = SET_TX_INFO;
			//reuse waiting host message to timeout after 1 seconds
			WaitForMessage(hostMessage, 1000, &G3DecentralizedNode::Init);
			break;
		}

		case SET_TX_INFO:
		{
			Set_TX_Info sti;
			//
			// TMR must be off for FCC bands..
			//
			sti.Set_TMR_Flag(TMR_FLAG);
			sti.Set_COH_Flag(COH_FLAG);
			sti.Set_Modulation(MODULATION);
			UINT16 txLevel = TX_LEVEL;
			if (txLevel > 0 && txLevel <= 32)
			{
				sti.Set_TX_Level(txLevel);
			}
			else
			{
				sti.Set_TX_Level(32);
			}
			sti.Set_Band_Select(BAND_VALUE);
			sti.Set_ToneMask(ToneMasks[TONEMASK_ID]->_Array);
			_InitState = SLEEP_TX_INFO;
			WaitForMessage(hostMessage, 1000, &G3DecentralizedNode::Init);
			SendMessage(sti);
			break;
		}

		case SLEEP_TX_INFO:
		{
			_InitState = SET_RX_INFO;
			//reuse waiting host message to timeout after 1 seconds
			WaitForMessage(hostMessage, 1000, &G3DecentralizedNode::Init);
			break;
		}

		case SET_RX_INFO:
		{
			Set_RX_Info sri;
			sri.Set_COH_Flag(COH_FLAG);
			sri.Set_AGC_Flag(1);
			sri.Set_GainValue(0);
			sri.Set_ROBO_Flag(1);
			sri.Set_ToneMask(ToneMasks[TONEMASK_ID]->_Array);
			sri.Set_Band_Select(BAND_VALUE);


			_InitState = SLEEP_RX_INFO;
			WaitForMessage(hostMessage, 1000, &G3DecentralizedNode::Init);
			SendMessage(sri);
			break;
		}

		case SLEEP_RX_INFO:
		{
			_InitState = INITIALIZATION_FINISH;
			//reuse waiting host message to timeout after 1 seconds
			WaitForMessage(hostMessage, 1000, &G3DecentralizedNode::Init);
			break;
		}

		case INITIALIZATION_FINISH:
		{
			delete hostMessage;
			_InitState = INITIALIZED;
			break;
		}

		case INITIALIZED:
		{
			//reset intitialization
			usbSerial.printf("plc reinitilization requested");
		}
	}
}

void G3DecentralizedNode::ParseExtendedAddress(const TextString & ts, BYTE * extendedAddress)
{
	TextString temp = ts;
	char * endPointer = NULL;
	char * startPointer = (char *)ts;

	for(int index=0; index < 8; index++)
	{
		int value = strtoul(startPointer, &endPointer, 16);
		extendedAddress[index] = (BYTE) value;
		startPointer = endPointer + 1;
	}
}

