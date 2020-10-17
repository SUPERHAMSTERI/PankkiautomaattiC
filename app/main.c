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
int chooseAction = 0 ;              // Toiminnon valinta
int loopCount = 0 ;                 // Voidaan käyttää toistojen laskemiseen.

/*
 * Main funktio ja sen esittely näissä kommenteissa
 */
int main() {

    printf("Moikkis! \n"); //Tervehditään käyttäjää toistorakenteen ulkopuolella, jottei tervehdys toistuisi.

    /*
     * Kysytään pin koodia niin kauan että tärppää. Tai oikeastaan viisi kertaa. Luovutetaan jos ei tuppaa onnistumaan.
     * Tallennetaan Käyttäjätunnus ja PIN - Koodi omaan muuttujaan, joista lasketaan tarkiste
     * tämän jälkeen vertaillaan tarkisteita keskenään. Jos löydetään vastaavuus, lopetetaan tämä toisto toisto toisto.
     */

    while (pinOk == 0) {

    printf("Kerrothan aivan aluksi käyttäjätunnuksesi! \n");
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

            /*
             * Jos oiekaa syötettä ei tule, niin luovutetaan.
             */

        if (loopCount >= 4) {
            printf("Eihän tästä nyt tule mitään! \n");
            printf("Olet laukaissut turvatoiminnon! Juokse kortteli ympäri ja yritä sitten uudelleen! \n");
            return (0);
        }

        loopCount = loopCount + 1;
    }

    /* Nyt ojelma on saanut oikean PIN koodin ja avataan uusi toistorakenne, jota toistetaan niin kauan, että käyttäjä
     * lopettaa istunnon joko nostolla tai muuten
     */

    /*  Alla testaamista varten pikku purkka, ettei tarvi täytellä salasanoja. Muista poistaa palautukseen!
     * sessionOn = 1; // TESTAAMISTA VARTEN OTA KOMMENTOINTI POIS
     */


    while (sessionOn == 1 ){
        printf("Moi NIMI TÄHÄN! Mitä haluat tehdä? \n");
        printf("1 Nosto" "\n");
        printf("2 Tarkista saldo" "\n");
        printf("0 Lopeta" "\n");
        scanf("%d", &chooseAction);
    }

    return (0);
}