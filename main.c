//Vakiokirjastot
#include <stdio.h>
#include <string.h>

//Omat funktiot
void session();
int login();
int balance();
int banknote();
void getAccountInfo();

//Muuttujien esittely
int sessionOn = 0 ;                 // Ilmaisee onko PIN syötetty ja istunto käynnissä.
int chooseAction = 0 ;              // Toiminnon valinta
int inLoop = 0 ;                    // Toiminto valittu, voidaan skipata valinta
int loopCount = 0 ;                 // Voidaan käyttää toistojen laskemiseen.
int userAccountBalance;      // Tarkoitus on hakea tämä myöhemmässä vaiheessa jostain muualta, nyt näin
int withdrawalSum = 0 ;             // Nostosumma
char anyKey = 0 ;                   // Juuppismoikkis
int chooseOK = 0 ;                  // Käytetään virheellisten valintojen suodattamiseen
int showBalance = 0;                // Käsketään balanssifunktiota suosiolla näyttämään saldo ilman kyselyjä
char userAccountName;

FILE *acc;
/*
 * Main funktio ja sen toiminnan esittely näissä kommenteissa. Tulossa. Ensi jaksossa.
 */

int main() {
    printf("\n" "Moikkis!" "\n" "\n");

/* Soitellaan pin koodin kyselijälle.
 * Sitten soitellaan funktiolle, joka haalii kaikki toiminnot.
 */


    sessionOn = login();

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

int login() {

    int pincompare;
    int userAccountFound;
    int pinOk = 0 ;                     // Tunnistamisen tila
    char userAccountPin[10];            // Mennään näillä testaamisen helpottamiseksi
    char userAccountInput[30];           // Juuri sitä
    char userAccountPinInput[4];       // Muuttujan nimi kertoo kaiken, mutta kommentoidaan nyt tätäkin
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
            fgets(userAccountInput, 256, stdin);

            if (userAccountInput[strlen(userAccountInput)-1] == '\n')
                userAccountInput[strlen(userAccountInput)-1] = '\0';
            strcat(userAccountInput,".acc");

            if((acc = fopen(userAccountInput, "r")) !=NULL) {
                userAccountFound = 1;
                printf("Anna tunnusluku:" "\n");
                scanf("%s", &userAccountPinInput);
                fgets(userAccountPin, 10, acc);

                if (userAccountPin[strlen(userAccountPin) - 1] == '\n')
                    userAccountPin[strlen(userAccountPin) - 1] = '\0';

            }else{
                printf("Tietojemme mukaan sinua ei ole olemassa. Kokeile luoda itsesi uudelleen.");
            }

            pincompare = strcmp(userAccountPin, userAccountPinInput);
            if (pincompare == 0 && userAccountFound == 1) {
                pinOk = 1;
                fclose(acc);
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
        getAccountInfo();
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

void getAccountInfo(void){
    fgets(userAccountBalance, 10, acc);
    fgets(userAccountPin, 10, acc);

}