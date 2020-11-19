//Vakiokirjastot

#include <stdio.h>

//Omat funktiot

int pinInput();
void session();
int banknote();

//Muuttujien esittely

int pinOk = 0 ;                     // Tunnistamisen tila
int userAccount = 1 ;               // Mennään näillä testaamisen helpottamiseksi
int userAccountPin = 1 ;            // Mennään näillä testaamisen helpottamiseksi
//int userAccount = 5454580;        // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, nyt näin
//int userAccountPin = 2345;        // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, nyt näin
int userAccountBalance = 200 ;      // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, nyt näin
int userAccountInput = 0;           // Juuri sitä
int userAccountPinInput = 0 ;       // Muuttujan nimi kertoo kaiken, mutta kommentoidaan nyt tätäkin
int checksum = 0 ;                  // Oikean käyttäjätunnuksen ja PIN -koodin tarkiste
int checksumInput = 0 ;             // Käyttäjän syöttämän käyttäjätunnuksen ja PIN -koodin tarkiste
int sessionOn = 0 ;                 // Ilmaisee onko PIN syötetty ja istunto käynnissä.
int chooseAction = 0 ;              // Toiminnon valinta
int inLoop = 0 ;                    // Toiminto valittu, voidaan skipata valinta
int loopCount = 0 ;                 // Voidaan käyttää toistojen laskemiseen.
int withdrawalSum = 0 ;             // Nostosumma
char anyKey = 0 ;                   // Juuppismoikkis
int chooseOK = 0 ;
int withdrawalSum50 = 0 ;
int withdrawalSum20 = 0 ;
int banknote20 = 0;
int banknote50 = 50;

/*
 * Main funktio ja sen toiminnan esittely näissä kommenteissa. Tulossa. Ensi jaksossa.
 */


int main() {

    printf("\nMoikkis!\n\n");

/* Soitellaan pin koodin kyselijälle.
 * Sitten soitellaan funktiolle, joka haalii kaikki toiminnot. Tämä funktio hajoitetaan tulevissa versioissa, mutta nyt näin
 */


    sessionOn = pinInput();
    session();

/*
 * Lopetetaan nyt tähän moikkis!
*/

    sessionOn = 0;
    printf("\n*********************************\n");
    printf("** Moikkis seuraavaan kertaan! **\n");
    printf("*********************************\n");
    scanf("%c", &anyKey);                            //Odotetaan jotain syötettä ennen lopetusta, jotta kaikki tulosteet ovat luettavissa.
    return (0);
}





/*
 * Seuraavaksi: funktioita.
*/

int pinInput() {

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
                return(1);
            }

            /*
             * Jos oiekaa syötettä ei tule, niin luovutetaan.
             */

            loopCount = loopCount + 1;

            if (loopCount >= 5) {
                printf("Hupsistarallukkaa!\n\n");
                printf("Taidat arvailla! Mene pois ja anna seuraavan tulla kokeilemaan onneaan!\n");
                return(0);
            }

        }

    return (0);

}

void session (void) {

    /* Nyt ohjelma on saanut oikean PIN koodin ja avataan uusi toistotoistorakenne, jota toistetoistetaan niin kauan,
     * että käyttäjä lopettaa istunnon joko tekemällä jotain tai kyllästymällä. Tämä kaikki tapahtuu session() -funktiossa.
     * Session funktio olisi tarkoitus hajoittaa järkeviin osiin, mutta vielä ohjelma on niin yksinkertainen, että mennään
     * näin
     */

    while (sessionOn == 1 && chooseOK ==  0){
        printf("\nMoi NIMI! Miten voimme auttaa?\n");
        printf("1 Nosto" "\n");
        printf("2 Tarkista saldo" "\n");
        printf("0 Lopeta" "\n");
        scanf("%d", &chooseAction);

        if(chooseAction == 0 || chooseAction == 1 || chooseAction == 2){
            chooseOK = 1;
        } else {
            printf("Valitse kunnolla!"  "\n");
        }

    }

    while (sessionOn == 1){
        /*if (inLoop == 0){

        }*/

        switch (chooseAction) {
            case 0 :
                sessionOn = 0;
                break;

            case 1 :
                printf("\nPaljon haluat nostaa?" "\n");
                scanf("%d", &withdrawalSum);
                if(withdrawalSum <= userAccountBalance) {
                    printf("Kiva! Ota luukusta %d euroa!" "\n", withdrawalSum);
                    banknote();
                    sessionOn = 0;
                    userAccountBalance = userAccountBalance - withdrawalSum;
                    printf("Tilisi saldo on nyt %d euroa!" "\nLupaan, ensi kerralla kysyn haluatko saldon ruuudulle", userAccountBalance);
                    break;

                } else {
                    printf("\nEi sinulla ole niin paljoa rahaa!\n");
                    inLoop = 1;
                    chooseAction = 2;
                    break;
                }

            case  2:
                printf("\nTilisi saldo on" "\n");
                printf("%d" "EUR\n\n", userAccountBalance);
                if (inLoop == 1){
                    printf("Haluatko nostaa jonkin toisen summan?\n" "1 = JOO" "\n" "0 = EI" "\n");
                } else {
                    printf("\nHaluatko nostaa rahaa?\n" "1 = JOO" "\n" "0 = EI" "\n");
                }

                scanf("%d", &chooseAction);
                break;

            default:
                inLoop = 1;
        }
    }
}

int banknote (){
    if(withdrawalSum < 20){
        printf("Ei noin minimaalisia summia voi nostaakkaan! Pienin mahdollinen nostosumma on 20 EUR");
    }
    if(withdrawalSum % 20 == 0){
        withdrawalSum20 = withdrawalSum / 20;
        banknote20 = withdrawalSum20;
        printf("Saat %d kappaletta 20 euron seteleitä", banknote20);
    }
    if(withdrawalSum % 50 == 0){
    withdrawalSum50 = withdrawalSum / 50;
    banknote50 = withdrawalSum50;
    }
    if(withdrawalSum % 10 != 0){
        printf("Me emme ropoja jakele!");
    }
    return (0);
}