#include "servo.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"

static uint servo_gpio;
static uint slice_num;

void servo_init(uint gpio)
{
    servo_gpio = gpio;

    // Configura o GPIO para PWM
    gpio_set_function(servo_gpio, GPIO_FUNC_PWM);

    // Descobre o slice do PWM
    slice_num = pwm_gpio_to_slice_num(servo_gpio);

    // Configuração padrão
    pwm_config config = pwm_get_default_config();

    // Clock: 125 MHz / 125 = 1 MHz
    pwm_config_set_clkdiv(&config, 125.0f);

    // Período: 20 ms (50 Hz)
    pwm_config_set_wrap(&config, 19999);

    pwm_init(slice_num, &config, true);

    // Centraliza o servo
    servo_set_angle(90.0f);
}

void servo_set_angle(float angle)
{
    if(angle < 0)
        angle = 0;

    if(angle > 180)
        angle = 180;

    // Converte ângulo para pulso (1000–2000 µs)
    uint16_t pulse = 1000 + (angle * 1000.0f / 180.0f);

    pwm_set_gpio_level(servo_gpio, pulse);
}