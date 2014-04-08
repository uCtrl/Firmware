#include "FakeSensor.h"

//int FakeSensor::s_threadId = 0;

/*
// See : http://stackoverflow.com/questions/4126616/c-to-c-call-argument-of-type-void-myclassu-char-does-not-match-voi
extern "C"
{
   void callback_wrapper(void const *arg) {
	  void *arg2 = (void*) arg;
	  static_cast<FakeSensor*>(arg2)->Read();
   }
}*/

// Constructor
FakeSensor::FakeSensor() : analogIn(UPinUtils::analogIn[0])//, m_timer(callback_wrapper, osTimerPeriodic, (void *)s_threadId++)
{
    m_sensorName = NULL;
    m_messageHandler = NULL;
    m_timeBetweenReads = 1000;
}

FakeSensor::FakeSensor(FakeMessageHandler* messageHandler, char* a_name, int a_pin, int timeBetweenReads)
: analogIn(UPinUtils::analogIn[a_pin])//, m_timer(callback_wrapper, osTimerPeriodic, (void *)s_threadId++)
{
    m_timeBetweenReads = timeBetweenReads;
    m_sensorName = a_name;
    m_messageHandler = messageHandler;
    //ticker.attach(this, &FakeSensor::Read, 5.0);
    //m_timer.start(timeBetweenReads);
}

// Forcefully reads a new value from the sensor, saves it in m_LastValueRead
// and raises the m_NewValueAvailableFlag.
int FakeSensor::ReadValue()
{
	return analogIn.read_u16();
}

// Save the current state of the sensor.
void FakeSensor::SaveState()
{

}

void FakeSensor::Read()
{
	//printf("test\n\r");

	int val = ReadValue();

	/*
    // Convert int to str
    char tmp[10];
    sprintf(tmp,"%d", val);

    char buf[BUFFER_SIZE] = {0};
    strcat(buf,"Captured input from sensor ");
    strcat(buf, m_sensorName);
    strcat(buf,", value : ");
    strcat(buf,tmp);
	m_messageHandler->SendMessage(buf);//*/

	//m_messageHandler->ReadValueFromSensor(m_sensorName, val);
}
