/*
 * UJsonUtils.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: uctrl
 */

#include <UJsonUtils.h>

char* UJsonUtils::m_IpAddress = new char[15];

void UJsonUtils::substr(char* arr, char* returnArr, int begin, int len)
{
    for (int i = 0; i < len; i++)
        returnArr[i] = *(arr + begin + i);
    returnArr[len] = 0;
}

void UJsonUtils::substr(const char* arr, char* returnArr, int begin, int len)
{
    for (int i = 0; i < len; i++)
        returnArr[i] = *(arr + begin + i);
    returnArr[len] = 0;
}


void UJsonUtils::AddJsonGetShell(char* response, int parent, bool status, int error, int messageType, int size, UTaskCfgType taskCfgType, int messageId)
{
	char temp[COM_BUFFER_SIZE] = {0};
	strcpy(temp, response);
	
	strcpy(response, "{ \"messageType\":");

	char buf1[10];
	sprintf(buf1, "%d", messageType);
	strcat(response, buf1);

	strcat(response, ", \"status\":");
	if(status == true)
		strcat(response, "true");
	else
		strcat(response, "false");

	strcat(response, ", \"error\":");
	if(error == 0)
		strcat(response, "null");
	else {
		char buf3[10];
		sprintf(buf3, "%d", error);
		strcat(response, buf3);
	}

	strcat(response, ", \"size\":");

	char buf2[10];
	sprintf(buf2, "%d", size);
	strcat(response, buf2);

	strcat(response, ", \"messageId\":");
	char buf_msgId[10];
	sprintf(buf_msgId, "%d", messageId);
	strcat(response, buf_msgId);
	
	char buf4[10];

	switch(taskCfgType) {
		case UPLATFORM:
			strcat(response, ", \"platform\":");
			break;
		case UDEVICE:
			strcat(response, ", \"platformId\":");

			sprintf(buf4, "%d", parent);
			strcat(response, buf4);

			strcat(response, ", \"devices\":");
			break;
		case USCENARIO:
			strcat(response, ", \"deviceId\":");

			sprintf(buf4, "%d", parent);
			strcat(response, buf4);

			strcat(response, ", \"scenarios\":");
			break;
		case UTASK:
			strcat(response, ", \"scenarioId\":");

			sprintf(buf4, "%d", parent);
			strcat(response, buf4);

			strcat(response, ", \"tasks\":");
			break;
		case UCONDITION:
			strcat(response, ", \"taskId\":");

			sprintf(buf4, "%d", parent);
			strcat(response, buf4);

			strcat(response, ", \"conditions\":");
			break;
		default:
			strcat(response, ", \"error\":");
			break;
	}

	strcat(response, "[");
	strcat(response, temp);
	strcat(response, "]}\0");
}

char* UJsonUtils::AddJsonSaveShell(int messageType, bool status, int error)
{
	// { "messageType": 12, "status": true, "error" : NULL }
	// Max 53 chars, + une petite marge = 60

	char* response = new char[JSON_HEADER_SIZE];
	strcpy(response, "{ \"messageType\":");

	char buf1[3];
	sprintf(buf1, "%d", ((int)messageType)+1);
	strcat(response, buf1);

	strcat(response, ", \"status\":");
	if(status == true)
		strcat(response, "true");
	else
		strcat(response, "false");

	strcat(response, ", \"error\":");
	if(error == 0)
		strcat(response, "null");
	else {
		char buf3[3];
		sprintf(buf3, "%d", error);
		strcat(response, buf3);
	}
	strcat(response, " }\0");

	return response;
}

bool UJsonUtils::ConvertToBool(const char* str) 
{
    if(strcmp(str, "true"))
    	return true;
    else if(strcmp(str, "TRUE"))
    	return true;
    else 
    	return false;
}

void UJsonUtils::SetIpAddress(char* ip)
{
	strcpy(m_IpAddress, ip);
}

char* UJsonUtils::GetIpAddress()
{
	return m_IpAddress;
}