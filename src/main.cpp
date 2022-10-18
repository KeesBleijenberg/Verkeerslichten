#include <hardwareVerkeerslichten.h>
#include <hulpfunc.h>
#include <setup.h>

#define PAUZE_NA_AFHANDELING_GEDRUKT_SECS 5.0
#define ORANJE_LICHT_TIJD_SECS 3.0        // de tijd die het oranje verkeerstlicht aan blijft
#define NEGEER_INDRUKKEN_TIJD_SECS 5.0              // iemand drukt op een knop -> de hele routine wordt afgehandeld -> de tijd na de afhandeling waarin de drukknoppen genegeerd worden.
#define ROOD_OVERSTEEK_TOT_GROEN_VERKEERSLICHT 4.0 //Tijd nadat het oversteeklicht rood is geworden totdat het verkeerslicht groen wordt
#define ROOD_TOT_GROEN_OVERSTEEKLICHT 3.0 //Tijd nadat het verkeerslicht op rood gaat totdat het oversteeklicht groen wordt
#define OVERSTEEKLICHT_ROOD_TIJD_SEC 0.5  // de tijd die het oversteeklicht nog op rood blijft staan.
#define OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD_SEC 10.0 // de tijd die overstekenden krijgen om over te steken voordat het groene licht gaat knipperen.
#define OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL 5  // het aantal keren dat het groene oversteeklicht gaat knipperen (een positieve int)
#define OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC 1.0  // de tijd tussen groen oversteeklicht aan en groen oversteeklicht uit.

/*  Als iemand drukt wordt er een programma gestart. 
    oranje, rood, oversteeklichten aan, groen aan, rood uit
    Dit programma is helemaal af als rood uit gaat. 
    Je wilt misschien niet dat iemand direct weer het verkeer wilt stoppen.
    Daarom een pauze waarin het systeem niet reageert op het indrukken van een knop
*/

void handleOversteekLichten(){        
  // Er is gedrukt, het verkeerslicht staat op rood. Hier verander ik alleen de oversteeklichten
  sleepInSecs(OVERSTEEKLICHT_ROOD_TIJD_SEC);
  zetRodeOversteeklichten(UIT);
  zetGroeneOversteeklichten(AAN);
  sleepInSecs(OVERSTEEKLICHT_VOLLEDIG_GROEN_TIJD_SEC);
  //knipperen van het groene oversteeklicht
  for (auto i = 0; i <  OVERSTEEKLICHT_GROEN_KNIPPER_AANTAL; i++) {
    zetGroeneOversteeklichten(UIT);
    sleepInSecs(OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC);
    zetGroeneOversteeklichten(AAN);
    sleepInSecs(OVERSTEEKLICHT_GROEN_KNIPPER_AAN_TIJD_SEC);
  }
  zetGroeneOversteeklichten(UIT);
  zetRodeOversteeklichten(AAN); 
}

void handleGedrukt() {
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

extern "C" { //extern "C" => voorkom name mangling door C++
  void app_main() {   
    setup();          // initaliseren poorten en lichten (oversteeklicht op rood en verkeerslicht op groen)
    while (true) {    // the main loop   
      if (leesIsGedrukt()) {
        handleGedrukt();
      }
    }
  } 
}