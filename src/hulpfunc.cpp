/* 
Hier staan alle hulpfuncties die je voor elk project kunt gebruiken.
*/

using namespace std;

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