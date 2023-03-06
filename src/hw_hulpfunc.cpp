#include <test.h>  
#include <iostream>
#include <driver/gpio.h>
#include <hardwareVerkeerslichten.h>
#include <hw_hulpfunc.h>
#include <hulpfunc.h>

void zetRodeVerkeerslichten(int aanUit) {
    // Zet het rood verkeerslicht aan of uit     
    gpio_set_level( ROOD_VERKEERSLICHT_GPIO , aanUit);
    wachtenOpLamp(aanUit);
}
  
void zetGroeneVerkeerslichten(int aanUit) {
      //zet het groene verkeerslicht aan of uit
    gpio_set_level(GROEN_VERKEERSLICHT_GPIO, aanUit);    
    wachtenOpLamp(aanUit);
}

void zetOranjeVerkeerslichten(int aanUit) {
    //zet het oranje verkeerslicht aan of uit
    gpio_set_level(ORANJE_VERKEERSLICHT_GPIO, aanUit);    
    wachtenOpLamp(aanUit);
}

void zetRodeOversteeklichten(int aanUit){
    //zet het rode oversteeklicht aan of uit
    gpio_set_level(ROOD_OVERSTEEKLICHT_GPIO, aanUit);    
    wachtenOpLamp(aanUit);    
} 

void zetGroeneOversteeklichten(int aanUit){
    // Ook het groene oversteeklicht is ook normally open
    gpio_set_level(GROEN_OVERSTEEKLICHT_GPIO , aanUit);
    wachtenOpLamp(aanUit);
} 

int  invertLevel(int hardwareLevel){
    if (hardwareLevel == UIT){
        return AAN;
    }
    return UIT;
}    

bool leesIsGedrukt() {
    //lees of de knop is gedrukt en retun het resultaat
    //lees daarvoor de binaire waarde van de poort DRUKKNOPPEN_GPIO en inverteer dan het gevonden level
    //poortGedrukt is een hardware status. gpio is hoog => niet gedrukt, gpio is laag => gedrukt (geinverteerd dus)    
    int poortGedrukt = invertLevel(gpio_get_level(DRUKKNOPPEN_GPIO)); 
    
    #ifdef TEST_GEDRUKT 
    cout << "De waarde van de gedrukt poort is: " << poortGedruktLevel << endl;
    #endif

    if ((poortGedrukt == AAN) && (GEDRUKT_DEBOUNCE_COUNT >=1)) {
        for (int i=1; i < GEDRUKT_DEBOUNCE_COUNT; i++){
            sleepSecs(GEDRUKT_DEBOUNCE_WACHTTIJD_SEC);
            poortGedrukt = invertLevel(gpio_get_level(DRUKKNOPPEN_GPIO));
            // hier nog even geen debug output (gaat te langzaam?)
            if (poortGedrukt == UIT) {
                // hardware matig is er niet gedrukt. Breek af en return false
                return false;                
            } 
        }
    }
    return poortGedrukt == AAN; 
}