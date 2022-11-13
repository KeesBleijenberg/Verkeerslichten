#include <driver/gpio.h>
#include <iostream>
#include "hardwareVerkeerslichten.h"
#include "hulpfunc.h"

void zetPinOutput(gpio_num_t pin) {
    checkPortAction(pin, gpio_reset_pin(pin), "reset pin");
    checkPortAction(pin, gpio_set_direction(pin, GPIO_MODE_OUTPUT), "set direction of pin");
}

void zetPinInput(gpio_num_t pin) {
    checkPortAction(pin, gpio_reset_pin(pin), "reset pin");
    checkPortAction(pin, gpio_set_direction(pin, GPIO_MODE_INPUT), "set direction of pin");
}

void zetPinPullUp(gpio_num_t pin){
    checkPortAction(pin, gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY), "set internal pull up resistor");
}

void checkPortAction(gpio_num_t pin, esp_err_t err, string errMsg) {
    //Als er geen fout is, dan zet een foutmelding op de serial monitor. 
    if (err != ESP_OK ) {
        if (err == ESP_FAIL){
            std::cout << "algemene fout op poort " << pin << ": " << err << " " << zetHaakjes(errMsg) << "\n";
            return;
        }
        cout << "Fout bij poort " << pin << ": " << esp_err_to_name(err) << " " << zetHaakjes(errMsg) << "\n";
        return;
    }
}



