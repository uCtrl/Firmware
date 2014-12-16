/*
* UMsgHandler.h
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#ifndef UMSGHANDLER_H_
#define UMSGHANDLER_H_

#include "mbed.h"
#include "rtos.h"
#include "cfg.h"
#include "UMsgHandlerMailType.h"
#include "frozen.h"
#include "UScenario.h"
#include "UTaskHandler.h"
#include "UDeviceType.h"
#include "UJsonUtils.h"
#include "MbedJSONValue.h"

#include "UPlatform.h"
#include "UDevice.h"
#include "UScenario.h"
#include "UTask.h"
#include "UCondition.h"
#include "MbedJSONValue.h"

extern Mail<UMsgHandlerMailType, MSGHANDLER_MAIL_SIZE> msgHandlerMail;
extern Mail<UMsgHandlerMailType, COMDRIVER_OUT_MAIL_SIZE> comDriverOutMail;

/**
 * ENUM Message Type
 */
enum
{
	//REQUESTS GET MESSAGES
	REQ_GETPLATFORM = 1,
	REQ_GETDEVICES = 3,
	REQ_GETSCENARIOS = 5,
	REQ_GETTASKS = 7,
	REQ_GETCONDITIONS = 9,
	//REQUESTS SAVE MESSAGES
	REQ_SAVEPLATFORM = 11,
	REQ_SAVEDEVICES  = 13,
	REQ_SAVESCENARIOS  = 15,
	REQ_SAVETASKS = 17,
	REQ_SAVECONDITIONS = 19,
	//RESPONSE GET MESSAGES
	RES_GETPLATFORM = 2,
	RES_GETDEVICES = 4,
	RES_GETSCENARIOS = 6,
	RES_GETTASKS = 8,
	RES_GETCONDITIONS = 10,
	//RESPONSE SAVE MESSAGES
	RES_SAVEPLATFORM = 12,
	RES_SAVEDEVICES  = 14,
	RES_SAVESCENARIOS  = 16,
	RES_SAVETASKS = 18,
	RES_SAVECONDITIONS = 20,
	
	EVT_UPDATESENSOR = 21,
	
	REQ_DELETEDEVICE = 33,
	REQ_DELETESCENARIO = 35,
	REQ_DELETETASK = 37,
	REQ_DELETECONDITION = 39,
};

class UMsgHandler
{
    private:
		void parseTokens(UMsgHandlerMailType *aMail, json_token* tokens, int size, const struct json_token *tok, int messageType);
		MbedJSONValue parser;

    public:
        UMsgHandler();
        void start();
        void parseMessage(UMsgHandlerMailType *aMail);
        void create(const char* aInput);
        ~UMsgHandler();

		static void SendMessage(char* message, Endpoint* endpoint);
		static void SendBroadcast(char* message);
		void ParseInnerJson(uint16_t messageType, int size, int parent, Endpoint* endpoint, json_token* tokens);
		
		void handleGet(UMsgHandlerMailType *aMail, int messageType);
		void handleSave(UMsgHandlerMailType *aMail, int messageType);
		void handleEvent(UMsgHandlerMailType *aMail, int messageType);
		void handleDelete(UMsgHandlerMailType *aMail, int messageType);
};

#endif  //UMSGHANDLER_H_

