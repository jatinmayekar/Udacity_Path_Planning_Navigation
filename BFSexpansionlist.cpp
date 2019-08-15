#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Map class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int> > grid = {
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 }
    };
};

// Planner class
class Planner : Map {
public:
    int start[2] = { 0, 0 };
    int goal[2] = { mapHeight - 1, mapWidth - 1 };
    int cost = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int> > movements{
        { -1, 0 },
        { 0, -1 },
        { 1, 0 },
        { 0, 1 }
    };
};

// Template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec)
{
    for (int i = 0; i < Vec.size(); ++i) {
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        cout << endl;
    }
}

/* Code the search function which will generate the expansion list */

void search(Map map, Planner planner)
{
    //  Define the open vector
    vector<vector<int> > open;
    
    // Set the starting point
    open.push_back({0, planner.start[0], planner.start[1]}); 
    
    // Define the explored grid cell check vector
    vector<vector<int> > eg(map.mapHeight, vector<int>(map.mapWidth));
    
    // Set the start cell as explored
    eg[planner.start[0]][planner.start[1]] = 1;
    
    //  Define the total path cost variable
    int pc = 0;
    
    // Set the goal flag variable
    // If path to goal exists, set it to 1
    int g = 0; 
    
    // Define the no. of steps variable - while loop iteraion variable
    int n = 0;
    
    // Define the visible cell cordinates
    int x = 0;
    int y = 0;
    
    // Define the next picked up index variable
    int k = 0;
    
    //  Search the map
    while(g == 0)
    {
        // Print the picked cell's triplet value
        // cout<< open[k][0] << " " << open[k][1] << " " << open[k][2] << endl;
        
        // Check the adjacent cells - visible cells - up, left, down, right
        for (int i = 0; i < planner.movements.size(); i++)
        {
            // Define the visible cells
            x = open[k][1] + planner.movements[i][0];
            y = open[k][2] + planner.movements[i][1];
            
            // Check if the cell is inside the grid - boundary conditions
            if ( (x >= 0) && (y >= 0) && (x < map.mapHeight) && (y < map.mapWidth) )
            {
                // Check if the cell is not an obstacle
                if( map.grid[x][y] == 0)
                {
                    // Check if the cell is the goal
                    if((x == planner.goal[0]) && (y == planner.goal[1]))
                    {
                        // Print the final triplets value
                        cout << (open[k][0] + planner.cost) << " " << x << " " << y << endl;
                        g = 1;
                        break;
                    }
                    
                    // Check if you have not previously seen the cell 
                    // so as not have same visible cell with different path cost ie., 
                    // viewed from different picked cells, 
                    // thus making the openvector contain all unique unseen cells
                    else if (eg[x][y] == 0)
                    {
                        // Add cells to the Frontier
                        open.push_back({open[k][0] + planner.cost, x, y});
                        
                        // Set the cell as seen
                        eg[x][y] = 1;
                    }
                }
            }
        }
        
        // Count expansion steps
        n++;
        // cout<< n << endl;
        
        // Check if reached goal
        if (g == 1)
        {
            break;
        }
        
        // Erase the picked cell so that open contains only unexplored seen cells 
        open.erase(open.begin());
        
        // Check for roadblock - If there are no unexplored seen cells in the open vector
        // then it means that there are no free cells left to go to,
        // thus it's a roadblock 
        if (open.size() == 0)
        {
            cout << "Roadblock - Failed to reach the goal" << endl;
            break; // Exit the while loop
        }
        
        // Iterate to the next cell since no roadblock
        // Choose the cell with the lowest total path cost value
        k = 0;
        for(int i = 1; i < open.size() - 1; i++)
        {
            // Compare the total path cost
            if (open[i][0] < open[k][0])
            {
                k = i;
            }
        }
    } 
    cout << "No. of steps = " << n << endl;
    // cout << "Size of open vector = " << open.size() << endl;
}

int main()
{
    // Get starting timepoint 
    auto start = high_resolution_clock::now();
    
    // Instantiate map and planner objects
    Map map;
    Planner planner;
    
    // Search for the expansions
    search(map, planner);
    
    // Get ending timepoint 
    auto stop = high_resolution_clock::now(); 
  
    // Get duration. Substart timepoints to  
    // get durarion. To cast it to proper unit 
    // use duration cast method 
    auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
         
    return 0;
}

/*
Output:
0 0 0
1 1 0
2 2 0
3 3 0
4 4 0
5 4 1
6 4 2
7 3 2
8 2 2
8 3 3
9 1 2
9 2 3
9 3 4
10 0 2
10 1 3
10 2 4
10 3 5
11 4 5
No. of steps = 17 
*/
/* Time taken = 111 sec compared to the ans provided by Udacity, 347 sec */

/* If grid changed to this:
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 1, 1, 0 }
then output:
0 0 0
1 1 0
2 2 0
3 3 0
4 4 0
Roadblock - Failed to reach the goal
No. of steps = 5
*/
