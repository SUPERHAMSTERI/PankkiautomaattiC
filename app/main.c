//Kirjastot
#include <stdio.h>


//Muuttujien esittely

int pinOk = 0 ;                     // Tunnistamisen tila
int userAccount = 5454580;          // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta
int userAccountInput = 0;           // Käyttäjän syöttämä käyttäjätunnus
int userAccountPin = 2345;          // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta
int userAccountPinInput = 0 ;       // Käyttäjän syöttämä PIN
int checksum = 0 ;                  // Oikean käyttäjätunnuksen ja PIN -koodin tarkiste
int checksumInput = 0 ;             // Käyttäjän syöttämän käyttäjätunnuksen ja PIN -koodin tarkiste
int sessionOn = 0 ;                 // Ilmaisee onko PIN syötetty ja istunto käynnissä.

/*
Main funktio ja sen esittely näissä kommenteissa*/
int main() {

    /*
     * Kysytään pin koodia niin kauan että tärppää.
     * Tallennetaan Käyttäjätunnus ja PIN - Koodi omaan muuttujaan, joista lasketaan tarkiste
     * tämän jälkeen vertaillaan tarkisteita keskenään. Jos löydetään vastaavuus, lopetetaan tämä toisto toisto toisto.
     */

    while (pinOk == 0) {
    printf("Syötä käyttäjätunnus \n");
    scanf("%i", &userAccountInput);
    printf("Anna tunnusluku \n");
    scanf("%d", &userAccountPinInput);
    checksum = userAccount + userAccountPin;
    checksumInput = userAccountInput + userAccountPinInput;

        if (checksumInput == checksum) {
            pinOk = 1;
            sessionOn = 1;
        }
            else{
                printf("PIN -väärin \n");
        }

    }

    /* Nyt ojelma on saanut oikean PIN koodin ja avataan uusi toistorakenne, jota toistetaan niin kauan, että käyttäjä
     * lopettaa istunnon joko nostolla tai muuten
     */

    while (sessionOn == 1 ){
        printf("Valitse toiminto \n");
    }
    return (0);
}