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

	UMsgHandlerMailType *mailOut = comDriverOutMail.alloc();
	if(USE_LWIP)
	{
		mailOut->endPoint.set_address(aMail->endPoint.get_address(), aMail->endPoint.get_port());
	}
	//Verify JSON authenticity
	if(parse_json(aMail->msg, strlen(aMail->msg), tokens, size) >= 1)
	{
		tok = find_json_token(tokens, "messageType");
		if(tok != 0)	//messageType trouvé
		{
			messageType = atoi(tok->ptr);

			int scenarioId;
			const json_token* name_from_json;
			char* name;
			UScenario scenario;
			
			//System > Platform > Device > Scenario > Task > Condition
			switch(messageType)
			{
				//REQUESTS GET MESSAGES
				case REQ_GETPLATFORM:
					//TODO
					break;
				case REQ_GETDEVICES:
					//tok = find_json_token(tokens, "deviceId");
					//TODO
					break;
				case REQ_GETSCENARIOS:

					scenarioId = atoi(find_json_token(tokens, "scenarioId")->ptr);
					name_from_json = find_json_token(tokens, "name");
					name = (char*) name_from_json->ptr;
					scenario = UScenario(scenarioId, name);

					strcpy(mailOut->msg, scenario.GetJSON());

					//mailOut->msg[name->len] = '\0';
					break;
				case REQ_GETTASKS:
					tok = find_json_token(tokens, "scenarioId");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					break;
				case REQ_GETCONDITIONS:
					tok = find_json_token(tokens, "taskId");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					break;
				//REQUESTS SAVE MESSAGES
				case REQ_SAVEPLATFORM:
					tok = find_json_token(tokens, "platform");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					tok = find_json_token(tokens, "size");
					messageSize = atoi(tok->ptr);
					break;
				case REQ_SAVEDEVICES:
					tok = find_json_token(tokens, "devices");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					tok = find_json_token(tokens, "size");
					messageSize = atoi(tok->ptr);
					break;
				case REQ_SAVESCENARIOS:
					tok = find_json_token(tokens, "scenarios");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					tok = find_json_token(tokens, "size");
					messageSize = atoi(tok->ptr);
					break;
				case REQ_SAVETASKS:
					tok = find_json_token(tokens, "tasks");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					tok = find_json_token(tokens, "size");
					messageSize = atoi(tok->ptr);
					break;
				case REQ_SAVECONDITIONS:
					tok = find_json_token(tokens, "conditions");
					strcpy(mailOut->msg, tok->ptr);
					mailOut->msg[tok->len] = '\0';
					tok = find_json_token(tokens, "size");
					messageSize = atoi(tok->ptr);
					break;
				default:
					//TODO : Error managing.
					strcpy(mailOut->msg, "DEFAULT\0");
					break;
			}
		}
		else
		{
			strcpy(mailOut->msg, "Error : No uCtrl message type found\0");
		}
	}
	else
	{
		//strcpy(mailOut->msg, "Error : No JSON string\0");
		strcpy(mailOut->msg, "Error : No JSON string");
		strcat(mailOut->msg, "\0");
	}
	comDriverOutMail.put(mailOut);
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
