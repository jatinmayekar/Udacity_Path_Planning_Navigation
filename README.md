# Udacity_Path_Planning_Navigation

## Overview
- Decision making aspect
- Given the map and the goal position, path planning is the calclulation of the path that gets the robot ewhere it needs to go
- Path planning is a strategic decision
- On its way the robot may encounter obstacles in its planned path and so with real-time sensor readings it has to use obstacle aviodance techniques to modify the original path
- Obstacle aviodance is a tactical decision

## Path Planning

* Two methods to assess the path planning algo: whether they are
  * Complete 
    - algo able to find a path between start and a goal when one exists
    - able to solve all solvable problems and return no solution for unsolvable poroblems
  * Optimal 
    - offers the best solution
    - best - shortest path, lowest time, or lowest risk path
    
* Bug algorithm 
  - Robot heads directly towards the goal 
  - Traverses the obstacle clockwise until it reaches its intended(planned) path   
  - Repeat until arrived at goal
  - Niether complete nor optimal
  
* Three types of path planning
  - Discrete(or combinatorial) 
    - Most straightforward
    - Explicitly discretize the workspace into a connected graph and apply a graph seacrh algo to calculate the best path
    - Very precise - precision depends on how fine you choose to discretize the space
    - Very thorough - discretize the complete workspace
    - Very computaionally expensive 
    - Best suited for low-dimensional problems
  - Sample-based
    - Suited for high dimensional problems
    - Instead of discretizing the entire workspace, it takes a no of samples and uses them to build a discrete representation of workspace
    - Not as precise as in discrete but much quicker to construct - relatively low no of samples
    - May not be the best path - but better to generate a feasible path rather than wait a long time for optimal path
  - Probabilistic
    - First two approaches do not consider of who or what is executing the actions 
    - Takes into account the uncertainty of the robot's motion
    - Especially helpful in highly-constrained environment with sensitive or high-risk areas
    
## Discrete Path Planning

* Ba
