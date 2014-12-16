/*
 * UPlcDriver.cpp
 *
 *  Created on: Oct 1, 2014
 *      Author: uctrl
 */

#include "UPlcHandler.h"

extern Serial usbSerial;

UPlcHandler::UPlcHandler():
hostMessageFactory(),
g3Node(this),
semHostMsgFactorySendMsg(1),
msgTimeDelay(osWaitForever)
{
}

void UPlcHandler::init()
{
	//This should be done to initialize PLC modules
	//g3Node.Init();
}

void UPlcHandler::start()
{
	init();

	Message *message = NULL;
	HostMessage *hostMessage = NULL;

	while(true)
	{
		usbSerial.printf("about to wait event in PLC handler");
		osEvent evt = queueUPlcDriverIn.get(msgTimeDelay);
		if (evt.status == osEventMessage)
		{
			message = (Message*)evt.value.p;
			
			usbSerial.printf("PLC handler, length%:%u\r\n",message->_MessageSize);
			
			semHostMsgFactorySendMsg.wait();
			hostMessage = hostMessageFactory.GetHostMessage(message->_Message, 0);
			semHostMsgFactorySendMsg.release();
			
			// Do not use message variable anymore, it has been mem copied in
			// host message, use host message instead.
			delete message;
			message = NULL;
			semQueueUPlcDriverIn.release();
			
			if(hostMessage != NULL)
			{
				g3Node.HandleMessage(hostMessage);
				
				// Node has finished working with host message
				delete hostMessage;
				hostMessage = NULL;
				
				//We are finished interpreting the message
			}
			else
			{
				usbSerial.printf("hostMessage is NULL\r\n");
			}
		}
		else if (evt.status == osEventTimeout)
		{
			usbSerial.printf("timeout in handler");
			//g3Node.handleMessageTimeout();

			//might not be important since we handle
			//msgTimeDelay = osWaitForever;
			//g3Node.handleMsgTimeout();
			//safe procedure
			//msgTimeDelay = osWaitForever;
		}
		else
		{
			usbSerial.printf("unhandled os message\r\n");
			semQueueUPlcDriverIn.release();
		}
	}
}

void UPlcHandler::setPLCNetworkConfig(const Endpoint &plcNetworkConfig)
{
    // This should be used be G3Decentralized node to initialize the PLC with
    // this hacked adresse
    
    /*
    BYTE ipv4Address[4];
    //link local ipv6 address |                 pan id in address |           | fffe link local
    BYTE ipv6Address[16] = {0xFE, 0x80, 00, 00, 00, 00, 00, 00, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF};
    //															         eth ipv4 address | 
    
    int intValue = 0;
    char subAddress[4] = {'\0'};
    for(int i = 0; i < 4; i++)
    {
    	memcpy(&subAddress,(&endpoint.get_address())+4*i,3);
    	ipv4Address[i] = (BYTE)atoi(&subAddress);
    	
    	
    }
    
    UINT16 panId = SwapOrder_UInt16(g3Node->_PAN_Id);
	memcpy(&ipv6Address[8], &panId, 2);
    
    
    
    ipv6Address = "fe80"endpoint.get_address();
    BYTE sourceIPv6Address[16] = {0xFE, 0x80, 00, 00, 00, 00, 00, 00, 0xFF, 0xFF, 0x00, 0xFF, 0xFE, 00, 00, 00};
    
	UINT16 panId = SwapOrder_UInt16(sn->_PAN_Id);
	memcpy(&sourceIPv6Address[8], &panId, 2);
    
    this->get_address();
    ipv4Address
    char* get_address(void);
    int get_port(void);*/
}

int UPlcHandler::sendMessage(const Endpoint &destination, const char * message, const uint16_t length)
{
	/*
	semHostMsgFactorySendMsg.wait();
	
	_LastBytesSent = 0;

	// Echo back the data.
	Data_Transfer_Request dtr;
	
	dtr.Set_Destination_Add(dti->Get_Source_Add());
	dtr.Set_DestinationPort(dti->Get_SourcePort());
	dtr.Set_Source_Add(dti->Get_Destination_Add());
	dtr.Set_SourcePort(dti->Get_DestinationPort());
	
	dtr.Set_HopLimit(dti->Get_HopLimit());
	
	dtr.Set_NSDU(0x0);

	//dtr.Set_QOS_Flag(1);
	dtr.Set_SEC_Flag(1);
	dtr.Set_DiscoveryRoute_Flag(1);

	Message * payload = dti->Get_Data();

	dtr.Set_Data(payload->_MessageSize, payload->_Message);
	delete payload;
	//Thread::wait(1000);

	SendMessage(dtr);
	_LastBytesSent = dtr.Get_UDP_Length() - 8;
	
	//TODO JF create message with hostfactory
	//Message *message = hostMessage.MakeMessage();
	//queueUPlcDriverOut.put(message);
	//sendMessage
	semHostMsgFactorySendMsg.release();*/
	
	return 0;
}

char * UPlcHandler::receiveMessage(Endpoint &source, uint16_t &length)
{
	semHostMsgFactorySendMsg.wait();
	//TODO create message with hostfactory
	//Message *message = hostMessage.MakeMessage();
	semHostMsgFactorySendMsg.release();
	//TODO return udp information (adresses and  port info) into Endpoint
	//TODO return the length od udp data (UDP length - 8 (see UDP on wiki)) into uint16_t
	//TODO return udp data data into char*
	
	//TODO return the true char *
	return NULL;
}

void UPlcHandler::sendMessage(HostMessage &hostMessage)
{
	usbSerial.printf("PLC handler, about to response\r\n");
	semQueueUPlcDriverOut.wait(osWaitForever);
	
	Message *message = hostMessage.MakeMessage();
	queueUPlcDriverOut.put(message);
}

