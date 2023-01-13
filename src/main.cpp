#include <test.h>
#include <hardwareVerkeerslichten.h>
#include <hw_hulpfunc.h>
#include <hulpfunc.h>
#include <setup.h>
#include <iostream>

//Alle tijden zijn in seconden als floating point nummer

//Tijd die het oranje verkeerstlicht aan blijft
#define ORANJE_LICHT_TIJD 4.0             
//Iemand drukt op een knop -> de hele routine wordt afgehandeld -> de tijd na de afhandeling waarin de drukknoppen genegeerd worden.                   
#define NEGEER_INDRUKKEN_TIJD 5.0                            
//Tijd nadat het oversteeklicht rood is geworden totdat het verkeerslicht groen wordt
#define ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT_TIJD 5.0       
//Tijd tussen: het verkeerslicht gaat op rood (eerst op oranje) en het oversteeklicht op groen (was rood)
#define OVERSTEEKLICHT_ROOD_TIJD 2.0
//Tijd die overstekenden krijgen om over te steken voordat het groene licht gaat knipperen.
#define OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD 15.0               
//Het aantal keren dat het groene oversteeklicht gaat knipperen (een positieve integer)
#define OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL 6                     
//Tijd tussen: groen oversteeklicht aan en groen oversteeklicht uit.
#define OVERSTEEKLICHT_GROEN_KNIPPER_TIJD 0.8             
//Tijd tussen: drukknop gedrukt en oranje verkeerslicht gaat aan = reactietijd op drukken
#define DRUKKEN_EN_ORANJE_VERKEERSLICHT_TIJD 1.5       

/********************************************************************************  
Als iemand drukt wordt de functie handleGedrukt() gestart:
1. Verkeerslicht eerst groen, dan oranje, dan rood. 
2. Overteeklichten eerst rood, rood uit, groen aan, groen knipperen en dan rood weer aan
3. Verkeerslichten weer groen.

De functie handleGedrukt() is klaar als het groene verkeerslicht weer aan gaat. 
Maar je wilt misschien niet dat kinderen steeds weer direct het verkeer willen stoppen door weer te drukken of door de knop steeds ingedrukt te houden.
Daarom is er een pauze van NEGEER_INDRUKKEN_TIJD_SECS seconden, waarin het programma niet reageert op het opnieuw indrukken van de knop. 
********************************************************************************/

void handleOversteekLichten(){        
  // Er is gedrukt, het verkeerslicht staat op rood. Hier verander ik alleen de oversteeklichten 
  // Wordt alleen aangeroepen door handleGedrukt.
  sleepSecs(OVERSTEEKLICHT_ROOD_TIJD); //het verkeerslichten en oversteeklichten staan op rood. Laat de oversteeklichten nog een tijdje op rood staan.
  zetRodeOversteeklichten(UIT);
  zetGroeneOversteeklichten(AAN);
  sleepSecs(OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD);
  //knipperen van het groene oversteeklicht
  for (auto i = 0; i <  OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL; i++) {
    zetGroeneOversteeklichten(UIT);
    sleepSecs(OVERSTEEKLICHT_GROEN_KNIPPER_TIJD);
    zetGroeneOversteeklichten(AAN);
    sleepSecs(OVERSTEEKLICHT_GROEN_KNIPPER_TIJD);
  }
  zetGroeneOversteeklichten(UIT);
  zetRodeOversteeklichten(AAN); 
}

void handleGedrukt() {
  sleepSecs(DRUKKEN_EN_ORANJE_VERKEERSLICHT_TIJD); // na indrukken niet direct reageren, maar eerst even wachten
  zetGroeneVerkeerslichten(UIT);
  zetRodeVerkeerslichten(UIT);
  zetOranjeVerkeerslichten(AAN);
  sleepSecs(ORANJE_LICHT_TIJD);
  zetOranjeVerkeerslichten(UIT);
  zetRodeVerkeerslichten(AAN);          
  // Verkeerstlichten en oversteeklichten rood
  handleOversteekLichten();
  sleepSecs(ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT_TIJD);
  zetRodeVerkeerslichten(UIT);        
  zetGroeneVerkeerslichten(AAN);
  sleepSecs(NEGEER_INDRUKKEN_TIJD); //neem een pauze om 'constant ingedrukt houden' te negeren
}

extern "C" {                //extern "C" => voorkom name mangling door C++
  void app_main() {   
    setup();                // initaliseren poorten en lichten (oversteeklicht op rood en verkeerslicht op groen)
    while (true) {          // the main loop  
      #ifdef TEST_GEDRUKT   // staat in test.h
        //lees alleen maar leesIsGedrukt uit
        bool b = leesIsGedrukt();
        cout << "Gedrukt: " << boolToNlStr(b) << endl << endl;
        sleepSecs(1.0);
      #else 
      if (leesIsGedrukt()) {        
        handleGedrukt();
      }
      #endif      
    }
  } 
}