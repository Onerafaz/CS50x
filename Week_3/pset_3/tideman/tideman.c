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
}
pair;

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
bool has_cycle(int start, bool visited[MAX]);

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
    // Check if the candidate name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Update the ranks array to indicate the voter's preference
            ranks[rank] = i;
            return true;
        }
    }
    // Candidate name not found, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int preferred_candidate = ranks[i];
            int less_preferred_candidate = ranks[j];
            preferences[preferred_candidate][less_preferred_candidate]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Loop through all pairs of candidates and add preferred candidates to the pairs array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // i is preferred over j
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                // j is preferred over i
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // If the pair is tied, do not add it to the pairs array
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Implement a simple sorting algorithm (bubble sort) to sort the pairs in decreasing order of strength of victory
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                // Swap the pairs if the strength of victory is in decreasing order
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

void lock_pairs(void)
{
    // Initialize an array to keep track of visited nodes during cycle check
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    // Lock pairs in decreasing order of strength of victory, ensuring no cycles are created
    for (int i = 0; i < pair_count; i++)
    {
        // Temporarily lock the pair and check if it creates a cycle
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (has_cycle(pairs[i].winner, visited))
        {
            // If adding this edge creates a cycle, remove the edge from the locked graph
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

        // Reset the visited array for the next iteration
        for (int j = 0; j < candidate_count; j++)
        {
            visited[j] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Print the name of the candidate who is the source of the graph
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                // If any candidate points to this candidate, it is not the source
                is_source = false;
                break;
            }
        }
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}


// Helper function to check if adding an edge creates a cycle
bool has_cycle(int start, bool visited[MAX])
{
    // If we encounter the start node while traversing, it indicates a cycle
    if (visited[start])
    {
        return true;
    }

    visited[start] = true;

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start][i])
        {
            // Check if there's a cycle by exploring the next candidate recursively
            if (has_cycle(i, visited))
            {
                return true;
            }
        }
    }

    return false;
}