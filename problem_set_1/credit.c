#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//assignment

//A credit (or debit) card, of course, is a plastic card with which you can pay for goods and services. Printed on that card is a number that’s also stored in a database somewhere, so that when your card is used to buy something, the creditor knows whom to bill. 
//There are a lot of people with credit cards in this world, so those numbers are pretty long: American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. And those are decimal numbers (0 through 9), not binary, which means, for instance, that American Express could print as many as 10^15 = 1,000,000,000,000,000 unique cards.
//
//All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem); and all Visa numbers start with 4. 
//But credit card numbers also have a “checksum” built into them, a mathematical relationship between at least one number and others. That checksum enables computers (or humans who like math) to detect typos (e.g., transpositions), if not fraudulent numbers, without having to query a database, which can be slow. 
//Of course, a dishonest mathematician could certainly craft a fake number that nonetheless respects the mathematical constraint, so a database lookup is still necessary for more rigorous checks.
//
//implement a program in C that checks the validity of a given credit card number, using Luhn’s Algorithm.

//start
int main(void)
{
    long card = get_long("Enter Credit Card: ");
    char cardStr[256];
    sprintf(cardStr, "%li", card);

    // validate checksum
    int sum = 0;
    int counter = 0;
    for (int i = strlen(cardStr) - 1; i >= 0; i--)
    {
        int num = (cardStr[i] - '0');
        if (counter % 2 == 0)
        {
            sum += num;
        }
        else
        {
            num *= 2;
            if (num > 9)
            {
                sum += 1 + ((num % 10));
            }
            else
            {
                sum += num;
            }
        }
        counter++;
    }

    // check what type of card it is
    char cardType[50];
    strncpy(cardType, "INVALID", 50);
    if (sum % 10 == 0)
    {
        if (cardStr[0] == '4' && (strlen(cardStr) == 13 || strlen(cardStr) == 16))
        {
            strncpy(cardType, "VISA", 50);
        }
        else if (cardStr[0] == '5' && (strlen(cardStr) == 16))
        {
            if (cardStr[1] == '1' || cardStr[1] == '2' || cardStr[1] == '3' || cardStr[1] == '4' ||
                cardStr[1] == '5')
            {
                strncpy(cardType, "MASTERCARD", 50);
            }
        }
        else if (cardStr[0] == '3' && (strlen(cardStr) == 15))
        {
            if (cardStr[1] == '4' || cardStr[1] == '7')
            {
                strncpy(cardType, "AMEX", 50);
            }
        }
    }

    printf("%s\n", cardType);
}
