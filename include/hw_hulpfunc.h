#ifndef HW_HULPFUNC_H 
    #define HW_HULPFUNC_H

    /* 
    Als het bordje aangeeft dat er gedrukt is, zou de melding 'er is gedrukt' ook kunnen komen van storingen van andere apparaten of storingen via andere kabels....
    Meestal zijn die storingen hoog frequent. Je kunt ze dan softwarematig ondervangen door snel na elkaar een paar keer te testen of er werkelijk gedrukt is. 
    Bijvoorbeeld: de functie leesIsGedrukt retourneert alleen TRUE als de hardware 5 keer na elkaar heeft gegeven dat er gedrukt is.     
    Als de hardware 3 keer na elkaar aangeeft dat er gedrukt is en de vierde keer niet, dan retourneert de functie leesIsGedrukt() false.
    GEDRUKT_DEBOUNCE_COUNT geeft het extra aantal keren dat de hardware moet aangeven dat er gedrukt is, voordat de functie leesgedrukt() true terug geeft.     
    GEDRUKT_DEBOUNCE_COUNT = 0 betekent dat er geen debouce controle gebruikt wordt. Hij leest de hardware en retourneert het resultaat. 
    GEDRUKT_DEBOUNCE_COUNT mag niet te groot worden omdat je de knop dan heel lang vast moet houden voor er iets gebeurt. Even op de knop duwen wordt dan niet meer herkend als 'er is gedrukt'.
    Uiteraard moet GEDRUKT_DEBOUNCE_COUNT >= 0 zijn. 
    */
    #define GEDRUKT_DEBOUNCE_COUNT 0

    /*
    GEDRUKT_DEBOUNCE_WACHTTIJD_SEC is de tijd tussen twee tijdstippen tijdens debouncen waarop de hardware probeert te bepalen of er gedrukt is. 
    Deze tijd moet klein zijn. Anders moet je de knop heel lang vast houden voordat er iets gebeurt.
    */
    #define GEDRUKT_DEBOUNCE_WACHTTIJD_SEC 0.1

    void zetRodeVerkeerslichten(int aanUit); 
    void zetGroeneVerkeerslichten(int aanUit); 
    void zetOranjeVerkeerslichten(int aanUit);
    void zetRodeOversteeklichten(int aanUit);    
    void zetGroeneOversteeklichten(int aanUit);
    int  invertLevel(int hardwareLevel);
    bool leesIsGedrukt();     
#endif
