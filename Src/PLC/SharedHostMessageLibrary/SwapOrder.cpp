#include "TLV_Messages.h"

union UInt16_Swap
{
	UINT16 _Data;
	BYTE _DataArray[2];
};

union Int32_Swap
{
	INT32 _Data;
	BYTE _DataArray[4];
};

union Int16_Swap
{
	INT16 _Data;
	BYTE _DataArray[2];
};

union UInt32_Swap
{
	UINT32 _Data;
	BYTE _DataArray[4];
};

UINT16 SwapOrder_UInt16(UINT16 data)
{
	union UInt16_Swap one;
	union UInt16_Swap two;

	one._Data = data;
	two._DataArray[0] = one._DataArray[1];
	two._DataArray[1] = one._DataArray[0];

	return two._Data;
}
/*
INT16 SwapOrder_Int16(INT16 data)
{
	union Int16_Swap one;
	union Int16_Swap two;

	one._Data = data;
	two._DataArray[0] = one._DataArray[1];
	two._DataArray[1] = one._DataArray[0];

	return two._Data;
}


INT32 SwapOrder_Int32(INT32 data)
{
	union Int32_Swap one;
	union Int32_Swap two;

	one._Data = data;
	two._DataArray[0] = one._DataArray[3];
	two._DataArray[1] = one._DataArray[2];
	two._DataArray[2] = one._DataArray[1];
	two._DataArray[3] = one._DataArray[0];

	return two._Data;
}
*/
UINT32 SwapOrder_UInt32(UINT32 data)
{
	union UInt32_Swap one;
	union UInt32_Swap two;

	one._Data = data;
	two._DataArray[0] = one._DataArray[3];
	two._DataArray[1] = one._DataArray[2];
	two._DataArray[2] = one._DataArray[1];
	two._DataArray[3] = one._DataArray[0];

	return two._Data;
}

void SwapOrder_UINT16_TLV(struct TLV_UINT16 * tlv)
{
	tlv->_TLV._Type = SwapOrder_UInt16(tlv->_TLV._Type);
	tlv->_TLV._Length = SwapOrder_UInt16(tlv->_TLV._Length);

	tlv->_UINT16 = SwapOrder_UInt16(tlv->_UINT16);
}

void SwapOrder_UINT32_TLV(struct TLV_UINT32 * tlv)
{
	tlv->_TLV._Type = SwapOrder_UInt16(tlv->_TLV._Type);
	tlv->_TLV._Length = SwapOrder_UInt16(tlv->_TLV._Length);

	tlv->_UINT32 = SwapOrder_UInt32(tlv->_UINT32);
}

UINT32 SwapInLine(BYTE * pointer, int size)
{
	UINT32 value;
	BYTE temp;
	temp = pointer[0];
	if (size == 2)
	{
		pointer[0] = pointer[1];
		pointer[1] = temp;
	}
	else
	{
		temp = pointer[0];
		pointer[0]= pointer[3];
		pointer[3] = temp;

		temp = pointer[1];
		pointer[1] = pointer[2];
		pointer[2] = temp;
	}
	value = 0;
	memcpy(&value, pointer, size);
	return value;
}
