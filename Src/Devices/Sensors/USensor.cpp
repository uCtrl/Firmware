#include "USensor.h"

//uint32_t FakeSensor::s_threadId = 0;

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
USensor::USensor()
: UDevice(),
  analogIn(UPinUtils::analogIn[0]) //, m_timer(callback_wrapper, osTimerPeriodic, (void *)s_threadId++)

{
    m_sensorId = 0;
    m_timeBetweenReads = 1000;
}

USensor::USensor(uint32_t a_id, uint32_t a_pin, uint32_t a_timeBetweenReads, char* a_deviceName)
: UDevice(a_id, a_deviceName),
  analogIn(UPinUtils::analogIn[a_pin]) //, m_timer(callback_wrapper, osTimerPeriodic, (void *)s_threadId++)

{
    m_timeBetweenReads = a_timeBetweenReads;
    m_sensorId = a_id;
}

// Forcefully reads a new value from the sensor, saves it in m_LastValueRead
// and raises the m_NewValueAvailableFlag.
uint32_t USensor::ReadValue()
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

	uint32_t val = ReadValue();

    // Convert uint32_t to str
    char tmp_value[10];
    sprintf(tmp_value,"%lu", val); //%d = int %llu = long unsingned int
    char tmp_name[10];
    sprintf(tmp_name,"%lu", val);

    char buf[BUFFER_SIZE] = {0};
    strcat(buf, "Captured input from sensor ");
    strcat(buf, tmp_value);
    strcat(buf, ", value : ");
    strcat(buf, tmp_value);
}
