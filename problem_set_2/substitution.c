#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//assignment

//In a substitution cipher, we “encrypt” (i.e., conceal in a reversible way) a message by replacing every letter with another letter. To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when we encrypt it. 
//To “decrypt” the message, the receiver of the message would need to know the key, so that they can reverse the process: translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).

//A key, for example, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB. This 26-character key means that A (the first letter of the alphabet) should be converted into N (the first character of the key), B (the second letter of the alphabet) should be converted into Q (the second character of the key), and so forth.

//A message like HELLO, then, would be encrypted as FOLLE, replacing each of the letters according to the mapping determined by the key.

//create a program that enables you to encrypt messages using a substitution cipher. At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be in the secret message they’ll provide at runtime.

//start
bool ValidateKey(string key);
void EncryptMessage(string plaintext, string key);
string CapitalizeKey(string key);

int main(int argc, string argv[])
{
    // if not proper amount of cl args are present return.
    if (argc != 2)
    {
        printf("Invalid Command Line Arguments!\n");
        return 1;
    }

    // chech for valid key based on rules.
    if (!ValidateKey(argv[1]))
    {
        printf("Invalid Key!\n");
        return 1;
    }

    string key = CapitalizeKey(argv[1]);

    // get input from user
    string plaintext = get_string("plaintext: ");

    // encrypt and print the message
    EncryptMessage(plaintext, key);
}

void EncryptMessage(string plaintext, string key)
{
    // finished string
    char cipher[strlen(plaintext) + 1];

    // in order to terminate the char array
    cipher[strlen(plaintext)] = '\0';

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (!isalpha(plaintext[i]))
        {
            cipher[i] = plaintext[i];
        }
        // check if the current letter is capital
        else if (plaintext[i] == toupper(plaintext[i]))
        {
            cipher[i] = key[plaintext[i] - 65];
        }
        else
        {
            cipher[i] = tolower(key[toupper(plaintext[i]) - 65]);
        }
    }
    printf("ciphertext: %s\n", cipher);
}

bool ValidateKey(string key)
{
    int occurrence[26] = {0};

    // check length
    if (strlen(key) != 26)
    {
        return false;
    }

    // check for invalid characters
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        occurrence[toupper(key[i]) - 65]++;
    }

    // check occurrence so we have every letter once
    for (int i = 0; i < 26; i++)
    {
        if (occurrence[i] != 1)
        {
            return false;
        }
    }

    return true;
}

string CapitalizeKey(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }
    return key;
}
