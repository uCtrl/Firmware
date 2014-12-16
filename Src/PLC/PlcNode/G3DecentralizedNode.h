/*
 * G3DecentralizedNode.h
 *
 *  Created on: Oct 17, 2014
 *      Author: uctrl
 */
#ifndef G3_DECENTRALIZED_NODE_H_
#define G3_DECENTRALIZED_NODE_H_

#include "UPlcConfigFile.h"
#include "NodeState.h"
#include "ServiceNode.h"
#include "HostMessage.h"
#include "mbed.h"
//#include <list>

class UPlcHandler;
class G3DecentralizedNode;

typedef void (G3DecentralizedNode::*G3DecentralizedNodeFctPtr)(HostMessage*, ResponseStatus status);

class G3DecentralizedNode
{
	struct HostMessageCallBack
	{
		HostMessage *hostMessagePtr;
		G3DecentralizedNodeFctPtr g3DecentralizedNodeFctPtr;
		uint32_t callBackTimeout;
	};

private:
	BYTE _ExtendedAddress[8];
	BYTE _IPv6_Address[16];
	UINT16 _ShortAddress;
	UINT16 _PAN_Id;
	UINT16 _LBA_Address;

	int _LastBytesSent;

	bool _AutoMode;

	ServiceNode _ServiceNode;
	//linked list templated
	//CallBackList _MessageCallBackList;
	//std::list<HostMessageCallBack> _HostMessageCallBackList;

	Timer timeoutTimer;
	UPlcHandler *_PlcHandler;

	InitializationState _InitState;

	int DiscoverNetwork();
	int Attach();
	int Detach();

	void Reattach();
	//void DetachTest();

	static void ProcessSocketCommands(void * classObject, void * pointer);
	void SendMessage(HostMessage &hostMessage);
	void WaitForMessage(HostMessage *hostMessage, uint32_t responseTimeout, G3DecentralizedNodeFctPtr);
	void ParseExtendedAddress(const TextString & ts, BYTE * extendedAddress);

public:
	G3DecentralizedNode(UPlcHandler *uplcHandler);
	virtual ~G3DecentralizedNode();

	virtual void Init(HostMessage *hostMessage = NULL, ResponseStatus status = TIMEOUT);
	virtual void Network();
	virtual void HandleMessage(HostMessage *hostMessage);
	/* return 0 if hostMessage is handled */
	virtual int CheckCallBackList(HostMessage *hostMessage);

};

#endif /* G3_DECENTRALIZED_NODE_H_ */
