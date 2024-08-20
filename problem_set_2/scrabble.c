#include <ctype.h>
#include <stdio.h>
#include <string.h>

//assignment

//implement a program in C that determines the winner of a short Scrabble-like game. Your program should prompt for input twice: once for “Player 1” to input their word and once for “Player 2” to input their word.
//Then, depending on which player scores the most points, your program should either print “Player 1 wins!”, “Player 2 wins!”, or “Tie!” (in the event the two players score equal points).

//start
int CalculateWord(char word[256]);

const char LETTERS[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int VAL[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                     1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    char words[2][256];
    int noOfPlayers = 2;
    int scoreSum[noOfPlayers];

    for (int i = 0; i < noOfPlayers; i++)
    {
        // Get Input from the player
        printf("Player %i: ", i + 1);
        scanf("%s", words[i]);

        // capitalize word
        for (int j = 0; j < strlen(words[i]); j++)
        {
            words[i][j] = toupper(words[i][j]);
        }

        // assign calculated score
        scoreSum[i] = CalculateWord(words[i]);
    }

    if (scoreSum[0] > scoreSum[1])
    {
        printf("Player 1 Wins!");
    }
    else if (scoreSum[0] < scoreSum[1])
    {
        printf("Player 2 Wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}

int CalculateWord(char word[256])
{
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // find char in the LETTERS and get the corresponding value from VAL
        for (int j = 0; j < 26; j++)
        {
            if (word[i] == LETTERS[j])
            {
                score += VAL[j];
                break;
            }
        }
    }
    return score;
}
