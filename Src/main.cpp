#include "mbed.h"
#include "rtos.h"
#include "UController.h"
#include "UComDriver.h"

DigitalOut led(LED_RED);
//Mail<struc,3> mail_box;

void controllerThread(void const *args) {
	UController uController;
	uController.start();
}

void comDriverThread(void const *args) {
	UComDriver uComDriver;
	uComDriver.start();
}

int main (void) {
    Thread ctrlThread(controllerThread);
    Thread comThread(comDriverThread);
    //    osEvent evt;
    while (true)
    {
    	/*evt = mail_box.get();
		if (evt.status == osEventMail) {
			UController *mail = (UController*)evt.value.p;
			//mail->start();

			mail_box.free(mail);
		}*/
    	Thread::wait(700);
    	//led = !led;
        Thread::wait(200);
        led = !led;
        Thread::wait(200);
        led = !led;
        Thread::wait(200);
        //led = !led;
        Thread::wait(700);
    }
}
