//Vakiokirjastot
#include <stdio.h>

//Omat funktiot
void session();
int pinInput();
int balance();
int banknote();

//Muuttujien esittely
int pinOk = 0 ;                     // Tunnistamisen tila
int userAccount = 1 ;               // Mennään näillä testaamisen helpottamiseksi
int userAccountPin = 1 ;            // Mennään näillä testaamisen helpottamiseksi
int userAccountBalance = 2000 ;      // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, nyt näin
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
int chooseOK = 0 ;                  // Käytetään virheellisten valintojen suodattamiseen
int showBalance = 0;                // Käsketään balanssifunktiota suosiolla näyttämään saldo ilman kyselyjä

/*
 * Main funktio ja sen toiminnan esittely näissä kommenteissa. Tulossa. Ensi jaksossa.
 */

int main() {

    printf("\n" "Moikkis!" "\n" "\n");

/* Soitellaan pin koodin kyselijälle.
 * Sitten soitellaan funktiolle, joka haalii kaikki toiminnot.
 */


    sessionOn = pinInput();
    session();
    sessionOn = 0;
    printf("\n" "\n" "*********************************" "\n");
    printf("** Moikkis seuraavaan kertaan! **" "\n");
    printf("*********************************" "\n");
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
                printf("\n" "\n" "Nyt ei mennyt oikein!" "\n");
                printf("Saat kokeilla uudelleen!" "\n" "\n");
            }

            printf("Anna nostotunnuksesi:" "\n");
            scanf("%i", &userAccountInput);
            printf("Anna tunnusluku:" "\n");
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
                printf("Hupsistarallukkaa!" "\n" "\n");
                printf("Taidat arvailla! Mene pois ja anna seuraavan tulla kokeilemaan onneaan!" "\n");
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
        printf("\n" "Moi NIMI! Miten voimme auttaa?" "\n");
        printf("1 Nosto" "\n");
        printf("2 Tarkista saldo" "\n");
        printf("0 Lopeta" "\n");
        scanf("%d", &chooseAction);

        if(chooseAction == 0 || chooseAction == 1 || chooseAction == 2){
            chooseOK = 1;
        } else {
            printf("Valitse kunnolla!" "\n");
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
                printf("\n" "Paljon haluat nostaa?" "\n");
                scanf("%d", &withdrawalSum);

                if(withdrawalSum <= userAccountBalance) {
                    banknote();
                    break;
                } else {
                    printf("\n" "Ei sinulla ole niin paljoa rahaa!" "\n");
                    inLoop = 1;
                    chooseAction = 2;
                    break;
                }

            case  2:
                showBalance = 1;
                balance();

                if (inLoop == 1){
                    printf("Haluatko nostaa jonkin toisen summan?" "\n");
                } else {
                    printf("\n" "Haluatko nostaa rahaa?" "\n");
                }

                printf("1 = JOO" "\n");
                printf("0 = EI" "\n");

                scanf("%d", &chooseAction);
                break;

            default:
                inLoop = 1;
        }
    }
}

/* Tämä funktio laskelee, minkäsmoista seteliä sitä syljettäisiin ulos. Näyttää kammottavalta, mutta toimii.
 * Koska taustalla on vain lyhyt matikka, voi ajatus sisältää ajatusvirheen. Siksi tarkistetaan, että jaettavaksi
 * menevien setelien summa vastaa pyydettyä, ennen kuin mennään mitään veloittelemaan. */

int banknote (){

    int banknote20;                 // 20€ setelien määrä
    int banknote50;                 // 50€ setelien määrä
    int withdrawalSumN;             // Käytetään laskemaan seteleitä, jos summa ei ole jaollinen 20:llä tai 50llä.
    int withdrawalSumY;             // Käytetään laskemaan seteleitä, jos summa ei ole jaollinen 20:llä tai 50llä.

    if(withdrawalSum == 30 || 1000 < withdrawalSum || withdrawalSum < 20 || withdrawalSum % 10 != 0){
        printf("Et voi nostaa %d EUR. Tarjoamme vain 20 EUR tai 40 - 1000 EUR suuruisia nostoja." "\n", withdrawalSum);
        printf("Voit valita summan kymmenen euron portaittain." "\n");
        printf("Valitse toinen mieluisa summa tarjoamistamme vaihtoehdoista!" "\n");
        inLoop = 1;
        return (0);
    }

    if(withdrawalSum % 50 == 0 && sessionOn != 0){
        banknote50 = withdrawalSum / 50;
        userAccountBalance = userAccountBalance - withdrawalSum;
        printf("Saat %d kappaletta 50 euron paperirahaa" "\n", banknote50);
        balance();
        sessionOn = 0;
    }

    if (withdrawalSum >= 20  && withdrawalSum % 50 != 0 && sessionOn != 0){
        withdrawalSumY = withdrawalSum - 50;
        banknote50 = withdrawalSumY / 50;
        withdrawalSumY = banknote50 * 50;
        withdrawalSumN = withdrawalSum - withdrawalSumY;
        banknote20 = withdrawalSumN / 20;
        withdrawalSumN = banknote20 * 20;

        if (withdrawalSumN + withdrawalSumY == withdrawalSum){
            userAccountBalance = userAccountBalance - withdrawalSum;

            if(banknote50 >=1){
                printf("Saat %d kappaletta 50 euron paperirahaa." "\n", banknote50);
            }

            printf("Saat %d kappaletta 20 euron paperirahaa" "\n", banknote20);
            balance();
            sessionOn = 0;
        } else{
            withdrawalSumY = withdrawalSum - 20;
            banknote50 = withdrawalSumY / 50;
            withdrawalSumY = banknote50 * 50;
            withdrawalSumN = withdrawalSum - withdrawalSumY;
            banknote20 = withdrawalSumN / 20;

            if (withdrawalSumN + withdrawalSumY == withdrawalSum) {
                userAccountBalance = userAccountBalance - withdrawalSum;
                printf("Saat %d kappaletta 50 euron paperirahaa" "\n", banknote50);
                printf("Saat %d kappaletta 20 euron paperirahaa" "\n", banknote20);
                balance();
                sessionOn = 0;
                return (0);
            } else{
                printf("HUPSISTARALLUKKAA!" "\n");
                printf("Rahojen jakamisessa sattui nyt harmillinen virhe!" "\n");
                inLoop = 1;
                return (0);
            }

        }
    }
    return (0);
}

int balance(){

    if (showBalance == 0){
        printf("Haluatko tulostaa saldon?" "\n");
        printf("1 = JOO" "\n");
        printf("0 = EI" "\n");
        scanf("%d", &showBalance);
    }

    if(showBalance == 1){
        printf("Tilisi saldo on %d EUR." "\n", userAccountBalance);
    }

    return(0);
}