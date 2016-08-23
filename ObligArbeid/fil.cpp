#include <QDebug>
#include "fil.h"


void Fil::skriv(std::string filnavn, Vertex vertices[], const int n)
{
    std::ofstream utfil(filnavn.c_str());   // Opprette (lage) en fil med angitt parameter filnavn

    utfil << n << std::endl;                // Skrive til fil. Skriver først antall vertices
    for (int i=0; i<n; i++)
        utfil << vertices[i] << std::endl;

    utfil.close();                          // Lukke fil
}

/* lesfil() åpner og leser en tekstfil med n Vertex-data
 * n leses inn først og det allokeres minne
 */
void Fil::les(std::string filnavn, Vertex*& vertices, GLuint &n)
{
    // std::cout << "\nFil::les()" << std::endl;


    // Åpne eksisterende fil
       std::ifstream inn;
       inn.open(filnavn.c_str());

    // Lese punkter - her: linje for linje
       if (inn.is_open())
       {
           inn >> n;
           vertices = new Vertex[n];
           for (int i=0; i<n; i++)
           {
                inn >> vertices[i];
                std::cout << vertices[i] << std::endl;
           }
       }
    // Lukke fil
        inn.close();
        //std::cout << "Filen er lest." << std::endl;
    //return n;
}

