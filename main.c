#include <stdio.h>

#include "pico/stdlib.h"

#include "servo.h"

int main()
{
    stdio_init_all();

    servo_init(15);

    while(true)
    {
        servo_set_angle(0);
        sleep_ms(1000);

        servo_set_angle(45);
        sleep_ms(1000);

        servo_set_angle(90);
        sleep_ms(1000);

        servo_set_angle(135);
        sleep_ms(1000);

        servo_set_angle(180);
        sleep_ms(1000);
    }
}