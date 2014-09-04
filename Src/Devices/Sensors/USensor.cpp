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
USensor::USensor()
: UDevice(),
  analogIn(UPinUtils::analogIn[0])

{
    m_sensorId = 0;
    m_timeBetweenReads = 1000;
}

USensor::USensor(int a_id, int a_pin, int a_timeBetweenReads, char* a_deviceName)
: UDevice(a_id, a_deviceName),
  analogIn(UPinUtils::analogIn[a_pin])

{
    m_timeBetweenReads = a_timeBetweenReads;
    m_sensorId = a_id;
}


// Destructor
USensor::~USensor()
{

}

// Read a new value from the sensor,
int USensor::ReadValue()
{
	return analogIn.read_u16();
}

void USensor::Read()
{
	// To be implemented
}
