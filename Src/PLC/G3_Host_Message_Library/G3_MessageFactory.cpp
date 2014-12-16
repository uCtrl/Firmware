#include "G3_MessageFactory.h"
#include "Get_System_Info.h"
#include "Attach.h"
#include "Detach.h"
#include "Discover.h"
#include "Network_Start.h"
#include "Set_Info.h"
#include "Load_System_Config.h"
#include "Data_Transfer_Confirm.h"
#include "Data_Transfer_Indication.h"
#include "Data_Transfer_Request.h"
#include "PathRequest.h"
#include "PathConfirm.h"
#include "RouteRequest.h"
#include "Set_PSK_PIB.h"
#include "Alarm.h"

#include "../CommonMessageLibrary/Shut_Down_Message.h"
#include "../CommonMessageLibrary/Status_Message.h"
#include "../CommonMessageLibrary/MessageIds.h"

G3_MessageFactory::G3_MessageFactory(void)
{
	//
	// Setup the message factory
	//
	AddToFactory(new Shut_Down_Message());
	AddToFactory(new Status_Message(Shut_Down_Id));

	AddToFactory(new Get_System_Info_Request());
	AddToFactory(new Get_System_Info());

	AddToFactory(new Network_Start_Request());
	AddToFactory(new Network_Start_Confirm());

	AddToFactory(new Discover_Network_Request());
	AddToFactory(new Discover_Network_Confirm());

	AddToFactory(new Attach_Request());
	AddToFactory(new Attach_Confirm());
	AddToFactory(new Attach_Indication());

	AddToFactory(new Detach_Request());
	AddToFactory(new Detach_Confirm());
	AddToFactory(new Detach_Indication());

	AddToFactory(new Set_TX_Info());
	AddToFactory(new Set_RX_Info());
	AddToFactory(new Set_VendorProduct_Info());
	AddToFactory(new Status_Message(Set_Info_Id));

	AddToFactory(new Load_System_Config());
	AddToFactory(new Status_Message(Load_System_Config_Id));

	AddToFactory(new Data_Transfer_Request());
	AddToFactory(new Data_Transfer_Confirm());
	AddToFactory(new Data_Transfer_Indication());

	AddToFactory(new Set_PSK_PIB());
	AddToFactory(new Set_PIB_Reply());

	AddToFactory(new Alarm());

//	AddToFactory(new RouteRequest());  the discover_network_request/confirm will create the proper message
//	AddToFactory(new PathRequest());
//	AddToFactory(new PathConfirm());
}


G3_MessageFactory::~G3_MessageFactory(void)
{
}