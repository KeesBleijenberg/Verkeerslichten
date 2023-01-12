#include <test.h>
#include <hardwareVerkeerslichten.h>
#include <hw_hulpfunc.h>
#include <hulpfunc.h>
#include <setup.h>
#include <iostream>

#define ORANJE_LICHT_TIJD_SECS 4.0                          //Tijd die het oranje verkeerstlicht aan blijft
#define NEGEER_INDRUKKEN_TIJD_SECS 5.0                      //Iemand drukt op een knop -> de hele routine wordt afgehandeld -> de tijd na de afhandeling waarin de drukknoppen genegeerd worden.
#define ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT 4.0          //Tijd nadat het oversteeklicht rood is geworden totdat het verkeerslicht groen wordt
#define ROOD_VERKEERSLICHT_TOT_GROEN_OVERSTEEKLICHT 3.0     //Tijd tussen: het verkeerslicht gaat op rood (eerst op oranje) en het oversteeklicht op groen (was rood)
#define OVERSTEEKLICHT_ROOD_TIJD_SEC 1.5                    //Tijd tussen: het oversteeklicht staat op rood en het oversteeklicht staat op groen
#define OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD_SEC 10.0         //Tijd die overstekenden krijgen om over te steken voordat het groene licht gaat knipperen.
#define OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL 6               //Het aantal keren dat het groene oversteeklicht gaat knipperen (een positieve integer)
#define OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC 0.8       //Tijd tussen: groen oversteeklicht aan en groen oversteeklicht uit.
#define TIJD_TUSSEN_DRUKKEN_EN_ORANJE_VERKEERSLICHT_SEC 1.5 //Tijd tussen: drukknop ingedrukt en oranje verkeerslicht gaat aan

/*  Als iemand drukt wordt de functie handleGedrukt() gestart:
    - Verkeerslicht eerst groend, dan oranje, dan rood. 
    - Overteeklichten eerst rood, rood uit, groen aan, groen knipperen en dan rood weer aan
    - Verkeerslichten weer groen.

    handleGedrukt()is klaar als het groene verkeerslicht weer aan gaat. 
    Maar je wilt misschien niet dat kinderen steeds weer direct het verkeer wilt stoppen door weer te drukken.
    Daarom is er een pauze van NEGEER_INDRUKKEN_TIJD_SECS seconden, 
    waarin het programma niet reageert op het indrukken van een knop nadat handleGedrukt() net klaar is. 
*/

void handleOversteekLichten(){        
  // Er is gedrukt, het verkeerslicht staat op rood. Hier verander ik alleen de oversteeklichten
  // 
  sleepSecs(OVERSTEEKLICHT_ROOD_TIJD_SEC);
  zetRodeOversteeklichten(UIT);
  zetGroeneOversteeklichten(AAN);
  sleepSecs(OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD_SEC);
  //knipperen van het groene oversteeklicht
  for (auto i = 0; i <  OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL; i++) {
    zetGroeneOversteeklichten(UIT);
    sleepSecs(OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC);
    zetGroeneOversteeklichten(AAN);
    sleepSecs(OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC);
  }
  zetGroeneOversteeklichten(UIT);
  zetRodeOversteeklichten(AAN); 
}

void handleGedrukt() {
  sleepSecs(TIJD_TUSSEN_DRUKKEN_EN_ORANJE_VERKEERSLICHT_SEC);
  zetGroeneVerkeerslichten(UIT);
  zetRodeVerkeerslichten(UIT);
  zetOranjeVerkeerslichten(AAN);
  sleepSecs(ORANJE_LICHT_TIJD_SECS);
  zetOranjeVerkeerslichten(UIT);
  zetRodeVerkeerslichten(AAN);          
  // Verkeerstlichten: rood aan, oranje uit en groen uit. Oversteeklichten: rood aan, groen uit.
  // Zet nu de oversteeklichten
  sleepSecs(ROOD_VERKEERSLICHT_TOT_GROEN_OVERSTEEKLICHT);
  handleOversteekLichten();
  sleepSecs(ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT);
  zetRodeVerkeerslichten(UIT);        
  zetGroeneVerkeerslichten(AAN);
  sleepSecs(NEGEER_INDRUKKEN_TIJD_SECS); //neem een pauze om 'constant ingedrukt houden' te voorkomen        
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