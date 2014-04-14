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
			UMsgHandler::parse(mail->msg);
			msgHandlerMail.free(mail);
		}
	}
}

/*
 * Parse and manage JSON messages from UComDriver
 * Please refer to http://uctrl.github.io/ for JSON format.
 * @param aInput Any input JSON string.
 * @return void
 * */
void UMsgHandler::parse(const char* aInput)
{
	struct json_token tokens[50];						//No more than 50 json tokens. TODO: To verify
	uint16_t size = sizeof(tokens) / sizeof(tokens[0]);
	const struct json_token *tok = NULL;
	uint16_t messageType = 0;
	uint16_t messageSize = 0;

	//Verify JSON authenticity
	if(parse_json(aInput, strlen(aInput), tokens, size) >= 1)
	{
		tok = find_json_token(tokens, "messageType");
		messageType = atoi(tok->ptr);
//TODO
		UComDriverOutMailType *mailOut = comDriverOutMail.alloc();
//.
		switch(messageType)
		{
			//REQUESTS MESSAGES
			case REQ_GETPLATFORM:
				//TODO
				break;
			case REQ_GETDEVICES:
				//TODO
				break;
			case REQ_GETSCENARIOS:
				//TODO
				break;
			case REQ_GETTASKS:
				//TODO
				break;
			case REQ_GETCONDITIONS:
				//TODO
				break;
			case REQ_SAVEPLATFORM:
				tok = find_json_token(tokens, "platform");
				strcpy(mailOut->msg, tok->ptr);
				tok = find_json_token(tokens, "size");
				messageSize = atoi(tok->ptr);
				mailOut->id1 = messageSize;
				break;
			case REQ_SAVEDEVICES:
				tok = find_json_token(tokens, "devices");
				strcpy(mailOut->msg, tok->ptr);
				tok = find_json_token(tokens, "size");
				messageSize = atoi(tok->ptr);
				mailOut->id1 = messageSize;
				break;
			case REQ_SAVESCENARIOS:
				tok = find_json_token(tokens, "scenarios");
				strcpy(mailOut->msg, tok->ptr);
				tok = find_json_token(tokens, "size");
				messageSize = atoi(tok->ptr);
				mailOut->id1 = messageSize;
				break;
			case REQ_SAVETASKS:
				tok = find_json_token(tokens, "tasks");
				strcpy(mailOut->msg, tok->ptr);
				tok = find_json_token(tokens, "size");
				messageSize = atoi(tok->ptr);
				mailOut->id1 = messageSize;
				break;
			case REQ_SAVECONDITIONS:
				tok = find_json_token(tokens, "conditions");
				strcpy(mailOut->msg, tok->ptr);
				tok = find_json_token(tokens, "size");
				messageSize = atoi(tok->ptr);
				mailOut->id1 = messageSize;
				break;
			default:
				//TODO : Error managing.
				strcpy(mailOut->msg,"DEFAULT");
				break;
		}
		comDriverOutMail.put(mailOut);
	}
	else
	{
		//TODO : Error managing.
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
