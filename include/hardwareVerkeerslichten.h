#include <driver/gpio.h>
#include <string>

using namespace std;


#ifndef PORTS_VERKEERSLICHTEN_H  //voorkom dubbel include
    #define PORTS_VERKEERSLICHTEN_H //Nog geen PORTS_VERKEERSLICHTEN => definieer PORTS_VERKEERSLICHTEN alsnog.

    #define UIT    0
    #define AAN    1
    
    //definieren van de pins. 
    #define ROOD_VERKEERSLICHT_GPIO     GPIO_NUM_33 
    #define ORANJE_VERKEERSLICHT_GPIO   GPIO_NUM_32 
    #define GROEN_VERKEERSLICHT_GPIO    GPIO_NUM_13 
    #define ROOD_OVERSTEEKLICHT_GPIO    GPIO_NUM_12 
    #define GROEN_OVERSTEEKLICHT_GPIO   GPIO_NUM_21 
    #define DRUKKNOPPEN_GPIO            GPIO_NUM_22 

    void zetPinOutput(gpio_num_t pin);
    void zetPinInput(gpio_num_t pin); 
    void zetPinPullUp(gpio_num_t pin);
    void checkPortAction(gpio_num_t pin, esp_err_t err, string errMsg);
#endif
