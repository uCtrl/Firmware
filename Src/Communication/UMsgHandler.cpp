/*
* UMsgHandler.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UMsgHandler.h"

Mail<UMsgHandlerMailType, 2> msgHandlerMail;
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
			parse(mail);
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
void UMsgHandler::parse(UMsgHandlerMailType *aMail)
{
	struct json_token tokens[50];						//No more than 50 json tokens. TODO: To verify
	uint16_t size = sizeof(tokens) / sizeof(tokens[0]);
	const struct json_token *tok = NULL;
	uint16_t messageType = 0;
	uint16_t messageSize = 0;

	//UMsgHandlerMailType *mailOut = comDriverOutMail.alloc();

	//if(USE_LWIP)
	//{
	//	mailOut->endPoint->set_address(aMail->endPoint->get_address(), aMail->endPoint->get_port());
	//}

	//Verify JSON authenticity
	if(parse_json(aMail->msg, strlen(aMail->msg), tokens, size) >= 1)
	{
		tok = find_json_token(tokens, "messageType");
		if(tok != 0)	//messageType trouvé
		{
			bool status;
			int error;

			messageType = atoi(tok->ptr);

			int platformId;
			int deviceId;
			int scenarioId;
			int taskId;

			UPlatform* platform;
			UDevice* device;
			UScenario* scenario;
			UTask* task;
			UCondition* condition;

			const json_token* initialJson;
			UTaskRequest *mail;

			char* jsonArrayPtr;
			char* jsonArray;
			char* ptr;

			//System > Platform > Device > Scenario > Task > Condition
			switch(messageType)
			{
				//REQUESTS GET MESSAGES
				case REQ_GETPLATFORM:

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					mail->taskRequestType = GET_INFO;
					mail->taskCfg.taskCfgType = UPLATFORM;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = 0;
					mail->taskCfg.endpoint = aMail->endPoint;
					mailUTaskHandler.put(mail);

					break;
				case REQ_GETDEVICES:

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					platformId = atoi(find_json_token(tokens, "platformId")->ptr); // ADDED TO JSON

					mail->taskRequestType = GET_INFO;
					mail->taskCfg.taskCfgType = UDEVICE;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = platformId;
					mail->taskCfg.endpoint = aMail->endPoint;
					mailUTaskHandler.put(mail);

					break;
				case REQ_GETSCENARIOS:

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					deviceId = atoi(find_json_token(tokens, "deviceId")->ptr);

					mail->taskRequestType = GET_INFO;
					mail->taskCfg.taskCfgType = USCENARIO;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = deviceId;
					mail->taskCfg.endpoint = aMail->endPoint;
					mailUTaskHandler.put(mail);

					break;
				case REQ_GETTASKS:

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					scenarioId = atoi(find_json_token(tokens, "scenarioId")->ptr);

					mail->taskRequestType = GET_INFO;
					mail->taskCfg.taskCfgType = UTASK;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = scenarioId;
					mail->taskCfg.endpoint = aMail->endPoint;
					mailUTaskHandler.put(mail);

					break;
				case REQ_GETCONDITIONS:

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					taskId = atoi(find_json_token(tokens, "TaskId")->ptr);

					mail->taskRequestType = GET_INFO;
					mail->taskCfg.taskCfgType = UCONDITION;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = taskId;
					mail->taskCfg.endpoint = aMail->endPoint;
					mailUTaskHandler.put(mail);

					break;
				//REQUESTS SAVE MESSAGES
				case REQ_SAVEPLATFORM:

					size = atoi(find_json_token(tokens, "size")->ptr);

					ParseInnerJson(messageType, size, 0, aMail->endPoint, tokens);

					break;
				case REQ_SAVEDEVICES:

					size = atoi(find_json_token(tokens, "size")->ptr);
					platformId = atoi(find_json_token(tokens, "platformId")->ptr);

					ParseInnerJson(messageType, size, platformId, aMail->endPoint, tokens);

					break;
				case REQ_SAVESCENARIOS:

					size = atoi(find_json_token(tokens, "size")->ptr);
					deviceId = atoi(find_json_token(tokens, "deviceId")->ptr);

					ParseInnerJson(messageType, size, deviceId, aMail->endPoint, tokens);

					break;
				case REQ_SAVETASKS:

					size = atoi(find_json_token(tokens, "size")->ptr);
					scenarioId = atoi(find_json_token(tokens, "scenarioId")->ptr);

					ParseInnerJson(messageType, size, scenarioId, aMail->endPoint, tokens);

					break;
				case REQ_SAVECONDITIONS:

					size = atoi(find_json_token(tokens, "size")->ptr);
					taskId = atoi(find_json_token(tokens, "taskId")->ptr);

					ParseInnerJson(messageType, size, taskId, aMail->endPoint, tokens);

					break;
				default:
					SendMessage("Error : Wrong message type", aMail->endPoint);
					break;
			}
		}
		else
		{
			SendMessage("Error : No uCtrl message type found", aMail->endPoint);
		}
	}
	else
	{
		SendMessage("Error : No JSON string", aMail->endPoint);
	}
}

void UMsgHandler::SendMessage(char* message, Endpoint* endpoint)
{
	if(endpoint != NULL)
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

			//delete endpoint;
		} else {
			printf("NULL\r\n");
		}
	}
}

void UMsgHandler::ParseInnerJson(uint16_t messageType, int size, int parent, Endpoint* endpoint, json_token* tokens)
{
	UPlatform* platform;
	UDevice* device;
	UScenario* scenario;
	UTask* task;
	UCondition* condition;

	const json_token* initialJson;
	UTaskRequest *mail;

	bool status;
	int error;
	char* jsonArrayPtr;
	char* jsonArray;
	char* ptr;

	// Here we will try to get elements in the array. We know every
	// object end with }, so we find where the next one is, read the json
	// up to that point, and update the pointer to start reading the next
	// values

	switch(messageType) {
		case REQ_SAVEPLATFORM:
			initialJson = find_json_token(tokens, "platform");
			break;
		case REQ_SAVEDEVICES:
			initialJson = find_json_token(tokens, "devices");
			break;
		case REQ_SAVESCENARIOS:
			initialJson = find_json_token(tokens, "scenarios");
			break;
		case REQ_SAVETASKS:
			initialJson = find_json_token(tokens, "tasks");
			break;
		case REQ_SAVECONDITIONS:
			initialJson = find_json_token(tokens, "conditions");
			break;
	}

	jsonArrayPtr = new char[strlen(initialJson->ptr)];
	jsonArray = jsonArrayPtr;
	strcpy(jsonArray, initialJson->ptr+1); // We dont want the first char

	Thread::wait(100);
	for(int i = 0; i < size; i++)
	{
		ptr = strstr(jsonArray, "}");
		int position = ptr - jsonArray;

		char* jsonToParse = new char[position+2];
		strncpy(jsonToParse, jsonArray, position+1);
		jsonToParse[position+1] = '\0';

		struct json_token newTokens[20];
		uint16_t newSize = sizeof(newTokens) / sizeof(newTokens[0]);

		int length;
		int id;
		char* enabled;
		char* name;
		char* room;
		UDeviceType type;
		int actionValue;
		int deviceId;
		int value;

		if(parse_json(jsonToParse, strlen(jsonToParse), newTokens, newSize) >= 1)
		{
			switch(messageType) {
				case REQ_SAVEPLATFORM:
					id = atoi(find_json_token(newTokens, "id")->ptr);

					enabled = new char[5];
					memset(reinterpret_cast<void*>(enabled), 0, 5);
					memcpy(enabled, find_json_token(newTokens, "enabled")->ptr, find_json_token(newTokens, "enabled")->len);

					name = new char[15];
					memset(reinterpret_cast<void*>(name), 0, 15);
					memcpy(name, find_json_token(newTokens, "name")->ptr, find_json_token(newTokens, "name")->len);

					room = new char[15];
					memset(reinterpret_cast<void*>(room), 0, 15);
					memcpy(room, find_json_token(newTokens, "room")->ptr, find_json_token(newTokens, "room")->len);

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					mail->taskRequestType = SAVE_INFO;
					mail->taskCfg.taskCfgType = UPLATFORM;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = parent;
					mail->taskCfg.endpoint = endpoint;

					platform = new UPlatform(id, enabled, name, room);
					mail->taskCfg.platform = platform;
					mailUTaskHandler.put(mail);
					break;

				case REQ_SAVEDEVICES:
					id = atoi(find_json_token(newTokens, "id")->ptr);
					type = static_cast<UDeviceType>(atoi(find_json_token(newTokens, "type")->ptr));

					length = find_json_token(newTokens, "name")->len;
					name = new char[length+1];
					memset(reinterpret_cast<void*>(name), 0, length+1);
					memcpy(name, find_json_token(newTokens, "name")->ptr, length);

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					mail->taskRequestType = SAVE_INFO;
					mail->taskCfg.taskCfgType = UDEVICE;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = parent;
					mail->taskCfg.endpoint = endpoint;

					device = new UDevice(id, name, type);
					mail->taskCfg.device = device;
					mailUTaskHandler.put(mail);

					break;
				case REQ_SAVESCENARIOS:

					id = atoi(find_json_token(newTokens, "id")->ptr);

					length = find_json_token(newTokens, "name")->len;
					name = new char[length+1];
					memset(reinterpret_cast<void*>(name), 0, length+1);
					memcpy(name, find_json_token(newTokens, "name")->ptr, length);

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					mail->taskRequestType = SAVE_INFO;
					mail->taskCfg.taskCfgType = USCENARIO;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = parent;
					mail->taskCfg.endpoint = endpoint;

					scenario = new UScenario(id, name);
					mail->taskCfg.scenario = scenario;
					mailUTaskHandler.put(mail);
					break;

				case REQ_SAVETASKS:
					id = atoi(find_json_token(newTokens, "id")->ptr);

					length = find_json_token(newTokens, "name")->len;
					name = new char[length+1];
					memset(reinterpret_cast<void*>(name), 0, length+1);
					memcpy(name, find_json_token(newTokens, "name")->ptr, length);

					actionValue = atoi(find_json_token(newTokens, "actionValue")->ptr);
					deviceId = atoi(find_json_token(newTokens, "deviceId")->ptr);

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					mail->taskRequestType = SAVE_INFO;
					mail->taskCfg.taskCfgType = UTASK;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = parent;
					mail->taskCfg.endpoint = endpoint;

					task = new UTask(id, name, actionValue, deviceId);
					mail->taskCfg.task = task;
					mailUTaskHandler.put(mail);
					break;

				case REQ_SAVECONDITIONS:

					Thread::wait(100);

					id = atoi(find_json_token(newTokens, "id")->ptr);

					length = find_json_token(newTokens, "name")->len;
					name = new char[length+1];
					memset(reinterpret_cast<void*>(name), 0, length+1);
					memcpy(name, find_json_token(newTokens, "name")->ptr, length);

					deviceId = atoi(find_json_token(newTokens, "deviceId")->ptr);
					value = atoi(find_json_token(newTokens, "value")->ptr);
					UOperatorType conditionOperator =
						static_cast<UOperatorType>(atoi(find_json_token(newTokens, "conditionOperator")->ptr));

					semMailUTaskHandler.wait();
					mail = mailUTaskHandler.alloc();

					mail->taskRequestType = SAVE_INFO;
					mail->taskCfg.taskCfgType = UCONDITION;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = parent;
					mail->taskCfg.endpoint = endpoint;

					condition = new UCondition(id, name, deviceId, value, conditionOperator);
					mail->taskCfg.condition = condition;
					mailUTaskHandler.put(mail);
					break;
			}
		} else {
			printf("Error no results while parsing.\r\n");
		}
		jsonArray = ptr+2;
		delete [] jsonToParse;
	}
	Thread::wait(100);

	delete [] jsonArrayPtr;

	status = true; error = 0;
	SendMessage(UJsonUtils::AddJsonSaveShell((int) messageType, status, error), endpoint);

}

/*
 * Destructor
 * */
UMsgHandler::~UMsgHandler()
{
}

//const char *str = " { foo: { bar: [ 80, 443 ], baz: 1.2e-21, testbob: "allo toi comment ça va? 123" } } ";
//const char *str = " {"messageType":15,"deviceId":2,"scenarios": [{"id":3,"name":"Semaine"}]}";
//tok = find_json_token(tokens, "foo.testbob");	//tok point to the token's beginning
//tok = find_json_token(tokens, "scenarios[1].name");

//				for(uint16_t i=0; i<tok->len; i++ )				//Next loop replace sprintf command:
//				{												//sprintf(mailOut->msg, "[%.*s]", tok->len, tok->ptr);
//					mailOut->msg[i] = tok->ptr[i];
//				}
