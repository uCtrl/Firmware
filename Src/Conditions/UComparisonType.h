/*
 * UOperatorType.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UCOMPARISONTYPE_H_
#define UCOMPARISONTYPE_H_

/** UTaskCfgType enum represent the comparison operator to use in each
 *  condition in the task system*/
typedef enum
{
	NONE = 0,
	GREATER_THAN = 1,
	LESSER_THAN = 2,
	EQUAL = 4,
	IN_BETWEEN = 8,
	NOT = 16,
	NOT_GREATER_THAN = 17,
	NOT_LESSER_THAN = 18,
	NOT_EQUAL = 20,
	NOT_IN_BETWEEN = 24
} UComparisonType;

#endif /* UCOMPARISONTYPE_H_ */

