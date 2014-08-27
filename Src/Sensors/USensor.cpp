#include "USensor.h"

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
USensor::USensor() : analogIn(UPinUtils::analogIn[0])//, m_timer(callback_wrapper, osTimerPeriodic, (void *)s_threadId++)
{
    m_sensorId = 0;
    m_timeBetweenReads = 1000;
}

USensor::USensor(int a_id, int a_pin, int timeBetweenReads)
: analogIn(UPinUtils::analogIn[a_pin])//, m_timer(callback_wrapper, osTimerPeriodic, (void *)s_threadId++)
{
    m_timeBetweenReads = timeBetweenReads;
    m_sensorId = a_id;
}

// Forcefully reads a new value from the sensor, saves it in m_LastValueRead
// and raises the m_NewValueAvailableFlag.
int USensor::ReadValue()
{
	return analogIn.read_u16();
}

// Save the current state of the sensor.
void USensor::SaveState()
{

}

void USensor::Read()
{
	//m_messageHandler->SendMessage("Reading Sensor : ");
	//m_messageHandler->SendMessage(m_sensorName);

	int val = ReadValue();

    // Convert int to str
    char tmp_value[10];
    sprintf(tmp_value,"%d", val);
    char tmp_name[10];
    sprintf(tmp_name,"%d", val);

    char buf[BUFFER_SIZE] = {0};
    strcat(buf, "Captured input from sensor ");
    strcat(buf, tmp_value);
    strcat(buf, ", value : ");
    strcat(buf, tmp_value);
}
