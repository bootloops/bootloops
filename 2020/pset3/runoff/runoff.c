#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// meaning: CANDIDATE[n] is VOTER[i]'s RANK[j]

int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) //give each candidate a name from argv
    {
        candidates[i].name = argv[i + 1]; //assign names from argv to candidate[i].name
        candidates[i].votes = 0; //set default, 0 votes
        candidates[i].eliminated = false; //default false, eliminated
    }

    voter_count = get_int("Number of voters: "); //obvious, get voter count
    if (voter_count > MAX_VOTERS) //if more than 9, error
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) //ask for each voter
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) //ask what rank, for how many candidates there are, and repeat for each candidate
        {
            string name = get_string("Rank %i: ", j + 1); //if 1 candidate, only 1 rank... if 2, 2 ranks, if 3, 3 ranks..etc

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    /* VOTE COMPLETE -- THIS IS NOW WORKING 06/09/2020 20:34  */
    int C = candidate_count;
    int x, v = voter;
    for (x = 0; x < C; x++)
    {
        if (strcmp(name, candidates[preferences[v][x]].name) == 0 && rank > 0)
        {
            return true;
        }
        if (strcmp(name, candidates[x].name) == 0)
        {
            //add each voters prefered rank to [x] in pref[v][x]
            preferences[v][rank] += x;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    /*
    Recall that for a voter i, their top choice candidate is represented by preferences[i][0], their second choice candidate by preferences[i][1], etc.
    Recall that the candidate struct has a field called eliminated, which will be true if the candidate has been eliminated from the election.
    Recall that the candidate struct has a field called votes, which you’ll likely want to update for each voter’s preferred candidate.
    #*#*#*pseduo code*#*#*#
    for i = 0, j = 0; i < voter_count; i++ //i is gonna increment up, j will remain 0
            if (!candidates[preferences[i][j]].eliminated) //if not eliminated
            //add votes to candidate j
                candidates[preferences[i][j]].votes++
            else
            //if eliminated
                //candidates[preferences[i][j]].eliminated = false
                candidates[preferences[i--][j++]]

    FINALLY!! Below is COMPLETED! 06/09/2020 21:03
    */

    for (int i = 0, j = 0; i < voter_count; i++)
    {
        //if ( strcmp(name, candidates[preferences[i][j]].name) == 0 )
        //first rank
        if (!candidates[preferences[i][j]].eliminated)
        {
            candidates[preferences[i][j]].votes++;
            j = 0;
        }
        else
        {
            j++;
            i--;
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int MAJ = (voter_count / 2) + 1;
    int C = candidate_count;
    for (int i = 0; i < C; i++)
    {
        if (candidates[i].votes >= MAJ)
        {
            //printf("WINNER: %s\n VOTES: %d", candidates[i].name, candidates[i].votes); //debugg
            printf("%s\n", candidates[i].name);
            return true;
        }

    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //THIS FUNCTION WILL RETURN THE LEAST NUM OF VOTES
    //loop through all candidates votes who have not been eliminated
    // --identify the one who has the least votes
    // --return that value
    /* COMPLETE 06/09/2020 21:36 */
    int MIN = (voter_count / 2);
    int C = candidate_count;
    for (int x = 1; x < C; x++)
    {
        if (!candidates[x].eliminated)
        {
            if (MIN > candidates[x].votes)
            {
                MIN = candidates[x].votes;
            }
        }
    }
    return MIN;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int C = candidate_count;
    int V = voter_count;

    //remember to use int min somewhere -- this is whats missing i think
    for (int i = 0; i < C; i++)
    {
        if (candidates[i].eliminated && candidates[i].votes < min)
        {
            if (candidates[i].votes == candidates[i - 1].votes)
            {
                return true;
            }
            else
            {
                continue;
            }

        }
        if (candidates[i].votes == candidates[i + 1].votes)
        {
            if (candidates[i].votes == candidates[i - 1].votes)
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if ((!candidates[i].eliminated) && (candidates[i].votes == min))
        {
            //if not eliminated and is least voted, eliminate.
            candidates[i].eliminated = true;
        }
        else
        {
            continue;
        }
    }
    return;
}
