#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    // // test
    // for (int i = 0 ; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         if (i == j)
    //         {
    //             printf("  ");
    //             continue;
    //         }
    //         printf("%i ",preferences[i][j]);
    //     }
    //     printf("\n");
    // }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[i] = rank;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0 ; i < candidate_count ; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ( i == j)
            {
                continue;
            }
            if (ranks[i] < ranks[j])
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if(preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // int temp[pair_count] = {0};
    // for (int i = 0; i < pair_count; i++)
    // {
    //     temp[i] = preference[pairs[i].winner][pairs[i].loser];
    // }
    int minpairwinner = pairs[0].winner;
    int minpairloser = pairs[0].loser;
    int tag = 0;
    for (int i = 0; i < (pair_count - 1); i++)
    {
        minpairwinner = pairs[0].winner;
        minpairloser = pairs[0].loser;
        tag = 0;
        for (int j = 0; j < (pair_count - i); j++)
        {
            // if (temp[j] < temp[tag])
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[tag].winner][pairs[tag].loser])
            {
                minpairwinner = pairs[j].winner;
                minpairloser = pairs[j].loser;
                tag = j;
            }
        }
        if (tag != (pair_count - i))
        {
            // temp[tag] = temp[pair_count - i];
            // temp[pair_count - i] = minnum;

            pairs[tag].winner = pairs[pair_count -i].winner;
            pairs[tag].loser = pairs[pair_count - i].loser;
            pairs[pair_count - i].winner = minpairwinner;
            pairs[pair_count - i].loser = minpairloser;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < (pair_count - 1); i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int nametag = pairs[0].winner;
    bool notstart = true;
    while (notstart)
    {
        for (int i = 0; i < candidate_count - 1; i++)
        {
            if (locked[i][nametag])
            {
                nametag = i;
                break;
            }
        }
        notstart = false;
    }
    printf("%s\n",candidates[nametag]);
    return;
}
