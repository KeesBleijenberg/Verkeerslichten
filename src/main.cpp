#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <stdio.h>
#include <cmath>
#include <driver/gpio.h>

#define UIT     0
#define AAN    1

#define SETUP_TIME_MODE_PINS_SECS 0.5  // wachten op zetten mode pins in de setup
#define SETUP_TIME_ZET_LICHTEN_SECS 0.5  // wachten op zetten lichten in de setup

#define PAUZE_NA_AFHANDELING_GEDRUKT_SECS 5.0
#define ORANJE_LICHT_TIJD_SECS 3.0        // de tijd die het oranje verkeerstlicht aan blijft
#define NEGEER_INDRUKKEN_TIJD_SECS 5.0              // iemand drukt op een knop -> de hele routine wordt afgehandeld -> de tijd na de afhandeling waarin de drukknoppen genegeerd worden.
#define ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT 4.0 //Tijd nadat het oversteeklicht rood is geworden totdat het verkeerslicht groen wordt
#define ROOD_TOT_GROEN_OVERSTEEKLICHT 3.0 //Tijd nadat het verkeerslicht op rood gaat totdat het oversteeklicht groen wordt
#define OVERSTEEKLICHT_ROOD_TIJD_SEC 0.5  // de tijd die het oversteeklicht nog op rood blijft staan.
#define OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD_SEC 10.0 // de tijd die overstekenden krijgen om over te steken voordat het groene licht gaat knipperen.
#define OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL 5  // het aantal keren dat het groene oversteeklicht gaat knipperen (een positieve int)
#define OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC 1.0  // de tijd tussen groen oversteeklicht aan en groen oversteeklicht uit.

//definieren van de pins. 
#define ROOD_LICHT_GPIO             GPIO_NUM_33 
#define ORANJE_LICHT_GPIO           GPIO_NUM_32 
#define GROEN_LICHT_GPIO            GPIO_NUM_13 
#define ROOD_OVERSTEEK_LICHT_GPIO   GPIO_NUM_12 
#define GROEN_OVERSTEEK_LICHT_GPIO  GPIO_NUM_21 

#define DRUKKNOPPEN_GPIO            GPIO_NUM_22 

extern "C" {

  /*  Als iemand drukt wordt er een programma gestart. 
      oranje, rood, oversteeklichten aan, groen aan, rood uit
      Dit programma is helemaal af als rood uit gaat. 
      Je wilt misschien niet dat iemand direct weer het verkeer wilt stoppen.
      Daarom een pauze waarin het systeem niet reageert op het indrukken van een knop
  */

  void sleepInSecs (const double secs) {
    //laat de computer secs seconden wachten    
    vTaskDelay(round ((secs * 1000)/ portTICK_PERIOD_MS));
  }

  void zetPinOutput(gpio_num_t pin) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
  }

  void zetPinInput(gpio_num_t pin) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
  }
 
  int invertLevel(int level) {
    return level; //nu nog even niet inverten. Inverten is nodig voor normally open relays.
      if (level == AAN) {
        return UIT;
      }
      else {
        return AAN;
      }
    
  }  

  void zetRodeLichten(int aanUit) {
    /* Zet het rode licht aan of uit
       Rood staat hardwarmatig op 'normal closed'. Dit betekent:
       - Als er geen stroom op het bordje staat of het inputsignaal laag is, is het relais dicht is en dus gaat het rood licht aan.
       - Signaal hoog betekent dat het relais onderbreekt de output.
    */    
    gpio_set_level( ROOD_LICHT_GPIO , invertLevel(aanUit));
  }
  
  void zetGroeneLichten(int aanUit) {
      //zet het groen licht aan of uit
    gpio_set_level(GROEN_LICHT_GPIO, aanUit);    
  }

  void zetOranjeLichten(const int aanUit) {
      //zet het oranje licht aan of uit
    gpio_set_level(ORANJE_LICHT_GPIO, aanUit);    
  }

  void zetRodeOversteeklichten(int aanUit){
    gpio_set_level(ROOD_OVERSTEEK_LICHT_GPIO, aanUit);    
  } 

  void zetGroeneOversteeklichten(int aanUit){
    // Ook het groene oversteeklicht is ook normally open
    gpio_set_level(GROEN_OVERSTEEK_LICHT_GPIO , invertLevel(aanUit));
  } 

  bool leesIsGedrukt() {
    //lees of knop is gedrukt en stelt de waarde van globale variabele gedrukt bij
    int levelGedrukt = gpio_get_level(DRUKKNOPPEN_GPIO);
    return levelGedrukt == AAN; //voor vorlopig altijd gedrukt
  }

  void handleOversteekLichten() {        
    // Er is gedrukt, het verkeerslicht staat op rood. Hier verander ik alleen de oversteeklichten
    sleepInSecs(OVERSTEEKLICHT_ROOD_TIJD_SEC);
    zetRodeOversteeklichten(UIT);
    zetGroeneOversteeklichten(AAN);
    sleepInSecs(OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD_SEC);
    //knipperen van het groene oversteeklicht
    for (int i = 0; i <  OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL; i++) {
      zetGroeneOversteeklichten(UIT);
      sleepInSecs(OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC);
      zetGroeneOversteeklichten(AAN);
      sleepInSecs(OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC);
    }
    zetGroeneOversteeklichten(UIT);
    zetRodeOversteeklichten(AAN); 
  }
  
  void setup(){
    //  initialiseren van de richting (input of output) van de poorten
    zetPinOutput(ROOD_LICHT_GPIO);    
    zetPinOutput(ORANJE_LICHT_GPIO);           
    zetPinOutput(GROEN_LICHT_GPIO);            
    zetPinOutput(ROOD_OVERSTEEK_LICHT_GPIO);
    zetPinOutput(GROEN_OVERSTEEK_LICHT_GPIO);
    zetPinInput(DRUKKNOPPEN_GPIO);
    sleepInSecs(SETUP_TIME_MODE_PINS_SECS); // Wacht even totdat alles de eerste initialisatie klaar is. 
    
    //initialiseer lichten
    zetGroeneOversteeklichten(UIT);
    zetRodeLichten(UIT);
    zetOranjeLichten(UIT);
    zetGroeneLichten(AAN);
    zetRodeOversteeklichten(AAN);
    zetGroeneOversteeklichten(UIT);
    sleepInSecs(SETUP_TIME_ZET_LICHTEN_SECS); // Wacht even totdat alles de initialisatie klaar is. 
  }

  // the main loop
  void app_main() {    
    setup(); //initaliseren poorten    
    while (true) {      
      if (leesIsGedrukt()) {        
        zetGroeneLichten(UIT);
        zetRodeLichten(UIT);
        zetOranjeLichten(AAN);
        sleepInSecs(ORANJE_LICHT_TIJD_SECS);
        zetOranjeLichten(UIT);
        zetRodeLichten(AAN);          
        //rood verkeerstlicht is aan. Oranje en groen zijn uit. Zet nu de oversteeklichten
        sleepInSecs(ROOD_TOT_GROEN_OVERSTEEKLICHT);
        handleOversteekLichten();
        sleepInSecs(ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT);
        zetRodeLichten(UIT);        
        zetGroeneLichten(AAN);
        sleepInSecs(NEGEER_INDRUKKEN_TIJD_SECS); //neem een pauze om 'constant ingedrukt houden' te voorkomen        
      }
    }
  }
}


