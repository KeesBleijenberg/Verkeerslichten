#include <driver/gpio.h>

#ifndef PORTS_VERKEERSLICHTEN  //voorkom dubbel include
    #define UIT    0
    #define AAN    1
    #define PORTS_VERKEERSLICHTEN
    //definieren van de pins. 
    #define ROOD_VERKEERSLICHT_GPIO     GPIO_NUM_33 
    #define ORANJE_VERKEERSLICHT_GPIO   GPIO_NUM_32 
    #define GROEN_VERKEERSLICHT_GPIO    GPIO_NUM_13 
    #define ROOD_OVERSTEEKLICHT_GPIO   GPIO_NUM_12 
    #define GROEN_OVERSTEEKLICHT_GPIO  GPIO_NUM_21 
    #define DRUKKNOPPEN_GPIO            GPIO_NUM_22 

    void zetPinOutput(gpio_num_t pin);
    void zetPinInput(gpio_num_t pin); 
#endif
