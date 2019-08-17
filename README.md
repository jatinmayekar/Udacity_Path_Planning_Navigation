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

* Develop a convenient continuous representation - can be done by representing the problem space as the configuration space
* Configuration space - known as C space - alternate way of representing the problem space - takes into account geometry of the robot and makes it easier to apply discrete search algorithms
* Discretization -  The C space must be discretized so that it can be easily be used into algo - represented by a graph
* Graph - Search algo can be applied to the graph to find the best path from the start node to the goal node

### Continuous Representation

* Robot represented as a point - path planning relatively easy - but impractical as robot has non-zero dimensions
* Simple way - create a circle with the most outer edge as a radius to represent the robot - check the distance of this circle with the obstacles along the planned paths - select the one that has enough space - but lot of work
* Best way - expand the obstacle by the radius of the robot and then treat robot as a point
* This is called configuration space - C space - set of all robot poses
* Divided into
    - C<sub>free</sub> - set of robot poses in free space that do not collide with any obstacles
    - C<sub>obs</sub> - set of robot poses in free space that are in collision with obstacles or walls 

### Minkowski Sum

* Mathematical property - used to compute the config space given an obstacle geometry and robot geometry
* Intuition behind how the Minkowski sum is calculated - Imagine to paint the outside of an obstacle using a paintbrush that is shaped like your robot, with the robot’s origin as the tip of the paintbrush - The painted area is C<sub>obs</sub>
* For convex polygons, computing the convolution is trivial and can be done in linear time - however for non-convex polygons (i.e. ones with gaps or holes present), the computation is much more expensive - concave polygon - draw a segement between any two points that has a part of it lying outside the polygon - if covered by a convex polygon - done using quickhull algo -this can cause "ghost" collision - there is a gap but still shows collision 


## Graph Search

### Overview
- Uniformed algo - Searches blindly - no knowledge of the space its traversing or where the goal is maybe 
- Informed algo - 

### Terms
- Time complexity - How long it takes an algo to generate the path, usually with respect to the no of nodes or dimensions present - can also refer to the trade-off between quality of an algo vs its computation time
- Space complexity - Assess how much memory is required to execute the search
- Generality - Consider the type of problems that the algo can solve 

### Breadth-First Search

* Simplest type 
* BFS for short
* Searches the space broadly before it searches deeply
* In a tree, it searches horzontally(left to right) rather than going deep into a particular branch
* Traverses one level at a time
* How the algo break ties depends on implementation
* Uniformed search algo 
* Not efficient
* Complete - Optimal(coz it expands the shallowest(not deep) unexplored node with every step)
* Limited to graphs where all the steps costs are equal
* Frontier - Queue - First come first out

![BFS_tree](https://github.com/gonfreces/Udacity_Path_Planning_Navigation/blob/master/BFS_tree.png)
 
 ### Depth-First Search
 
 * Searches deep before it searches broadly
 * Goes from parent to child - when at the end - goes back to search the child of most recent parent 
 * Niether complete or optimal or efficient
 * DFS is not complete, because in an infinitely deep space, the algorithm would end up continuing to explore one branch indefinitely
 * DFS is not optimal, because it may find a longer path down one branch before it is able to see a shorter path on another branch
 * Frontier - Stack - Last in first out

![DFS_tree](https://github.com/gonfreces/Udacity_Path_Planning_Navigation/blob/master/DFS_tree.png)

### Uniform Cost Search

* Builds upon BFS to be able to search graph with differing edge costs
* Optimal - expands nodes in order of increasing path cost
* In certain environments, you can assign cost to every edge - cost may represent turn arounf corner or time delay
* Uniform cost search explores nodes on the frontier(place where nodes which are visible(neigbouring nodes) but not explored are placed) starting with the node having the lowest cost path
* Path cost - refers to the sum of all the edge cost leading from the start to that node
* Frontier - Priority Queue - Organized by path cost
* Uniform Cost Search is complete if every step cost is greater than some value, ϵ (otherwise, it can get stuck in infinite loops)
* No uninformed search algorithm can be particularly efficient. They always search in all directions, as they have no information to lead them in the direction of their goal

### A* Search 

* Informed search - takes into acoount information about the goal's location as it goes about its search - uses a heuristic function
* Heuristic function - *h(n)* - estimate of the distance of the node from the goal - as the only way to know the true distance is to traverse the path - helps steer the search in goal's direction - nodes cloes to the goal have lower heuristic value - goal = *h(n) = 0*
* No uninformed search algorithm can be particularly efficient. They always search in all directions, as they have no information to lead them in the direction of their goal
* Path cost - *g(n)* 
* A* chooses the path to minimize the sum of path cost and heuristic function - *f(n) = Summation of g(n)'s upto the explored node + Value of h(n) assigned to the explored node* - therefore searches for the shortest path in the direction of the goal
* Algo selects the node to explore (order it) based on the f(n) - Path with lowest *f(n)* will be explored first
* Frontier - Priority Queue 
* A* search - less steps to complete than Uniform cost search - coz of *h(n)*
* Conditions for optimality:
   * Every edge must have a cost value greater than the some value \epsilon, otherwise the search can get struck in infinite loops and the search would not be complete
   * The heuristic function must be consistent. This means that it must obey the triangle inqeuality theorem. 
   * Heuristic function must be admissible - means that h(n) must always be less than or equal to the true cost of reaching the goal from every node. In other words, h(n) must never overestimate the true path cost.??????
   * As you saw in the image above, admissibility is a requirement for A* to be optimal. For this reason, common heuristics include the Euclidean distance from a node to the goal (as you saw in the video), or in some applications the Manhattan distance. When comparing two different types of values - for instance, if the path cost is measured in hours, but the heuristic function is estimating distance - then you would need to determine a scaling parameter to be able to sum the two in a useful manner.
   * While A* is a much more efficient search in most situations, there will be environments where it will not outperform other search algorithms. This happens if the path to the goal happens to go in the opposite direction first.
   * Variants of A* search exist - some accommodate the use of A* search in dynamic environments, while others help A* become more manageable in large environments
   * [Path Finding Visualization](https://qiao.github.io/PathFinding.js/visual/)
   
   * Types of Heuristic vector:
      * x<sub>d</sub> =  x<sub>goal</sub> - x<sub>cellposition</sub>   
      * y<sub>d</sub> =  y<sub>goal</sub> - y<sub>cellposition</sub>
      * Manhattan distance = | x<sub>d</sub> | + | y<sub>d</sub> |
      * Euclidean distance = sqrt ( ( x<sub>d</sub><sup>2</sup> ) + ( y<sub>d</sub><sup>2</sup> ) )
      * Chebyshev distance  = max ( | x<sub>d</sub> |, | y<sub>d</sub> | ) 
      
## Sample-Based & Probabilistic Path Planning    

### Overview

* For 3D space or robotts with 6DOF, path planning using the above mentioned algorithms can be done but the efficiency of these algo's become more critical
* Performing complete discretization of the entire space and applying a graph search algorithm maybe too costly
* To tackle path planning problems of larger size and greater dimension - use sample based - algo randomly sample the complete space hoping the collection of samples will adequately represent the configuration space 

### Why Sample-Based planning

* Increased Dimensions
  * For a 2-dimensional 8-connected space, every node has 8 successors (8-connected means that from every cell you can move laterally or diagonally). Imagine a 3-dimensional 8-connected space, how many successors would every node have? 26. As the dimension of the C-space grows, the number of successors that every cell has increases substantially. In fact, for an n-dimensional space, it is equal to 3^n - 1 
* Constrained Dynamics
 * Aside from robots with many degrees of freedom and multi-robot systems, another computational difficulty involves working with robots that have constrained dynamics. For instance, a car is limited in its motion - it can move forward and backward, and it can turn with a limited turning radius
 
* Categories of robotic systems
  - Holonomic systems can be defined as systems where every constraint depends exclusively on the current pose and time, and not on any derivatives with respect to time. 
  - Nonholonomic systems, on the other hand, are dependent on derivatives. Path planning for nonholonomic systems is more difficult due to the added constraints.


