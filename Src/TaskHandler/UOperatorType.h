/*
 * UOperatorType.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UOPERATORTYPE_H_
#define UOPERATORTYPE_H_

/** UTaskCfgType enum represent the comparison operator to use in each
 *  condition in the task system*/
typedef enum {
	OPERATOR_TYPE_NONE = 0,
	EQUAL = 1,
	GREATER_EQUAL = 2,
	GREATER = 3,
	LESSER = 4,
	LESSER_EQUAL = 5,
	NOT_EQUAL = 6
} UOperatorType;

#endif /* UOPERATORTYPE_H_ */
