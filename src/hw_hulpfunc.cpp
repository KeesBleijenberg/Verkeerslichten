#include <test.h>  
#include <iostream>
#include <driver/gpio.h>
#include <hardwareVerkeerslichten.h>
  


void zetRodeLichten(int aanUit) {
    /* Zet het rood licht van verkeerslichten aan of uit       
    */    
    gpio_set_level( ROOD_VERKEERSLICHT_GPIO , aanUit);
}
  
void zetGroeneLichten(int aanUit) {
      //zet het groen licht aan of uit
    gpio_set_level(GROEN_VERKEERSLICHT_GPIO, aanUit);    
}

void zetOranjeLichten(const int aanUit) {
      //zet het oranje licht aan of uit
    gpio_set_level(ORANJE_VERKEERSLICHT_GPIO, aanUit);    
}

void zetRodeOversteeklichten(int aanUit){
    gpio_set_level(ROOD_OVERSTEEKLICHT_GPIO, aanUit);    
} 

void zetGroeneOversteeklichten(int aanUit){
    // Ook het groene oversteeklicht is ook normally open
    gpio_set_level(GROEN_OVERSTEEKLICHT_GPIO , aanUit);
} 

bool leesIsGedrukt() {
    //lees of de knop is gedrukt en stelt de waarde van globale variabele gedrukt bij
    //lees het level van de poort DRUKKNOPPEN_GPIO
    int poortGedruktLevel = gpio_get_level(DRUKKNOPPEN_GPIO);
    // gpio is hoog => niet gedrukt, gpio is laag => gedrukt (geinverteerd dus)    
    #ifdef TEST_GEDRUKT 
    cout << "De waarde van de gedrukt poort is: " << poortGedruktLevel << endl;
    #endif
    return poortGedruktLevel == UIT; 
}