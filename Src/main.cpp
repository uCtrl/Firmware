/*
* main.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "mbed.h"
#include "rtos.h"
#include "cfg.h"

#include "threadCfg.h"
#include "UComDriverIn.h"
#include "UComDriverOut.h"
#include "UMsgHandler.h"
#include "UTaskHandler.h"
#include "UPinUtils.h"
#include "UDeviceHandler.h"
#include "UDeviceType.h"
#include "UJsonUtils.h"

#include "UPlatform.h"
#include "UDevice.h"
#include "UScenario.h"
#include "UTask.h"
#include "UCondition.h"

//#include "redefinitionOfNewAndDelete.h"


extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER> mailUTaskHandler;

//extern "C" void mbed_mac_address(char *mac) { mac[0]=0x00; mac[1]=0x02; mac[2]=0xf7; mac[3]=0xf0; mac[4]=0x22; mac[5]=0x45; }

#ifdef DEBUG_PRINT
//extern Semaphore semMailUTaskHandler;
//extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;
#endif

#ifdef TARGET_LPC1768
#define LED_RED LED1
#define LED_GREEN LED2
#define LED_BLUE LED3
#endif
DigitalOut ledr(UPinUtils::leds[0]);
DigitalOut ledg(UPinUtils::leds[1]);
DigitalOut ledb(UPinUtils::leds[2]);
DigitalOut ledw(UPinUtils::leds[3]);

void sendPlatformInfo();
void setDefaultPlatform(); 
void setDefaultDevices(int devices); 
void setDefaultScenarios(int scenarios); 
void setDefaultTasks(int tasks); 
void setDefaultConditions(int conditions); 

Serial usbSerial(USBTX, USBRX);

UMsgHandler msgHandler;
UDeviceHandler uDeviceHandler = UDeviceHandler();
UTaskHandler uTaskHandler = UTaskHandler(&uDeviceHandler);

void startComDriverInThread(void const *args)
{
	UComDriverIn comDriverIn;
	comDriverIn.start();
}

void startComDriverOutThread(void const *args)
{
	UComDriverOut comDriverOut;
	comDriverOut.start();
}

void startMsgHandlerThread(void const *args)
{
	msgHandler.start();
}

void devicePoolingThread(void const *args)
{
	uDeviceHandler.StartPoolingSensors();
}

void taskHandlerThread(void const *args)
{
	uTaskHandler.start();
}

void softRest(void const *args)
{
	Thread::wait(180000);
    NVIC_SystemReset();
}

int main (void)
{
	usbSerial.printf("Initializing...\r\n");

    Thread comDriverInThread(	startComDriverInThread,		NULL,	COM_DRIVER_IN_PRIORITY,		COM_DRIVER_IN_STACK_SIZE, 	COM_DRIVER_IN_STACK);
    Thread comDriverOutThread(	startComDriverOutThread,	NULL,	COM_DRIVER_OUT_PRIORITY,	COM_DRIVER_OUT_STACK_SIZE, 	COM_DRIVER_OUT_STACK);
	Thread deviceThread(		devicePoolingThread,		NULL,	DEVICE_HANDLER_PRIORITY,	DEVICE_HANDLER_STACK_SIZE, 	DEVICE_HANDLER_STACK);
    Thread msgHandlerThread(	startMsgHandlerThread,		NULL,	MESSAGE_HANDLER_PRIORITY,	MESSAGE_HANDLER_STACK_SIZE, MESSAGE_HANDLER_STACK);
	Thread taskThread(			taskHandlerThread,			NULL,	TASK_HANDLER_PRIORITY,		TASK_HANDLER_STACK_SIZE, 	TASK_HANDLER_STACK);
	
	//Thread softResetThread(		softRest,					NULL,	COM_DRIVER_IN_PRIORITY,		SOFT_RESET_STACK_SIZE, 		SOFT_RESET_STACK);
	
	if(USE_DHCP)
		Thread::wait(2000);
	else
		Thread::wait(20000);	

	ledr = true;
	ledg = true;
	ledb = true;
	ledw = true;
	
	setDefaultPlatform();	
		
	if(DEFAULT_CONFIG) 
	{ 
		if(FREESCALE_TEMP) 
		{
			setDefaultDevices(8); //Temperature sensor
		}
		else if (PLATFORM_1) 
		{
			// If both sensors detect light outside, close all the lamps. 
			// If one sensor detect darkness, light all the lamps
			
			setDefaultDevices(10);  //Light sensor id 100
			setDefaultDevices(12); //Light actuator id 120
			setDefaultScenarios(7);	//Id : 121, Scenario actuator 120
			setDefaultTasks(14); //Id : 122, Actuator 120 on
			setDefaultTasks(15); //Id : 123, Actuator 120 on
			setDefaultTasks(16); //Id : 124, Actuator 120 off
			setDefaultConditions(14); //Id : 125, Task 122, if sensor 100 = dark
			setDefaultConditions(15); //Id : 126, Task 123, if sensor 110 = dark
			setDefaultConditions(16); //Id : 127, Task 124, if sensor 100 = light
			setDefaultConditions(17); //Id : 128, Task 124, if sensor 110 = light
		} 
		else if (PLATFORM_2) 
		{
			// If both sensors detect light outside, close all the lamps. 
			// If one sensor detect darkness, light all the lamps
			
			setDefaultDevices(11); //Light sensor id 110
			setDefaultDevices(13); //Light actuator id 130
			setDefaultScenarios(8);	//Id : 131, Scenario actuator 130
			setDefaultTasks(17); //Id : 132, Actuator 130 on
			setDefaultTasks(18); //Id : 133, Actuator 130 on
			setDefaultTasks(19); //Id : 134, Actuator 130 off
			setDefaultConditions(18); //Id : 135, Task 132, if sensor 100 = dark
			setDefaultConditions(19); //Id : 136, Task 133, if sensor 110 = dark
			setDefaultConditions(20); //Id : 137, Task 134, if sensor 100 = light
			setDefaultConditions(21); //Id : 138, Task 134, if sensor 110 = light
		}
		else
		{
			//setDefaultDevices(0);	//Light sensor
			setDefaultDevices(1); 
			setDefaultDevices(2);
			setDefaultDevices(3);
			setDefaultDevices(4);
			setDefaultDevices(5);
			//setDefaultDevices(6); //Logo flash
			setDefaultDevices(7);
			//setDefaultDevices(8); //Temperature sensor
			setDefaultScenarios(0);	
			setDefaultScenarios(1);	
			setDefaultScenarios(2);	
			setDefaultScenarios(3);	
			setDefaultScenarios(4);	
			setDefaultScenarios(5);	
			setDefaultScenarios(6);	
			setDefaultTasks(0);
			setDefaultTasks(1);	
			setDefaultTasks(2);
			setDefaultTasks(3);	
			setDefaultTasks(4);
			setDefaultTasks(5);	
			setDefaultTasks(6);
			setDefaultTasks(7);	
			setDefaultTasks(8);
			setDefaultTasks(9);	
			setDefaultTasks(10);
			setDefaultTasks(11);	
			setDefaultTasks(12);
			setDefaultTasks(13);
			setDefaultConditions(0);
			setDefaultConditions(1);
			setDefaultConditions(2);
			setDefaultConditions(3);
			setDefaultConditions(4);
			setDefaultConditions(5);
			setDefaultConditions(6);
			setDefaultConditions(7);
			setDefaultConditions(8);
			setDefaultConditions(9);
			setDefaultConditions(10);
			setDefaultConditions(11);
			setDefaultConditions(12);
			setDefaultConditions(13);
		}
	}
	
	Thread::wait(1000);
	
	sendPlatformInfo();
	
	for(;;)
	{		
		//ledr = !ledr;
		Thread::wait(DELAY_BETWEEN_PLATFORM_BROADCASTS);
		sendPlatformInfo();
	}
}

void sendPlatformInfo()
{
	//char jsonToSend[COM_BUFFER_SIZE] = {0};
	char* jsonToSend = new char[COM_BUFFER_SIZE];
	uTaskHandler.m_platform->GetJSON(jsonToSend);
	
	int parent = 0;
	bool status = true;
	int error = 0;
	int messageType = 2;
	int size = 1;
	UTaskCfgType taskCfgType = UPLATFORM;
	int messageId = 0;
	
	usbSerial.printf("Address of jsonToSend : %d\r\n", jsonToSend);
	UJsonUtils::AddJsonGetShell(jsonToSend, parent, status, error, messageType, size, taskCfgType, messageId);
			
	// We send a broadcasted response to a virtual get platform on boot, so we can let the others know we exist
	msgHandler.SendBroadcast(jsonToSend);
	delete [] jsonToSend;
}

void setDefaultPlatform()
{	
	UTaskRequest *mail;
	UPlatform* platform;
		
	int id = 1;
	string firmwareVersion = "1.0.0.0";
	string name = "uCtrl Hardware";	
	string ip = string(UJsonUtils::GetIpAddress());	
	int port = 7;	
	int status = 0;				
	string room = "Centre culturel";						
	bool enabled = true;
	int lastUpdated = 0;
	
	if(FREESCALE_TEMP) 
	{
		id = 100;
		firmwareVersion = "1.0.0.0";
		name = "uCtrl Hardware - Temperature";	
		ip = string(UJsonUtils::GetIpAddress());	
		port = 7;	
		status = 0;				
		room = "Centre culturel";						
		enabled = true;
		lastUpdated = 0;
	} 
	else if (PLATFORM_1) 
	{
		id = 1;
		firmwareVersion = "1.0.0.0";
		name = "uCtrl Hardware - Platforme 1";	
		ip = string(UJsonUtils::GetIpAddress());	
		port = 7;	
		status = 0;				
		room = "4115";						
		enabled = true;
		lastUpdated = 0;
	} 
	else if (PLATFORM_2) {
		id = 100;
		firmwareVersion = "1.0.0.0";
		name = "uCtrl Hardware - Platforme 2";	
		ip = string(UJsonUtils::GetIpAddress());	
		port = 7;	
		status = 0;				
		room = "4115";						
		enabled = true;
		lastUpdated = 0;
	}
					
	semMailUTaskHandler.wait();
	mail = mailUTaskHandler.alloc();

	mail->taskRequestType = SAVE_INFO;
	mail->taskCfg.taskCfgType = UPLATFORM;
	mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
	mail->taskCfg.parentId = 0;
	mail->taskCfg.endpoint = NULL;

	platform = new UPlatform(id, firmwareVersion, name, ip, port, status, room, enabled, lastUpdated);
	mail->taskCfg.platform = platform;
	mailUTaskHandler.put(mail);
}

void setDefaultDevices(int devices)
{
	UTaskRequest *mail;
	UDevice* device;
				
	int id; string name; UDeviceType type; string description; string maxValue; string minValue;
	string value; int precision; int status; string unitLabel; bool enabled; int lastUpdated;
	
	string value_flow = "1";
	string value_flow_dir = "1";
	string value_foyer_red = "1";
	string value_foyer_blue = "1";
	string value_logo = "1";
	string value_chauffage = "1";
	
	int platformId = 1;
	
	switch(devices)
	{
		case 0:
			id = 2;
			name = "Capteur de lumiere embarque";
			type = Sensor_Light;					
			description = "Capteur lumiere du salon";
			maxValue = "100";
			minValue = "0";
			value = "1";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 1:
			id = 3;
			name = "Led A";
			type = Actuator_Switch;					
			description = "Led embarquee sur mbed";
			maxValue = "100";
			minValue = "0";
			value = "1";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 2:
			id = 20;
			name = "Leds representant le PLC";
			type = Actuator_Switch;					
			description = "ON/OFF";
			maxValue = "1";
			minValue = "0";
			value = value_flow;
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 3:
			id = 30;
			name = "Direction des leds du PLC";
			type = Actuator_LedsFlow;					
			description = "UP/DOWN";
			maxValue = "1";
			minValue = "0";
			value = value_flow_dir;
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 4:
			id = 40;
			name = "Activer image foyer";
			type = Actuator_Switch;					
			description = "ON/OFF";
			maxValue = "1";
			minValue = "0";
			value = value_foyer_red;
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 5:
			id = 50;
			name = "Activer image ventilation";
			type = Actuator_Switch;					
			description = "ON/OFF";
			maxValue = "1";
			minValue = "0";
			value = value_foyer_blue;
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 6:
			id = 60;
			name = "Leds logo";
			type = Actuator_Switch;					
			description = "ON/OFF";
			maxValue = "1";
			minValue = "0";
			value = value_logo;
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 7:
			id = 70;
			name = "Chauffage";
			type = Actuator_Switch;					
			description = "ON/OFF";
			maxValue = "1";
			minValue = "0";
			value = value_chauffage;
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			break;
			
		case 8:
			id = 80;
			name = "Capteur Temperature";
			type = Sensor_Temperature;					
			description = "Dans la boite avec les lumieres";
			maxValue = "1";
			minValue = "0";
			value = "0";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			platformId = 100;
			break;
			
		case 10:
			id = 100;
			name = "Capteur Lumiere 1";
			type = Sensor_Light;					
			description = "Capteur de lumiere platforme 1";
			maxValue = "1";
			minValue = "0";
			value = "0";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			platformId = 1;
			break;
			
		case 11:
			id = 110;
			name = "Capteur Lumiere 2";
			type = Sensor_Light;					
			description = "Capteur de lumiere platforme 2";
			maxValue = "1";
			minValue = "0";
			value = "0";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			platformId = 100;
			break;
			
		case 12:
			id = 120;
			name = "Led 1";
			type = Actuator_Switch;					
			description = "Led embarquee sur mbed";
			maxValue = "1";
			minValue = "0";
			value = "0";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			platformId = 1;
			break;
			
		case 13:
			id = 130;
			name = "Led 2";
			type = Actuator_Switch;					
			description = "Led embarquee sur mbed";
			maxValue = "1";
			minValue = "0";
			value = "0";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = true;
			lastUpdated = 1;
			platformId = 100;
			break;
			
		default:
			id = -1;
			name = "";
			type = Actuator_RGB;					
			description = "";
			maxValue = "";
			minValue = "";
			value = "";
			precision = 1;
			status = 0;
			unitLabel = "";
			enabled = false;
			lastUpdated = -11;
			break;
	}
	
	
	semMailUTaskHandler.wait();
	mail = mailUTaskHandler.alloc();
	
	mail->taskRequestType = SAVE_INFO;
	mail->taskCfg.taskCfgType = UDEVICE;
	mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
	mail->taskCfg.parentId = platformId;
	mail->taskCfg.endpoint = NULL;
	
	device = new UDevice(id, name, type, description, maxValue, minValue, value, precision, status, unitLabel, enabled, lastUpdated);
	mail->taskCfg.device = device;
	mailUTaskHandler.put(mail);
}

void setDefaultScenarios(int scenarios)
{
	UTaskRequest *mail;
	UScenario* scenario;

	int id = 4;
	string name = "Scenario leds flow";
	bool enabled = true;
	int lastUpdated = 0;

	int deviceId = 0;
	
	switch(scenarios)
	{
		case 0 :
			id = 4;
			name = "Scenario led embarquee";
			enabled = true;
			lastUpdated = 0;
			deviceId = 3;
			break;
		case 1 :
			id = 21;
			name = "Scenario leds flow on/off";
			enabled = false;
			lastUpdated = 0;
			deviceId = 20;
			break;
		case 2 :
			id = 31;
			name = "Scenario leds flow up/down";
			enabled = true;
			lastUpdated = 0;
			deviceId = 30;
			break;
		case 3 :
			id = 41;
			name = "Scenario foyer rouge";
			enabled = true;
			lastUpdated = 0;
			deviceId = 40;
			break;
		case 4 :
			id = 51;
			name = "Scenario foyer bleu";
			enabled = true;
			lastUpdated = 0;
			deviceId = 50;
			break;
		case 5 :
			id = 61;
			name = "Scenario logo flash";
			enabled = true;
			lastUpdated = 0;
			deviceId = 60;
			break;
		case 6 :
			id = 71;
			name = "Scenario chauffage active";
			enabled = true;
			lastUpdated = 0;
			deviceId = 70;
			break;
		case 7 :
			id = 121;
			name = "Scenario allumer lumiere 1";
			enabled = true;
			lastUpdated = 0;
			deviceId = 120;
			break;
		case 8 :
			id = 131;
			name = "Scenario allumer lumiere 2";
			enabled = true;
			lastUpdated = 0;
			deviceId = 130;
			break;
		default :
			break;
	}
	
	semMailUTaskHandler.wait();
	mail = mailUTaskHandler.alloc();
	
	mail->taskRequestType = SAVE_INFO;
	mail->taskCfg.taskCfgType = USCENARIO;
	mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
	mail->taskCfg.parentId = deviceId;
	mail->taskCfg.endpoint = NULL;

	scenario = new UScenario(id, name, enabled, lastUpdated, deviceId);
	mail->taskCfg.scenario = scenario;
	mailUTaskHandler.put(mail);
}

void setDefaultTasks(int tasks)
{
	UTaskRequest *mail;
	UTask* task;
			
	int id;	string actionValue; bool enabled; int lastUpdated;
	
	int scenarioId = 0;
	
	switch(tasks) 
	{
		case 0:		
			id = 5;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 4;
			break;
		case 1:		
			id = 6;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 4;
			break;
		case 2:
			id = 22;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 21;
			break;
		case 3:
			id = 23;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 21;
			break;
		case 4:
			id = 32;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 31;
			break;
		case 5:
			id = 33;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 31;
			break;
		case 6:
			id = 42;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 41;
			break;
		case 7:
			id = 43;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 41;
			break;
		case 8:
			id = 52;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 51;
			break;
		case 9:
			id = 53;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 51;
			break;
		case 10:
			id = 62;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 61;
			break;
		case 11:
			id = 63;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 61;
			break;
		case 12:
			id = 72;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 71;
			break;
		case 13:
			id = 73;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 71;
			break;
			
		case 14:
			id = 122;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 121;
			break;
			
		case 15:
			id = 123;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 121;
			break;
			
		case 16:
			id = 124;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 121;
			break;
			
		case 17:
			id = 132;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 131;
			break;
			
		case 18:
			id = 133;
			actionValue = "1";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 131;
			break;
			
		case 19:
			id = 134;
			actionValue = "0";
			enabled = true;
			lastUpdated = 0;
			scenarioId = 131;
			break;
			
		default:
			id = -1;
			actionValue = "0";
			enabled = false;
			lastUpdated = 0;
			break;
	}

	semMailUTaskHandler.wait();
	mail = mailUTaskHandler.alloc();

	mail->taskRequestType = SAVE_INFO;
	mail->taskCfg.taskCfgType = UTASK;
	mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
	mail->taskCfg.parentId = scenarioId;
	mail->taskCfg.endpoint = NULL;

	task = new UTask(id, enabled, lastUpdated, actionValue);
	mail->taskCfg.task = task;
	mailUTaskHandler.put(mail);
}

void setDefaultConditions(int conditions) 
{
	UTaskRequest *mail;
	UCondition* condition;
			
	int id;	UConditionType conditionType; UComparisonType comparisonType;
	int beginValue; int endValue; int deviceId; bool enabled; int lastUpdated;
	int taskId;
	
	
	int deviceIdToCompare = 80;
	int valueToCompare = 28;
	
	switch(conditions)
	{
		case 0:
			id = 7;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 5;
			break;
		case 1:
			id = 8;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 6;
			break;
		case 2:
			id = 24;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 22;
			break;
		case 3:
			id = 25;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 23;
			break;
		case 4:
			id = 34;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 32;
			break;
		case 5:
			id = 35;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 33;
			break;
		case 6:
			id = 44;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 42;
			break;
		case 7:
			id = 45;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 43;
			break;
		case 8:
			id = 54;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 52;
			break;
		case 9:
			id = 55;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 53;
			break;
		case 10:
			id = 64;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 62;
			break;
		case 11:
			id = 65;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 63;
			break;
		case 12:
			id = 74;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = valueToCompare;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 72;
			break;
		case 13:
			id = 75;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = valueToCompare;
			endValue = 0;
			deviceId = deviceIdToCompare;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 73;
			break;
		case 14:
			id = 125;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 100;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 122;
			break;
			
		case 15:
			id = 126;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 110;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 123;
			break;
			
		case 16:
			id = 127;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 100;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 124;
			break;
			
		case 17:
			id = 128;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 110;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 124;
			break;
			
		case 18:
			id = 135;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 100;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 132;
			break;
			
		case 19:
			id = 136;					
			conditionType = DEVICE;
			comparisonType = LESSER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 110;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 133;
			break;
			
		case 20:
			id = 137;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 110;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 134;
			break;
			
		case 21:
			id = 138;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 90;
			endValue = 90;
			deviceId = 100;
			enabled = true;
			lastUpdated = 0;
			
			taskId = 134;
			break;
			
		default:
			id = -1;					
			conditionType = DEVICE;
			comparisonType = GREATER_THAN;
			beginValue = 0;
			endValue = 0;
			deviceId = 0;
			enabled = false;
			lastUpdated = 0;
			
			taskId = 0;
			break;
	} 

	semMailUTaskHandler.wait();
	mail = mailUTaskHandler.alloc();

	mail->taskRequestType = SAVE_INFO;
	mail->taskCfg.taskCfgType = UCONDITION;
	mail->taskCfg.taskCfgMod = TASK_CFG_MOD_NONE;
	mail->taskCfg.parentId = taskId;
	mail->taskCfg.endpoint = NULL;

	condition = new UCondition(id, conditionType, comparisonType, beginValue, endValue, deviceId, enabled, lastUpdated);
	
	mail->taskCfg.condition = condition;
	mailUTaskHandler.put(mail);
}