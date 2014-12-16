/*
* UMsgHandler.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UMsgHandler.h"
#include <string>

extern Serial usbSerial;

Mail<UMsgHandlerMailType, MSGHANDLER_MAIL_SIZE> msgHandlerMail;
extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER> mailUTaskHandler;

/*
 * Constructor
 * */
UMsgHandler::UMsgHandler()
{
}

/*
 * Starting thread
 * @return void
 * */
void UMsgHandler::start()
{
	while(true)
	{
		osEvent evt = msgHandlerMail.get();
		if (evt.status == osEventMail)
		{
			UMsgHandlerMailType *mail = (UMsgHandlerMailType*)evt.value.p;
			parseMessage(mail);
			msgHandlerMail.free(mail);
		}
	}
}

/*
 * Parse and manage JSON messages from UComDriver
 * Please refer to http://uctrl.github.io/ for JSON format.
 * @param aMail mail handler type.
 * @return void
 * */
void UMsgHandler::parseMessage(UMsgHandlerMailType *aMail)
{
	parse(parser, aMail->msg);
	
	int messageType = parser["messageType"].get<int>();
	
	if(	messageType == REQ_GETPLATFORM || 
		messageType == REQ_GETDEVICES ||
		messageType == REQ_GETSCENARIOS ||
		messageType == REQ_GETTASKS ||
		messageType == REQ_GETCONDITIONS)
	{
		handleGet(aMail, messageType);
	} 
	else if (	messageType == REQ_SAVEPLATFORM || 
				messageType == REQ_SAVEDEVICES ||
				messageType == REQ_SAVESCENARIOS ||
				messageType == REQ_SAVETASKS ||
				messageType == REQ_SAVECONDITIONS)
	{		
		handleSave(aMail, messageType);
	} 
	else if (messageType == EVT_UPDATESENSOR)
	{
		handleEvent(aMail, messageType);
		delete aMail->endPoint;
	}
	else if (	messageType == REQ_DELETEDEVICE ||
				messageType == REQ_DELETESCENARIO ||
				messageType == REQ_DELETETASK ||
				messageType == REQ_DELETECONDITION )
	{
		handleDelete(aMail, messageType);
	}
}

void UMsgHandler::handleGet(UMsgHandlerMailType *aMail, int messageType)
{
	usbSerial.printf("Get recieved.\n\r");
			
	UTaskRequest *mail;
	
	int platformId;
	int deviceId;
	int scenarioId;
	int taskId;
	
	int messageId = parser["messageId"].get<int>();
	
	//System > Platform > Device > Scenario > Task > Condition
	switch(messageType)
	{
		//REQUESTS GET MESSAGES
		case REQ_GETPLATFORM:
#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_GETPLATFORM.\n\r");
#endif
			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();

			mail->taskRequestType = GET_INFO;
			mail->taskCfg.taskCfgType = UPLATFORM;
			mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = 0;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);

			break;
		case REQ_GETDEVICES:
#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_GETDEVICES.\n\r");
#endif

			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();

			platformId = atoi(parser["platformId"].get<string>().c_str());
				
			mail->taskRequestType = GET_INFO;
			mail->taskCfg.taskCfgType = UDEVICE;
			mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = platformId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);

			break;
		case REQ_GETSCENARIOS:
#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_GETSCENARIOS.\n\r");
#endif
			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();

			deviceId = atoi(parser["deviceId"].get<string>().c_str());

			mail->taskRequestType = GET_INFO;
			mail->taskCfg.taskCfgType = USCENARIO;
			mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = deviceId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);

			break;
		case REQ_GETTASKS:
#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_GETTASKS.\n\r");
#endif

			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();

			scenarioId = atoi(parser["scenarioId"].get<string>().c_str());

			mail->taskRequestType = GET_INFO;
			mail->taskCfg.taskCfgType = UTASK;
			mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = scenarioId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);

			break;
		case REQ_GETCONDITIONS:
#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_GETCONDITIONS.\n\r");
#endif

			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();

			taskId = atoi(parser["taskId"].get<string>().c_str());	

			mail->taskRequestType = GET_INFO;
			mail->taskCfg.taskCfgType = UCONDITION;
			mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = taskId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);
		default:
			break;
	}
}

void UMsgHandler::handleSave(UMsgHandlerMailType *aMail, int messageType)
{	
	UTaskRequest *mail;
	
	int size = parser["size"].get<int>();
	int platformId = 0;
	int deviceId = 0;
	int scenarioId = 0;
	int taskId = 0;
	
	int messageId = 0;//parser["messageId"].get<int>();
	
	switch(messageType)
	{
		case REQ_SAVEPLATFORM:	
			break;
			
		case REQ_SAVEDEVICES:	
			platformId = atoi(parser["platformId"].get<string>().c_str());
			break;
			
		case REQ_SAVESCENARIOS:	
			deviceId = atoi(parser["deviceId"].get<string>().c_str());
			break;
			
		case REQ_SAVETASKS:					
			scenarioId = atoi(parser["scenarioId"].get<string>().c_str());
			break;
			
		case REQ_SAVECONDITIONS:						
			taskId = atoi(parser["taskId"].get<string>().c_str());
			break;
			
		default:		
			break;	
	}
	
	for(int i = 0; i < size; i++)
	{	
		UPlatform* platform;
		UDevice* device;
		UScenario* scenario;
		UTask* task;
		UCondition* condition;
	
		UConditionType conditionType;
		UComparisonType comparisonType;
		int beginValue;
		int endValue;		
		
		int id;
		string firmwareVersion;
		string ip;
		int port;
		int status;
		bool enabled;
		string name;
		string room;
		UDeviceType type;
		string actionValue;
		string description;
		string maxValue;
		string minValue;
		string value;
		int precision;
		string unitLabel;
		int lastUpdated;
		
		switch(messageType) 
		{
			case REQ_SAVEPLATFORM:
#ifdef DEBUG_PRINT
				usbSerial.printf("Message is REQ_SAVEPLATFORM.\n\r");
#endif					
				id = 	atoi(		parser["platform"][i]["id"]				.get<string>()	.c_str());	
				name = 				parser["platform"][i]["name"]			.get<string>();	
				status = 			parser["platform"][i]["status"]			.get<int>();				
				room = 				parser["platform"][i]["room"]			.get<string>();						
				enabled = 			parser["platform"][i]["enabled"]		.get<bool>();
				lastUpdated = 		parser["platform"][i]["lastUpdated"]	.get<int>();
				
				firmwareVersion = FIRMWARE_VERSION;	
				ip = string(UJsonUtils::GetIpAddress());
				port = UDPSOCKET_PORT;	
				
				semMailUTaskHandler.wait();
				mail = mailUTaskHandler.alloc();

				mail->taskRequestType = SAVE_INFO;
				mail->taskCfg.taskCfgType = UPLATFORM;
				mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
				mail->taskCfg.parentId = 0;
				mail->taskCfg.endpoint = aMail->endPoint;

				platform = new UPlatform(id, firmwareVersion, name, ip, port, status, room, enabled, lastUpdated);
				mail->taskCfg.platform = platform;
				mailUTaskHandler.put(mail);
				break;
			
			case REQ_SAVEDEVICES:
#ifdef DEBUG_PRINT
				usbSerial.printf("Message is REQ_SAVEDEVICES.\n\r");
#endif
				
				id = 	atoi(	parser["devices"][i]["id"]			.get<string>()	.c_str());	
				name = 			parser["devices"][i]["name"]		.get<string>();
				type = 			static_cast<UDeviceType>(parser["devices"][i]["type"].get<int>());					
				description =   parser["devices"][i]["description"]	.get<string>();
				maxValue = 		parser["devices"][i]["maxValue"]	.get<string>();
				minValue = 		parser["devices"][i]["minValue"]	.get<string>();
				value = 		parser["devices"][i]["value"]		.get<string>();
				precision = 	parser["devices"][i]["precision"]	.get<int>();
				status = 		parser["devices"][i]["status"]		.get<int>();
				unitLabel = 	parser["devices"][i]["unitLabel"]	.get<string>();
				enabled = 		parser["devices"][i]["enabled"]		.get<bool>();
				lastUpdated = 	parser["devices"][i]["lastUpdated"]	.get<int>();
				
				semMailUTaskHandler.wait();
				mail = mailUTaskHandler.alloc();

				mail->taskRequestType = SAVE_INFO;
				mail->taskCfg.taskCfgType = UDEVICE;
				mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
				mail->taskCfg.parentId = platformId;
				mail->taskCfg.endpoint = aMail->endPoint;

				device = new UDevice(id, name, type, description, maxValue, minValue, value, precision, status, unitLabel, enabled, lastUpdated);
				mail->taskCfg.device = device;
				mailUTaskHandler.put(mail);

				break;
			case REQ_SAVESCENARIOS:
#ifdef DEBUG_PRINT
				usbSerial.printf("Message is REQ_SAVESCENARIOS.\n\r");
#endif
				
				id = 	atoi(	parser["scenarios"][i]["id"]			.get<string>()	.c_str());	
				//id = 			parser["scenarios"][i]["id"]			.get<int>();
				name = 			parser["scenarios"][i]["name"]			.get<string>();
				enabled = 		parser["scenarios"][i]["enabled"]		.get<bool>();
				lastUpdated = 	parser["scenarios"][i]["lastUpdated"]	.get<int>();
				
				semMailUTaskHandler.wait();
				mail = mailUTaskHandler.alloc();
				
				mail->taskRequestType = SAVE_INFO;
				mail->taskCfg.taskCfgType = USCENARIO;
				mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
				mail->taskCfg.parentId = deviceId;
				mail->taskCfg.endpoint = aMail->endPoint;

				scenario = new UScenario(id, name, enabled, lastUpdated, deviceId);
				mail->taskCfg.scenario = scenario;
				mailUTaskHandler.put(mail);
				break;

			case REQ_SAVETASKS:
#ifdef DEBUG_PRINT
				usbSerial.printf("Message is REQ_SAVETASKS.\n\r");
#endif
				id = 	atoi(	parser["tasks"][i]["id"]			.get<string>()	.c_str());		
				//id = 			parser["tasks"][i]["id"]			.get<int>();
				actionValue = 	parser["tasks"][i]["value"]	.get<string>();
				enabled = 		parser["tasks"][i]["enabled"]		.get<bool>();
				lastUpdated = 	parser["tasks"][i]["lastUpdated"]	.get<int>();

				semMailUTaskHandler.wait();
				mail = mailUTaskHandler.alloc();
				
				mail->taskRequestType = SAVE_INFO;
				mail->taskCfg.taskCfgType = UTASK;
				mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
				mail->taskCfg.parentId = scenarioId;
				mail->taskCfg.endpoint = aMail->endPoint;

				task = new UTask(id, enabled, lastUpdated, actionValue);
				mail->taskCfg.task = task;
				mailUTaskHandler.put(mail);
				break;

			case REQ_SAVECONDITIONS:
#ifdef DEBUG_PRINT
				usbSerial.printf("Message is REQ_SAVECONDITIONS.\n\r");
#endif

				id = atoi(			parser["conditions"][i]["id"]				.get<string>()	.c_str());					
				conditionType = 	static_cast<UConditionType>(parser["conditions"][i]["type"]				.get<int>());
				comparisonType = 	static_cast<UComparisonType>(parser["conditions"][i]["comparisonType"]	.get<int>());
                beginValue = atoi(  parser["conditions"][i]["beginValue"]   	.get<string>()  .c_str());
                endValue =   atoi(  parser["conditions"][i]["endValue"]     	.get<string>()  .c_str());
                deviceId =   atoi(  parser["conditions"][i]["deviceId"]         .get<string>()  .c_str());
                enabled =           parser["conditions"][i]["enabled"]          .get<bool>();
                lastUpdated =       parser["conditions"][i]["lastUpdated"]      .get<int>();

				semMailUTaskHandler.wait();
				mail = mailUTaskHandler.alloc();
				
				mail->taskRequestType = SAVE_INFO;
				mail->taskCfg.taskCfgType = UCONDITION;
				mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
				mail->taskCfg.parentId = taskId;
				mail->taskCfg.endpoint = aMail->endPoint;

				condition = new UCondition(id, conditionType, comparisonType, beginValue, endValue, deviceId, enabled, lastUpdated);
				
				usbSerial.printf("New condition : %d\r\n", condition->ConditionId);
				
				mail->taskCfg.condition = condition;
				mailUTaskHandler.put(mail);
				break;
			default:
				break;
		}	
	}
	// If everything went well...
	
	int response_status = true; int response_error = 0;		
	char* messageWithShell = UJsonUtils::AddJsonSaveShell((int) messageType, response_status, response_error);
	SendMessage(messageWithShell, aMail->endPoint);
				
	delete [] messageWithShell;
				
}

void UMsgHandler::handleEvent(UMsgHandlerMailType *aMail, int messageType)
{
	UTaskRequest *mail;

#ifdef DEBUG_PRINT
	usbSerial.printf("Message is EVT_UPDATESENSOR.\n\r");
#endif
	int sensorId = parser["sensorId"].get<int>();
	double value = parser["value"].get<double>();
	
	semMailUTaskHandler.wait();
	mail = mailUTaskHandler.alloc();

	mail->taskRequestType = EVENT;
	mail->event.sensorId = sensorId;
	mail->event.value = value;
	mailUTaskHandler.put(mail);	
}

void UMsgHandler::handleDelete(UMsgHandlerMailType *aMail, int messageType)
{
	UTaskRequest *mail;
	int messageId = 0;
		
	switch(messageType)
	{						
		case REQ_DELETEDEVICE:	
		{
//#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_DELETEDEVICE.\n\r");
//#endif
			int deviceId = atoi(parser["deviceId"].get<string>().c_str());
			
			// Delete current scenarios
			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();
			mail->taskRequestType = DELETE;
			mail->taskCfg.taskCfgType = UDEVICE;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = deviceId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);
			break;
		}
			
		case REQ_DELETESCENARIO:	
		{		
//#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_DELETESCENARIO.\n\r");
//#endif		
			int scenarioId = atoi(parser["scenarioId"].get<string>().c_str());

			// Delete current tasks
			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();
			mail->taskRequestType = DELETE;
			mail->taskCfg.taskCfgType = USCENARIO;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = scenarioId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);	
			break;
		}
		case REQ_DELETETASK:	
		{		
//#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_DELETETASK.\n\r");
//#endif		
			int taskId = atoi(parser["taskId"].get<string>().c_str());

			// Delete current tasks
			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();
			mail->taskRequestType = DELETE;
			mail->taskCfg.taskCfgType = UTASK;
			mail->taskCfg.messageId = messageId;
			mail->taskCfg.parentId = taskId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);	
			break;
		}
		case REQ_DELETECONDITION:		
		{		
//#ifdef DEBUG_PRINT
			usbSerial.printf("Message is REQ_DELETECONDITION.\n\r");
//#endif		
			int conditionId = atoi(parser["conditionId"].get<string>().c_str());

			// Delete current conditions
			semMailUTaskHandler.wait();
			mail = mailUTaskHandler.alloc();
			mail->taskRequestType = DELETE;
			mail->taskCfg.taskCfgType = UCONDITION;
			mail->taskCfg.parentId = conditionId;
			mail->taskCfg.endpoint = aMail->endPoint;
			mailUTaskHandler.put(mail);
			break;
		}
		default:		
			break;	
	}
}


void UMsgHandler::SendMessage(char* message, Endpoint* endpoint)
{
	UMsgHandlerMailType *mailOut = comDriverOutMail.alloc();

	if(mailOut != NULL)
	{
		if(USE_LWIP)
		{
			mailOut->endPoint = endpoint;
		}

		strcpy(mailOut->msg, message);
		strcat(mailOut->msg, "\0");

		comDriverOutMail.put(mailOut);
	} else {
		usbSerial.printf("NULL\r\n");
	}
}


void UMsgHandler::SendBroadcast(char* message)
{
	SendMessage(message, NULL);
}


/*
 * Destructor
 * */
UMsgHandler::~UMsgHandler()
{
}
