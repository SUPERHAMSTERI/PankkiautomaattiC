//Kirjastot
#include <stdio.h>

//Omat pallerot

//Muuttujien esittely

int pinOk = 0 ;                     // Tunnistamisen tila
int userAccount = 5454580;          // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, protossa nyt näin
int userAccountPin = 2345;          // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, protossa nyt näin
int userAccountBalance = 100 ;      // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, protossa nyt näin
int userAccountInput = 0;           // Käyttäjän syöttämä käyttäjätunnus
int userAccountPinInput = 0 ;       // Käyttäjän syöttämä PIN
int checksum = 0 ;                  // Oikean käyttäjätunnuksen ja PIN -koodin tarkiste
int checksumInput = 0 ;             // Käyttäjän syöttämän käyttäjätunnuksen ja PIN -koodin tarkiste
int sessionOn = 0 ;                 // Ilmaisee onko PIN syötetty ja istunto käynnissä.
int chooseAction = 0 ;              // Toiminnon valinta
int withdrawalFailed = 0 ;          // Toiminto valittu, voidaan skipata valinta
int loopCount = 0 ;                 // Voidaan käyttää toistojen laskemiseen.
int withdrawalSum = 0 ;             // Nostosumma
char something = 0 ;                // Vain jotain

/*
 * Main funktio ja sen esittely näissä kommenteissa
 */
int main() {
    printf("\n\nMoikkis!\n\n");//Tervehditään käyttäjää toistorakenteen ulkopuolella, jottei tervehdys toistuisi.

    /*
     * Kysytään pin koodia niin kauan että tärppää. Tai oikeastaan viisi kertaa. Luovutetaan jos ei tuppaa onnistumaan.
     * Tallennetaan Käyttäjätunnus ja PIN - Koodi omaan muuttujaan, joista lasketaan tarkiste
     * tämän jälkeen vertaillaan tarkisteita keskenään. Jos löydetään vastaavuus, lopetetaan tämä toisto toisto toisto.
     */

    while (pinOk == 0) {
    if (loopCount >= 1){
        printf("\n\nNyt ei mennyt oikein!\n");
        printf("Saat kokeilla uudelleen!\n\n");
    }
    printf("Anna nostotunnuksesi:\n");
    scanf("%i", &userAccountInput);
    printf("Anna tunnusluku:\n");
    scanf("%d", &userAccountPinInput);
    checksum = userAccount + userAccountPin;
    checksumInput = userAccountInput + userAccountPinInput;

        if (checksumInput == checksum) {
            pinOk = 1;
            sessionOn = 1;
        }

            /*
             * Jos oiekaa syötettä ei tule, niin luovutetaan.
             */

        if (loopCount >= 4) {
            printf("Hupsistarallukkaa!\n\n");
            printf("Taidat arvailla! Mene pois ja anna seuraavan tulla kokeilemaan onneaan!\n");
            break;
        }

        loopCount = loopCount + 1;
    }

    /* Nyt ojelma on saanut oikean PIN koodin ja avataan uusi toistotoistorakenne, jota toistetoistetaan niin kauan,
     * että käyttäjä lopettaa istunnon joko tekemällä jotain tai kyllästymällä.
     */

        if (sessionOn == 1){
        printf("Moi NIMI! Miten voimme auttaa?\n", sessionOn);
        }

    while (sessionOn == 1){
        if (withdrawalFailed == 0){
        printf("1 Nosto" "\n");
        printf("2 Tarkista saldo" "\n");
        printf("0 Lopeta" "\n");
        scanf("%d", &chooseAction);
        }

        switch (chooseAction) {
            case 0 :
                sessionOn = 0;
                break;
            case 1 :
                printf("\nPaljon haluat nostaa?" "\n");
                scanf("%d", &withdrawalSum);
                if(withdrawalSum <= userAccountBalance) {
                    printf("Kiva! Ota luukusta %d euroa!" "\n", withdrawalSum);
                    sessionOn = 0;
                    userAccountBalance = userAccountBalance - withdrawalSum;
                    break;

                } else {
                    printf("\nEi sinulla ole niin paljoa rahaa!\n", withdrawalSum);
                    withdrawalFailed = 1;
                    chooseAction = 2;
                    break;
                }

            case  2:
                printf("\nTilisi saldo on" "\n");
                printf("%d" "EUR\n\n", userAccountBalance);
                if (withdrawalFailed == 1){
                    printf("Haluatko nostaa jonkin toisen summan?\n" "1 = JOO" "\n" "0 = EI" "\n");
                } else {
                    printf("\nHaluatko nostaa rahaa?" "1 = JOO" "\n" "0 = EI" "\n");
                }
                scanf("%d", &chooseAction);
                break;
        }
    }
/*
 * Lopetetaan kaikki nyt tähän moikkis!
*/

    sessionOn = 0;
    printf("\n*********************************\n");
    printf("** Moikkis seuraavaan kertaan! **\n");
    printf("*********************************\n");
    scanf("%d", &something);                            //Odotetaan jotain syötettä ennen lopetusta, ihan vain esimerkin vuoksi
    return (0);
}