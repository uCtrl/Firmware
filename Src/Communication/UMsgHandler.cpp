/*
* UMsgHandler.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UMsgHandler.h"

Mail<UMsgHandlerMailType, 2> msgHandlerMail;

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
			bool status; int error;

			messageType = atoi(tok->ptr);

			int parent;
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
					mail->taskCfg.taskCfgType = UTASK;
					mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
					mail->taskCfg.id = 0;
					mail->taskCfg.parentId = taskId;
					mail->taskCfg.endpoint = aMail->endPoint;
					mailUTaskHandler.put(mail);

					break;
				//REQUESTS SAVE MESSAGES
				case REQ_SAVEPLATFORM:

					size = atoi(find_json_token(tokens, "size")->ptr);

					// Here we will try to get elements in the array. We know every
					// object end with }, so we find where the next one is, read the json
					// up to that point, and update the pointer to start reading the next
					// values

					initialJson = find_json_token(tokens, "platform");
					jsonArrayPtr = new char[strlen(initialJson->ptr)];
					jsonArray = jsonArrayPtr;
					strcpy(jsonArray, initialJson->ptr+1); // We dont want the first char

					for(int i = 0; i < size; i++)
					{
						ptr = strstr(jsonArray, "}");
						int position = ptr - jsonArray;

						char* jsonToParse = new char[position+2];
						strncpy(jsonToParse, jsonArray, position+1);
						jsonToParse[position+1] = '\0';

						struct json_token newTokens[10];
						uint16_t newSize = sizeof(newTokens) / sizeof(newTokens[0]);

						if(parse_json(jsonToParse, strlen(jsonToParse), newTokens, newSize) >= 1)
						{
							int id = atoi(find_json_token(newTokens, "id")->ptr);

							char* enabled = new char[5];
							memset(reinterpret_cast<void*>(enabled), 0, 5);
							memcpy(enabled, find_json_token(newTokens, "enabled")->ptr, find_json_token(newTokens, "enabled")->len);

							char* name = new char[15];
							memset(reinterpret_cast<void*>(name), 0, 15);
							memcpy(name, find_json_token(newTokens, "name")->ptr, find_json_token(newTokens, "name")->len);

							char* room = new char[15];
							memset(reinterpret_cast<void*>(room), 0, 15);
							memcpy(room, find_json_token(newTokens, "room")->ptr, find_json_token(newTokens, "room")->len);

							semMailUTaskHandler.wait();
							mail = mailUTaskHandler.alloc();

							mail->taskRequestType = SAVE_INFO;
							mail->taskCfg.taskCfgType = UPLATFORM;
							mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
							mail->taskCfg.id = 0;
							mail->taskCfg.parentId = 0;
							mail->taskCfg.endpoint = aMail->endPoint;

							platform = new UPlatform(id, enabled, name, room);
							mail->taskCfg.platform = platform;
							mailUTaskHandler.put(mail);
						}
						jsonArray = ptr+2;
						delete jsonToParse;

					}

					delete jsonArrayPtr;

				    status = true; error = 0;
				    SendMessage(UJsonUtils::AddJsonSaveShell((int) messageType, status, error), aMail->endPoint);

					break;
				case REQ_SAVEDEVICES:

					size = atoi(find_json_token(tokens, "size")->ptr);
					platformId = atoi(find_json_token(tokens, "platformId")->ptr);

					// Here we will try to get elements in the array. We know every
					// object end with }, so we find where the next one is, read the json
					// up to that point, and update the pointer to start reading the next
					// values

					initialJson = find_json_token(tokens, "devices");
					jsonArrayPtr = new char[strlen(initialJson->ptr)];
					jsonArray = jsonArrayPtr;
					strcpy(jsonArray, initialJson->ptr+1); // We dont want the first char

					for(int i = 0; i < size; i++)
					{
						ptr = strstr(jsonArray, "}");
						int position = ptr - jsonArray;

						char* jsonToParse = new char[position+2];
						strncpy(jsonToParse, jsonArray, position+1);
						jsonToParse[position+1] = '\0';

						struct json_token newTokens[10];
						uint16_t newSize = sizeof(newTokens) / sizeof(newTokens[0]);

						if(parse_json(jsonToParse, strlen(jsonToParse), newTokens, newSize) >= 1)
						{
							int id = atoi(find_json_token(newTokens, "id")->ptr);
							UDeviceType type = static_cast<UDeviceType>(atoi(find_json_token(newTokens, "type")->ptr));

							char* name = new char[DEVICE_NAME_LENGHT];
							memset(reinterpret_cast<void*>(name), 0, DEVICE_NAME_LENGHT);
							memcpy(name, find_json_token(newTokens, "name")->ptr, find_json_token(newTokens, "name")->len);

							semMailUTaskHandler.wait();
							mail = mailUTaskHandler.alloc();

							mail->taskRequestType = SAVE_INFO;
							mail->taskCfg.taskCfgType = UDEVICE;
							mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
							mail->taskCfg.id = 0;
							mail->taskCfg.parentId = platformId;
							mail->taskCfg.endpoint = aMail->endPoint;
							mailUTaskHandler.put(mail);

							device = new UDevice(id, name, type);
							mail->taskCfg.device = device;
							mailUTaskHandler.put(mail);
						}
						jsonArray = ptr+2;
						delete jsonToParse;
					}

					delete jsonArrayPtr;

				    status = true; error = 0;
				    SendMessage(UJsonUtils::AddJsonSaveShell((int) messageType, status, error), aMail->endPoint);

					break;
				case REQ_SAVESCENARIOS:

					size = atoi(find_json_token(tokens, "size")->ptr);
					deviceId = atoi(find_json_token(tokens, "deviceId")->ptr);

					// Here we will try to get elements in the array. We know every
					// object end with }, so we find where the next one is, read the json
					// up to that point, and update the pointer to start reading the next
					// values

					initialJson = find_json_token(tokens, "scenarios");
					jsonArrayPtr = new char[strlen(initialJson->ptr)];
					jsonArray = jsonArrayPtr;
					strcpy(jsonArray, initialJson->ptr+1); // We dont want the first char

					for(int i = 0; i < size; i++)
					{
						ptr = strstr(jsonArray, "}");
						int position = ptr - jsonArray;

						char* jsonToParse = new char[position+2];
						strncpy(jsonToParse, jsonArray, position+1);
						jsonToParse[position+1] = '\0';

						struct json_token newTokens[10];
						uint16_t newSize = sizeof(newTokens) / sizeof(newTokens[0]);

						if(parse_json(jsonToParse, strlen(jsonToParse), newTokens, newSize) >= 1)
						{
							int id = atoi(find_json_token(newTokens, "id")->ptr);

							char* name = new char[DEVICE_NAME_LENGHT];
							memset(reinterpret_cast<void*>(name), 0, DEVICE_NAME_LENGHT);
							memcpy(name, find_json_token(newTokens, "name")->ptr, find_json_token(newTokens, "name")->len);

							semMailUTaskHandler.wait();
							mail = mailUTaskHandler.alloc();

							mail->taskRequestType = SAVE_INFO;
							mail->taskCfg.taskCfgType = USCENARIO;
							mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
							mail->taskCfg.id = 0;
							mail->taskCfg.parentId = deviceId;
							mail->taskCfg.endpoint = aMail->endPoint;
							mailUTaskHandler.put(mail);

							scenario = new UScenario(id, name);
							mail->taskCfg.scenario = scenario;
							mailUTaskHandler.put(mail);
						}
						jsonArray = ptr+2;
						delete jsonToParse;
					}

					delete jsonArrayPtr;

				    status = true; error = 0;
				    SendMessage(UJsonUtils::AddJsonSaveShell((int) messageType, status, error), aMail->endPoint);

					break;
				case REQ_SAVETASKS:

					size = atoi(find_json_token(tokens, "size")->ptr);
					scenarioId = atoi(find_json_token(tokens, "scenarioId")->ptr);

					// Here we will try to get elements in the array. We know every
					// object end with }, so we find where the next one is, read the json
					// up to that point, and update the pointer to start reading the next
					// values

					initialJson = find_json_token(tokens, "tasks");
					jsonArrayPtr = new char[strlen(initialJson->ptr)];
					jsonArray = jsonArrayPtr;
					strcpy(jsonArray, initialJson->ptr+1); // We dont want the first char

					for(int i = 0; i < size; i++)
					{
						ptr = strstr(jsonArray, "}");
						int position = ptr - jsonArray;

						char* jsonToParse = new char[position+2];
						strncpy(jsonToParse, jsonArray, position+1);
						jsonToParse[position+1] = '\0';

						struct json_token newTokens[10];
						uint16_t newSize = sizeof(newTokens) / sizeof(newTokens[0]);

						if(parse_json(jsonToParse, strlen(jsonToParse), newTokens, newSize) >= 1)
						{
							int id = atoi(find_json_token(newTokens, "id")->ptr);

							char* name = new char[DEVICE_NAME_LENGHT];
							memset(reinterpret_cast<void*>(name), 0, DEVICE_NAME_LENGHT);
							memcpy(name, find_json_token(newTokens, "name")->ptr, find_json_token(newTokens, "name")->len);

							int actionValue = atoi(find_json_token(newTokens, "actionValue")->ptr);
							int device = atoi(find_json_token(newTokens, "device")->ptr);

							semMailUTaskHandler.wait();
							mail = mailUTaskHandler.alloc();

							mail->taskRequestType = SAVE_INFO;
							mail->taskCfg.taskCfgType = UTASK;
							mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
							mail->taskCfg.id = 0;
							mail->taskCfg.parentId = scenarioId;
							mail->taskCfg.endpoint = aMail->endPoint;
							mailUTaskHandler.put(mail);

							task = new UTask(id, name, actionValue, device);
							mail->taskCfg.task = task;
							mailUTaskHandler.put(mail);
						}
						jsonArray = ptr+2;
						delete jsonToParse;
					}

					delete jsonArrayPtr;

				    status = true; error = 0;
				    SendMessage(UJsonUtils::AddJsonSaveShell((int) messageType, status, error), aMail->endPoint);

					break;
				case REQ_SAVECONDITIONS:

					size = atoi(find_json_token(tokens, "size")->ptr);
					taskId = atoi(find_json_token(tokens, "taskId")->ptr);

					// Here we will try to get elements in the array. We know every
					// object end with }, so we find where the next one is, read the json
					// up to that point, and update the pointer to start reading the next
					// values

					initialJson = find_json_token(tokens, "tasks");
					jsonArrayPtr = new char[strlen(initialJson->ptr)];
					jsonArray = jsonArrayPtr;
					strcpy(jsonArray, initialJson->ptr+1); // We dont want the first char

					for(int i = 0; i < size; i++)
					{
						ptr = strstr(jsonArray, "}");
						int position = ptr - jsonArray;

						char* jsonToParse = new char[position+2];
						strncpy(jsonToParse, jsonArray, position+1);
						jsonToParse[position+1] = '\0';

						struct json_token newTokens[10];
						uint16_t newSize = sizeof(newTokens) / sizeof(newTokens[0]);

						if(parse_json(jsonToParse, strlen(jsonToParse), newTokens, newSize) >= 1)
						{
							int id = atoi(find_json_token(newTokens, "id")->ptr);

							char* name = new char[DEVICE_NAME_LENGHT];
							memset(reinterpret_cast<void*>(name), 0, DEVICE_NAME_LENGHT);
							memcpy(name, find_json_token(newTokens, "name")->ptr, find_json_token(newTokens, "name")->len);

							int sensorId = atoi(find_json_token(newTokens, "sensorId")->ptr);
							int value = atoi(find_json_token(newTokens, "value")->ptr);
							UOperatorType conditionOperator = static_cast<UOperatorType>(atoi(find_json_token(newTokens, "conditionOperator")->ptr));

							semMailUTaskHandler.wait();
							mail = mailUTaskHandler.alloc();

							mail->taskRequestType = SAVE_INFO;
							mail->taskCfg.taskCfgType = UCONDITION;
							mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
							mail->taskCfg.id = 0;
							mail->taskCfg.parentId = taskId;
							mail->taskCfg.endpoint = aMail->endPoint;
							mailUTaskHandler.put(mail);

							condition = new UCondition(id, name, sensorId, value, conditionOperator);
							mail->taskCfg.condition = condition;
							mailUTaskHandler.put(mail);
						}
						jsonArray = ptr+2;
						delete jsonToParse;
					}

					delete jsonArrayPtr;

				    status = true; error = 0;
				    SendMessage(UJsonUtils::AddJsonSaveShell((int) messageType, status, error), aMail->endPoint);

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
