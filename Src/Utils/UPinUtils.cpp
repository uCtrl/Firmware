#include "UPinUtils.h"

/*
// The duplication of led1 is to ensure that p5 is at the 5th position in the array.
const PinName UPinUtils::pins[] = { LED1, LED1, LED2, LED3, LED4 };
                                    p5,  p6,  p7,  p8,  p9,  p10,
                                    p11, p12, p13, p14, p15, p16,
                                    p17, p18, p19, p20, p21, p22,
                                    p23, p24, p25, p26, p27, p28,
                                    p29, p30 };*/

#ifdef TARGET_K64F
//const PinName UPinUtils::analogIn[] = { PTC2, PTB3, PTB2, PTB1, PTB0};
//const PinName UPinUtils::analogOut[] = { PTE30};
//const PinName UPinUtils::digitalInOut[] = { LED1, LED2, LED3 };
#endif

#ifdef TARGET_LPC1768
// p15, p16, p17, p18, p19, p20
const PinName UPinUtils::analogIn[] = { P0_23, P0_24, P0_25, P0_26, P1_30, P1_31 };

// p18
const PinName UPinUtils::analogOut[] = { P0_26 };

// Leds + p5-p30

// Note :
// LED1 = P1_18
// LED2 = P1_20
// LED3 = P1_21
// LED4 = P1_23

const PinName UPinUtils::digitalInOut[] = { P1_18, P1_20, P1_21, P1_23,
											P0_9, P0_8, P0_7, P0_6 }; // Can be completed if needed
#endif


#ifdef TARGET_KL25Z
const PinName UPinUtils::analogIn[] = { PTC2, PTB3, PTB2, PTB1, PTB0};
const PinName UPinUtils::analogOut[] = { PTE30};
const PinName UPinUtils::digitalInOut[] = { LED1, LED2, LED3 };
#endif
