/*Kirjastot*/
#include <stdio.h>
#include <wchar.h>


/*
Muuttujien esittely*/
int pinOk = 0 ;
int userAccount = 5454580;
int userAccountInput = 0;
int userAccountPin = 2345;
int userAccountPinInput = 0 ;
int checksum = 0 ;
int checksumInput = 0 ;
int sessionOn = 0 ;

/*
Main funktio ja sen esittely näissä kommenteissa*/
int main() {
/*
    Kysytään pin koodia niin kauan että tärppää.
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
    while (sessionOn == 1 ){
        printf("Valitse toiminto \n");
    }
    return (0);
}