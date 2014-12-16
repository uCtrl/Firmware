/*
 * UTaskRequestType.h
 *
 *  Created on: Apr 4, 2014
 *      Author: uctrl
 */

#ifndef UTASKREQUESTTYPE_H_
#define UTASKREQUESTTYPE_H_

typedef enum
{
	TASKREQUEST_TYPE_NONE = 0,
	DELETE = 1,
	EVENT = 2,
	GET_INFO = 3,
	SAVE_INFO = 4,
} UTaskRequestType;


#endif /* UTASKREQUESTTYPE_H_ */

