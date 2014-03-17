#include "mbed.h"
#include "rtos.h"

Queue<uint32_t, 5> queue;

DigitalOut gpo(PTB8);
DigitalOut myled(LED_RED);
PwmOut myled2(LED_GREEN);

void queue_isr() {
    queue.put((uint32_t*)2);
    myled = !myled;
}

void queue_isr2() {
    queue.put((uint32_t*)2);
    myled2 = !myled2;
}

void queue_thread(void const *args) {
    while (true) {
        queue.put((uint32_t*)1);
        Thread::wait(1000);
    }
}

int main (void) {
    Thread thread(queue_thread);

    Ticker ticker;
    //Ticker ticker2;
    ticker.attach(queue_isr, 1.0);
    //ticker2.attach(queue_isr2, 3.0);

    while (true) {
        osEvent evt = queue.get();
        if (evt.status != osEventMessage) {
            printf("queue->get() returned %02x status\n\r", evt.status);
        } else {
            printf("queue->get() returned %d\n\r", evt.value.v);
        }
    }
}
