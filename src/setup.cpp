#include <hardwareVerkeerslichten.h>
#include <hulpfunc.h>
#include <setup.h>
#include <hw_hulpfunc.h>

#define SETUP_TIME_MODE_PINS_SECS   0.5  // wachten op zetten mode pins in de setup
#define SETUP_TIME_ZET_LICHTEN_SECS 0.5  // wachten op zetten lichten in de setup

void setup(){
    //  initialiseren van de richting (input of output) van de poorten
    zetPinOutput(ROOD_VERKEERSLICHT_GPIO);    
    zetPinOutput(ORANJE_VERKEERSLICHT_GPIO);           
    zetPinOutput(GROEN_VERKEERSLICHT_GPIO);            
    zetPinOutput(ROOD_OVERSTEEKLICHT_GPIO);
    zetPinOutput(GROEN_OVERSTEEKLICHT_GPIO);
    zetPinInput(DRUKKNOPPEN_GPIO);
    zetPinPullUp(DRUKKNOPPEN_GPIO);
    sleepSecs(SETUP_TIME_MODE_PINS_SECS); // Wacht even tot de eerste initialisatie klaar is. 
    
    //initialiseer verkeerslichten en oversteeklichten
    zetGroeneOversteeklichten(UIT);
    zetRodeVerkeerslichten(UIT);
    zetOranjeVerkeerslichten(UIT);
    zetGroeneVerkeerslichten(AAN);
    zetRodeOversteeklichten(AAN);
    zetGroeneOversteeklichten(UIT);
    sleepSecs(SETUP_TIME_ZET_LICHTEN_SECS); // Wacht even tot de initialisatie klaar is. 
}