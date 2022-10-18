#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>  
#include <driver/gpio.h>
#include <cmath>
#include <hardwareVerkeerslichten.h>
  
void sleepInSecs (const double secs) {
    //laat de computer secs seconden wachten    
    vTaskDelay(round ((secs * 1000)/ portTICK_PERIOD_MS));
}


int invertLevel(int level) {
  return level; //nu nog even niet inverten. Inverten is nodig voor normally open relays.
  /*
    if (level == AAN) {
      return UIT;
    }
    else {
      return AAN;
    }    
  */
}  

void zetRodeLichten(int aanUit) {
    /* Zet het rood licht van verkeerslichten aan of uit       
    */    
    gpio_set_level( ROOD_VERKEERSLICHT_GPIO , invertLevel(aanUit));
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
    gpio_set_level(GROEN_OVERSTEEKLICHT_GPIO , invertLevel(aanUit));
} 

bool leesIsGedrukt() {
    //lees of knop is gedrukt en stelt de waarde van globale variabele gedrukt bij
    int levelGedrukt = gpio_get_level(DRUKKNOPPEN_GPIO);
    return levelGedrukt == AAN; //voor vorlopig altijd gedrukt
}
