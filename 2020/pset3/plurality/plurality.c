#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) //because i is counting from 0, argv[i + 1];
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int i = candidate_count;
    int x;
    //printf("candidate_count: %i\n", i);
    for (x = 0; x < i; x++)
    {
        //printf("%i. %s\n", x+1,candidates[x].name); //debugging
        //printf("\t votes: %i. \n", candidates[x].votes); //testing
        if (strcmp(name, candidates[x].name) == 0) //great strcmp() function makes things easy
        {
            //printf("Yes!\n"); //debugging
            candidates[x].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //printf("Candidates Votes: \n"); //debugging
    char name_length;
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("\t %s", candidates[i].name); //debugging
        //printf("\t %i\n", candidates[i].votes); //debugging
        string WinName = candidates[i].name;
        int WinVote = candidates[i].votes;
        int Right = candidates[i + 1].votes;
        int Left = candidates[i - 1].votes;

        if (WinVote >= Right) //scan right, and check if greater than OR equalto.. if yes, next if
        {
            if (WinVote >= Left) //scan left, and check if greater than OR equal to
            {
                //printf("%s :: %i\n", WinName, WinVote); //debugging
                printf("%s\n", WinName);
            }
        }
    }
    return;
}

