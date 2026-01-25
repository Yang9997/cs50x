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
bool check_cycle(int start, int end);
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
            // 这里又弄反了...修改了vote和record_preferences
            // 选民的第rank+1偏好是第i+1个候选人
            ranks[rank] = i;
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
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
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
    // test
    // for(int i = 0; i < pair_count; i++)
    // {
    //     printf("%i ",preferences[pairs[i].winner][pairs[i].loser]);
    // }
    // printf("\n");
    int maxpairwinner;
    int maxpairloser;
    int tag;
    for (int i = 0; i < (pair_count - 1); i++)
    {
        maxpairwinner = pairs[i].winner;
        maxpairloser = pairs[i].loser;
        tag = i;
        // 选择排序，大的放在前面，每轮选出要排序的内容中最大的，交换到放在本轮排序最前面
        for (int j = i + 1; j < pair_count; j++)
        {
            // if (temp[j] < temp[tag])
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[tag].winner][pairs[tag].loser])
            {
                maxpairwinner = pairs[j].winner;
                maxpairloser = pairs[j].loser;
                tag = j;
            }
        }
        if (tag != i)
        {
            // temp[tag] = temp[pair_count - i];
            // temp[pair_count - i] = minnum;

            pairs[tag].winner = pairs[i].winner;
            pairs[tag].loser = pairs[i].loser;
            pairs[i].winner = maxpairwinner;
            pairs[i].loser = maxpairloser;
        }
    }
    // test
    // for(int i = 0; i < pair_count; i++)
    // {
    //     printf("%i ",preferences[pairs[i].winner][pairs[i].loser]);
    // }
    return;
}
// 成环判定，递归逻辑完全想不出来
bool check_cycle(int start, int end)
{
    if (start == end)
    {
        // 成环
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // start到i有一条路
        if (locked[start][i])
        {
            if (check_cycle(i, end))
            {
                return true;
            }
        }
    }

    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // 成环判定？
    for (int i = 0; i < pair_count; i++)
    {
        //反向成环，说明再加上这条边就成环了
        if (!check_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
// 题里面的意思应该是【一定含有第一条链】的尽头节点
void print_winner(void)
{
    // TODO
    int nametag = pairs[0].winner;
    for (int i = 0; i < candidate_count ; i++)
    {
        if (locked[i][nametag])
        {
            nametag = i;
            i = -1;
        }
     }
    printf("%s\n",candidates[nametag]);
    return;
}
