#include "mbed.h"
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
#include <cstdio>
#include <array>
float read_temperature()
{
float const voltage = (adc_read(0) / 65535.0f) * 3.0f;
return (voltage * 1000 - 400) / 19.5f;
}
void init_display()
{
board_init();
u8g2_ClearBuffer(&oled);
u8g2_SetFont(&oled, u8g2_font_6x12_mr);
u8g2_SendBuffer(&oled);
}
void display_message(char const *message)
{
u8g2_ClearBuffer(&oled);
u8g2_DrawUTF8(&oled, 10, 10, message);
u8g2_SendBuffer(&oled);
}
void display_temperature(float temp)
{
std::array<char, 50> msg {};
// workaround because %f format specifier is not supported
int const ti = static_cast<int>(temp);
int const tf = abs(static_cast<int>(100 * temp) % 100);
std::snprintf(msg.data(), msg.size(), "Temperature is %d.%02d C", ti, tf);
display_message(msg.data());
}
int main()
{
init_display();
DigitalOut led_green {PTB3};
DigitalOut led_red {PTC12};
PwmOut heater_power {PTA7};
while (true)
{
float const temp = read_temperature();
constexpr float SENSOR_CUTOFF = -10.0f;
bool const has_sensor = temp >= SENSOR_CUTOFF;
constexpr float TEMP_MIN = 30.0f;
constexpr float TEMP_MAX = 35.0f;
led_green = has_sensor && temp >= TEMP_MIN && temp <= TEMP_MAX;
constexpr float TEMP_TARGET = 32.5f;
heater_power = has_sensor && temp < TEMP_TARGET;
led_red = heater_power;
if (has_sensor) display_temperature(temp);
else display_message("No temperature sensor connected!");
ThisThread::sleep_for(100ms);
}
}
Tests