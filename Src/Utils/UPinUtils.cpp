#include "UPinUtils.h"

/*
// The duplication of led1 is to ensure that p5 is at the 5th position in the array.
const PinName UPinUtils::pins[] = { LED1, LED1, LED2, LED3, LED4 };
                                    p5,  p6,  p7,  p8,  p9,  p10,
                                    p11, p12, p13, p14, p15, p16,
                                    p17, p18, p19, p20, p21, p22,
                                    p23, p24, p25, p26, p27, p28,
                                    p29, p30 };*/

const PinName UPinUtils::analogIn[] = {PTC2, PTB3, PTB2, PTB1, PTB0};
const PinName UPinUtils::analogOut[] = {PTE30};
const PinName UPinUtils::digitalInOut[] = { LED1, LED2, LED3 };
