/*
 * UPlcDriver.h
 *
 *  Created on: Oct 1, 2014
 *      Author: uctrl
 */

#ifndef UPLC_HANDLER_H_
#define UPLC_HANDLER_H_
#include "Message.h"
#include "HostMessage.h"
#include "G3_MessageFactory.h"
#include "G3DecentralizedNode.h"

#include "UPlcConfigFile.h"
#include "UPlcDriverIn.h"
#include "UPlcDriverOut.h"

#include "mbed.h"
#include "rtos.h"

#include "EthernetInterface.h"

//aka network management
class UPlcHandler
{
// Friend class must be in same thread (no thread safe between them)
// This friend allow more granular access to private member function of
// UPlcHandler. It allow G3DecentralizedNode to be more indepedent
// from UPlcHandler
friend class G3DecentralizedNode;
private:
	void init();

	//for firend class G3DecentralizedNode
	void sendMessage(HostMessage &hostMessage);
	//void waitForResponse(HostMessage &hostMessage);

	G3_MessageFactory hostMessageFactory;
	G3DecentralizedNode g3Node;
	Semaphore semHostMsgFactorySendMsg;
	uint32_t msgTimeDelay;
public:

	UPlcHandler();
	~UPlcHandler(){};
	void setPLCNetworkConfig(const Endpoint &plcNetworkConfig);
	int sendMessage(const Endpoint &destination, const char * message, const uint16_t length);
	char * receiveMessage(Endpoint &source, uint16_t &length);
	void start();
	/** sendMessage
	 *
	 */
	//void sendMessage(char * message, uint16_t length)
	/** sendMessage is thread safe using Semaphore semHostMsgFactorySendMsg
	 *
	 */
	//void sendMessage(char * message,int length, char * ipAddress);

	/** Initialize the interface with dynamically assigned ipv6 address.
	* return 0 on success, a negative number on failure
	*/
	//static int init();

	/** Initialize the interface with given static ipv6 address.
	* return 0 on success, a negative number on failure
	*/
	//static int init(const char* ip, const char* mask, const char* gateway);
	/*static int connect();
	static int disconnect();
	static char* getMACAddress();
	static char* getIPAddress();
	static char* getGateway();
	static char* getNetworkMask();
	*/
};

#endif /* UPLC_HANDLER_H_ */
