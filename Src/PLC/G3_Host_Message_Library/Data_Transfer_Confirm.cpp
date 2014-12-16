#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Data_Transfer_Confirm.h"
#include "Data_Transfer_Indication.h"
#include "MessageHeader.h"
#include "MessageIds.h"

Data_Transfer_Confirm::Data_Transfer_Confirm(void)
{
	InitializeData();
}


Data_Transfer_Confirm::Data_Transfer_Confirm(BYTE * msg, int offset)
{
	ReadGenericMessage(&_DTC,sizeof(DataTransferConfirm), msg, offset);
}
Data_Transfer_Confirm::Data_Transfer_Confirm(const Data_Transfer_Confirm & msg)
{
	memcpy(&_DTC, & msg._DTC, sizeof(DataTransferConfirm));
}

Data_Transfer_Confirm::~Data_Transfer_Confirm(void)
{
}

void Data_Transfer_Confirm::InitializeData(void)
{
	memset(&_DTC, 0, sizeof(DataTransferConfirm));
	_DTC._Header._Id = Data_Transfer_Id;
	_DTC._Header._Origin = 0x00;
}
HostMessage * Data_Transfer_Confirm::CreateMessage(BYTE * data, int offset)
{
	//
	// The origin and Id are the same for the confirm and indication messages.
	// We have to check the message length to decide which message we have.
	//
	HostMessage * message = NULL;
	MessageHeader header(data, offset);
	if (header.GetMessageLength() == 8)
	{
		message = new Data_Transfer_Confirm(data, offset);
	}
	else
	{
		message = new Data_Transfer_Indication(data, offset);
	}

	return message;
}

TextString Data_Transfer_Confirm::ToString()
{
	TextString temp;
#ifdef P1901
	temp.Format("P1901.2 Data Transfer Confirm: Id=   0x%2.2X\r\n", GetId());
#else
	temp.Format("G3 Data Transfer Confirm: Id=   0x%2.2X\r\n", GetId());
#endif
	temp.AppendFormat("   NSDU_Handle:    %d\r\n", Get_NSDU());
	temp.AppendFormat("   Confirm Flag:   %d\r\n", Get_ConfirmFlag());
	temp.AppendFormat("   Status:         0x%2.2X\r\n\r\n", Get_Status());
	return temp;
}
