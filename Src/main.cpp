#include "mbed.h"
#include "rtos.h"
#include "UController.h"
#include "UComDriver.h"
#include "FakeMessageHandler.h"

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

void fakeMessageHandlerThread(void const *args) {
	FakeMessageHandler::GetInstance()->start();
}

int main (void) {
    //Thread ctrlThread(controllerThread);
    //Thread comThread(comDriverThread);
    Thread fakeMsgThread(fakeMessageHandlerThread);
    //    osEvent evt;
    while (true)
    {
    	FakeMessageHandler::GetInstance()->SendMessage("Will not block after this - From main");
    	Thread::wait(700);

    	/*evt = mail_box.get();
		if (evt.status == osEventMail) {
			UController *mail = (UController*)evt.value.p;
			//mail->start();

			mail_box.free(mail);
		}
    	Thread::wait(700);
    	//led = !led;
        Thread::wait(200);
        led = !led;
        Thread::wait(200);
        led = !led;
        Thread::wait(200);
        //led = !led;
        Thread::wait(700);*/
    }
}
