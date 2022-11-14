/* 
Hier staan alle hulpfuncties die je voor elk project kunt gebruiken.
*/

using namespace std;
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>  
#include <cmath>
#include <hulpfunc.h> 
#include <string>

string zetHaakjes (string s) {
    return "(" + s + ")";
}

string boolToNlStr(bool b) {
    if (b) 
        return "Ja";
    else 
        return "Nee";
}

void sleepSecs (const double secs) {
    //laat de computer secs seconden wachten    
    vTaskDelay(round ((secs * 1000)/ portTICK_PERIOD_MS));
}