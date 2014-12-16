/*
 * DeviceType.h
 *
 *  Created on: Oct 19, 2014
 *      Author: uctrl
 */

#ifndef DEVICETYPE_H_
#define DEVICETYPE_H_

enum UDeviceType
{
	Undefined = 0,
	Actuator_Switch = 1,
	Actuator_RGB = 10002,
	Actuator_LedsFlow = 10001,
	Sensor_Light = 10000,
	Sensor_Temperature = 31,
	Sensor_Motion = 7
};

#endif /* DEVICETYPE_H_ */

