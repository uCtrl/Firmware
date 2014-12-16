#include "HostMessages.h"

void InitializeSystemConfigurationMessage(struct LoadSystemConfig * config)
{
	config->_Header._Id = 0x0C;
	config->_Header._Origin = 0x80;
	config->_Port = NULL;
	config->_SystemConfig = NULL;
	config->_G3_Config = NULL;
};
void FreeSystemConfigMessage(struct LoadSystemConfig * config)
{
	if (config->_Port != NULL)
	{
		free(config->_Port);
		config->_Port = NULL;
	}
	if (config->_SystemConfig != NULL)
	{
		free(config->_SystemConfig);
		config->_SystemConfig = NULL;
	}
	if (config->_G3_Config != NULL)
	{
		free(config->_G3_Config);
		config->_G3_Config = NULL;
	}
}

BYTE * MakeLoadSystemConfigurationMessage(struct LoadSystemConfig * config)
{
	UINT16 totalMessageLength = sizeof(struct Header) + sizeof(struct CRC_Header);
	int tlvLength = 0;
	BYTE * payLoad = NULL;
	BYTE * msg = NULL;
	int offset = 0;
	int headerLength = 0;

	if (config->_Port != NULL)
	{
		config->_Port->_Type = 0x0001;
		config->_Port->_Length = 1;

		tlvLength += sizeof(struct PortDesignation);
	}
	if (config->_SystemConfig != NULL)
	{
		config->_SystemConfig->_Type = 0x0003;
		config->_SystemConfig->_Length = 26;

		tlvLength += sizeof(struct SystemConfig);
	}
	if(config->_G3_Config != NULL)
	{
		config->_G3_Config->_Type = 0x0008;
		config->_G3_Config->_Length = 16;
		config->_G3_Config->_MAC_SegmentSize = 239; // obsolete but needed for older dsp s/w

		tlvLength += sizeof(struct G3Configuration);
	}
	totalMessageLength += (UINT16)tlvLength;
	headerLength = totalMessageLength - sizeof(struct Header);;
	//
	// Make sure the message length is even
	//
	if ((totalMessageLength & 1) != 0)
	{
		totalMessageLength++;
	}
	msg = (BYTE *) malloc(totalMessageLength);
	memset(msg, 0, totalMessageLength);

	payLoad = (BYTE *) malloc(tlvLength);

	if (config->_Port != NULL)
	{
		memcpy(&payLoad[offset], config->_Port, sizeof(struct PortDesignation));
		offset += sizeof(struct PortDesignation);
	}
	if (config->_SystemConfig != NULL)
	{
		memcpy(&payLoad[offset], config->_SystemConfig, sizeof(struct SystemConfig));
		offset += sizeof(struct SystemConfig);
	}
	if(config->_G3_Config != NULL)
	{
		memcpy(&payLoad[offset], config->_G3_Config, sizeof(struct G3Configuration));
		offset += sizeof(struct G3Configuration);
	}
	
	config->_Header._Length = (UINT16)headerLength;
	
	MakeCRC_Header(&config->_CRC_Header, &config->_Header, sizeof(struct Header), payLoad, tlvLength);

	offset = 0;
	memcpy(&msg[offset], config, sizeof(struct Header) + sizeof(struct CRC_Header));
	offset += sizeof(struct Header) + sizeof(struct CRC_Header);
	memcpy(&msg[offset], payLoad, tlvLength);

	free(payLoad);
	
	return msg;
}

int ReadLoadSystemConfigurationMessage(struct LoadSystemConfig * configMessage, BYTE * message, int offset)
{
	int headerSize = sizeof(struct Header) + sizeof(struct CRC_Header);
	int type = 0;
	int length = 0;
	int msgLength = 0;
	struct PortDesignation * pd = NULL;
	struct SystemConfig * sc = NULL;
	struct G3Configuration * gc = NULL;
	//
	// free any previous allocations..
	//
	FreeSystemConfigMessage(configMessage);
	
	memcpy(configMessage, message, headerSize);
	offset += headerSize;
	msgLength = configMessage->_Header._Length + sizeof(struct CRC_Header);

	while (offset < msgLength)
	{
		memcpy(&type, &message[offset], sizeof(UINT16));
		memcpy(&length, &message[offset+2], sizeof(UINT16));

		if (type == 0x0001)
		{
			pd = (struct PortDesignation *) malloc(sizeof(struct PortDesignation));
			memset(pd, 0, sizeof(struct PortDesignation));
			memcpy(pd, & message[offset], sizeof(struct PortDesignation));
			configMessage->_Port = pd;
		}
		else if (type == 0x0003)
		{
			sc = (struct SystemConfig *) malloc(sizeof(struct SystemConfig));
			memcpy(sc, & message[offset], sizeof(struct SystemConfig));
			configMessage->_SystemConfig = sc;
		}
		else if (type == 0x0008)
		{
			gc = (struct G3Configuration *) malloc(sizeof(struct G3Configuration));
			memcpy(gc, & message[offset], sizeof(struct G3Configuration));
			configMessage->_G3_Config = gc;
		}
		offset += length + 4;
	}
	return offset;
}