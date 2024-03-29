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
  - Nonholonomic systems, on the other hand, are dependent on derivatives. Path planning for nonholonomic systems is more difficult due to the added constraints
  
 ### Weaking Requirements
 
 * Combinatorial path planning are too inefficient to apply in high-dimensional environments, therefore compromise - weaken the requirements - complete and optimal
 * Instead of aiming for the algo to be complete, aim for it to be probablistically complete
 * *Probabilistically complete* = Probability of finding a path, if one exists increases to 1 as time goes to infinity
 * Requirement of optimal path to a feasible path
 * *Feasible path* = A path that obeys all the environmental and robot constraints such as obstacle and motion constraints
 * Finding a feasible path proves that a path from start to goal exists, and if needed, the path can be optimized locally to improve performance
 
 ### Sample-Based Planning
 
 * Unlike the combinatorial path planning, does not discretize the configuration space but rather samples it randomly(or semi-randmonly) to build up a representation of the space - resultant graph is not precise but much quicker because of the relatively small no of samples used 
 * Such a method is probabilistic beavuse as time passes, the no of samples reaches infintiy and the probability of finding a path, if it exists, approaches 1
 * Effective for high-dimensional space - but also not suitable for some places where the no of samples required is more than the rest and so it might fail at such problems
 * Two methods:
     * Probabilistic Roadmap
     * Rapidly Exploring Random Tree
     
 ### Probabilistic Roadmap (PRM)
 
 * Randomly samples the free space, building up the graph to represent the free space - without needing to construc the C space or discretize it
 * It does so by a collison check function - to check whether a randomly generated node lies in free space or is in collision with an obstacle
 * Two Phases:
    * Learning Phase
        * Process of building up a graph
        * Sampling random config and adding them to the graph
        * It does so by generating a new random config represented by a node in the graph and checking to see it its a collision 
        * If not the PR will try to connect it to neigbhours - two ways
            * PRM looks for any no of neigbhours within a certain radius of the node
            * Look for the node's K nearest neigbhours
         * Once the neigbhour has been selected - PRM will try to successfully create an edge to each of its neigbhours
         * The edges that collide with the obstacle are removed - to indentify this two ways - local planner must find a path between two nodes or return that such a path does not exists - has to be done quickly - so easy way - create a straight line between the nodes - place a no of evenly spaced samples - see whether any one of them is in a collision - 
            * incrementally work from one side to other side
            * binary approach - check midpoint - if not break the line into segments - try their midpoints for collision
            * If all samples return no collision, then the edge can be added to the graph
      * Eventually a certain criteria is met such as specific no of nodes or edges or a particular amt of time has elapsed - learning phase over 
      
    * Query Phase
        * Uses the resulting graph to find a path from start to goal
        * Connect the start and goal to the graph
        * PRM does so by looking for nodes closest to the start and goal and using local planner to build a connection
        * If this is successful - like A* applied - path may not be optimal but feasible
        
     * Parameters
        * No of iterations  
          * Conrols between how detailed the resultant graph is and how long the computation takes
          * Additional computation is not required in wide open spaces as additional detail is unlikely to improve the resultant path
          * Additional computation is required for complicated environments with narrow passages between obstacles
          * Beware, insufficient no of iterations can result in a 'path not found' if the samples inadequately reppresent the space
        * How to find neigbhours
           * One option - look for k-nearest neigbhors to a node
           * Efficient way - ![k-d] tree(https://xlinux.nist.gov/dads/HTML/kdtree.html) can be utilized -  to break up the space into 'bins' with nodes - search the bins for the nearest node
           * Other way - search for any nodes within a certain distance of the goal
           * Ultimately, knowledge of the environment and the solution requirements will drive this decision-making process
        * Local Planner
           * Choice needs to be made by robotics engineer
           * For most scenarios, the process of checking the edge for collision is repeated many times and efficiency is te key - but more powerful planners may be required in certain problems
           
     * ![A Comparative Study of Probabilistic Roadmap Planners](http://www.staff.science.uu.nl/~gerae101/pdf/compare.pdf)
     
     * The Learning Phase takes significantly longer to implement than the Query Phase, which only has to connect the start and goal nodes, and then search for a path. However, the graph created by the Learning Phase can be reused for many subsequent queries. For this reason, PRM is called a multi-query planner.
     
     * This is very beneficial in static or mildly-changing environments. However, some environments change so quickly that PRM’s multi-query property cannot be exploited. In such situations, PRM’s additional detail and computational slow nature is not appreciated. A quicker algorithm would be preferred - one that doesn’t spend time going in all directions without influence by the start and goal.
     
     * Psuedocode:
        * `Initialize an empty graph`
        *  `For n iterations:`
        *       `Generate a random configuration`
        *       `If the configuration is collision free:`
        *             `Add the  configuration to the graph`
        *             `Find the k nearest neighbours of the configuration`
        *             `For each of the k neighbours:`
        *                  `Try to find a collision-free path between`
        *                     `the neighbour and original configuration`
        *                     `If edge is collision-free:`
        *                         `Add it to the graph`
               
   ### Rapidly Exploring Random Tree   
   
   *  Psuedocode:
      * `Initialize two empty trees` // One from the start and one from the goal
      * `Add start node to trees #1` // This a variation where two trees are grown from start and goal node and tried to connect
      * `Add goal node to trees #2`
      * `For n iterations,or until an edge connects trees #1 or #2:`
      *     `Generate a random configuration (alternating trees)`
      *      `If the configuration is collision free:`
      *           `Find the closest neighbur on the tree to the configuration`
      *           `If the configuration is less than the distance delta away from the neighbour:`
      *                 `Try to connect the two with a local planner`
      *            `Else:` // So farther the node, more likely to be in collision with an obstacle so create a node in between
      *                  `Replace the randomly generated configuration`
      *                  `with a new configuration that falls along the same path` but a distance delts from the neighbour
      *                   `Try to connect the two with a local planner`
      *       `If node is added successfully:`
      *             `Try to connect the new node to the closest neighbour`
   *  Parameters
       *  Sampling method
          - Sample uniformly -favor unexplored areas
          - Sample with a bias - cause search to advance greedily towards goal - greediness can be beneficial in simple planning problems - common methods - but sometimes can cause the robot to get stuck in a local minima
       *  Delta
          - RRT will dictate the direction of growth
          - Delta is the growth rate
          - Small delta - large density of nodes - small growth rate
          - Large delta - lost detail - more nodes unable to connect due to greater chances of collisions with obstacles 
          - Choose carefully with knowledge of environment and requirement of solution
    * Single query planner
        * Explores the space starting with the start and the goal - therefore resultant graph cannot be applied to solve additional queries
        * Builds a new graph for each query - much smaller but more directed graph with faster computation time
    * RRT builds a tree, a type of graph where each node has only one parent 
    * PRM builds a graph
    * Very good for multidimensiional spaces
    
    * Advantages of RRT over PRM:
      * RRT is much quicker than PRM - takes into account the start and end nodes and limits the growth area surrounding the existing graph instead of reaching out into all distant corners, the way PRM does
      * RRT is more efficient than PRM at solving large path planning problems in dynamic environments
      * RRT supports planning for non-holonomic systems, while PRM does not - because RRT method can take into consideration the additional constraints(such as a car’s turning radius at a particular speed) when adding nodes to a graph, the same way it already takes into consideration how far away the new node is from the existing tree
      * RRT - Dynamic environments(changes quickly)
      * PRM - Static environments     
      
### Path Smoothing
  
* Psuedo Code:
   * `For n iterations`
   * `Select the two nodes from the graph`
   * `If the edge between the two nodes is shorter than the existing path between the nodes:`
   *        `Use local planner to see if edge collision-free.`
   *        `If collision-free:`
   *               `Replace existing path with edge between the two nodes`
    
* Path Shortcutter algorithm - can optimize for path smoothness, expected energy use or any other measurable factor
* After the Path Shortcutting algorithm is applied, the result is a more optimized path. It may still not be the optimal path, but it should have at the very least moved towards a local minimum. There exist more complex, informed algorithms that can improve the performance of the Path Shortcutter. These are able to use information about the workspace to better guide the algorithm to a more optimal solution
* To path plan in an environment such as the one presented above, alternate means of sampling can be introduced (such as Gaussian or Bridge sampling). Alternate methods bias their placement of samples to obstacle edges or vertices of the open space.
* ![Path Planning for Non-Circular Micro Aerial Vehicles in Constrained Environments](https://www.cs.cmu.edu/~maxim/files/pathplanforMAV_icra13.pdf)
* Anytime algorithm: an anytime algorithm is an algorithm that will return a solution even if it's computation is halted before it finishes searching the entire space. The longer the algorithm plans, the more optimal the solution will be.

* RRT*: RRT* is a variant of RRT that tries to smooth the tree branches at every step. It does so by looking to see whether a child node can be swapped with it's parent (or it's parent's parent, etc) to produce a more direct path. The result is a less zig-zaggy and more optimal path.

### Probabilistic Path Planning

* No path planning algo uptil now has modeled/considered risk and uncertainty of robot motion
* Need - Model the uncertainty the by considering a non-deterministic transition model - in some cases path execution is uncertain, an algorithm that takes the uncertainty into account explicitly is more likely to produce realistic paths - leads to Markov Decision processes
* Non-deterministic model = One-step dynamics - Means action cannot guarantee to lead a robot from one state to another state. Instead, there is a probability associated with resulting in each state

#### Markov Decision Process
* A Markov Decision Process is defined by:
   * A set of states *S*
   * Initial state *s<sub>o<sub>*
   * A set of actions *A*
   * The transition model *T(s,a,s')* - Probability of reaching state *s'* from state *s* by executing action *a*
   * A set of rewards *R*
* The Markov assumption states that the probability of transitioning from state *s* to *s'* is only dependent on the present state *s* and not on the path taken to get to *s'* 
 * One notable difference between MDPs in probabilistic path planning and MDPs in reinforcement learning, is that in path planning the robot is fully aware of all of the items listed above (state, actions, transition model, rewards). Whereas in RL, the robot was aware of its state and what actions it had available, but it was not aware of the rewards or the transition mode 
 * Movement actions are non-deterministic
 * Every action will have a probability less than 1 of being successfully executed. This can be due to a number of reasons such as wheel slip, internal errors, difficult terrain, etc
 * In each state (cell), the robot will receive a certain reward, R(s)R(s). This reward could be positive or negative, but it cannot be infinite. It is common to provide the following rewards,

      * small negative rewards to states that are not the goal state(s) - to represent the cost of time passing (a slow moving robot would incur a greater penalty than a speedy robot),
      * large positive rewards for the goal state(s), and
      * large negative rewards for hazardous states - in hopes of convincing the robot to avoid them.
* These rewards will help guide the rover to a path that is efficient, but also safe - taking into account the uncertainty of the rover’s motion.
* With the robot’s transition model identified and appropriate rewards assigned to all areas of the environment, we can now construct a policy.

#### Policy

* Solution to a Markov Decision Process is a policy - Denoted by pi
* Policy is a mapping from states to actions
* For every state, a policy will inform the robot of which action it should take
* An optimal policy is denoted by pi* -  informs the robot of the best action to take from any state, to maximise the overall reward

#### State Utility

* Represents how attractive the state is wrt the goal
* For each state, the state value function yields the expected return if the robot starts in that state and then follows the policy for all time steps
* Mathematical Notation: U<sup>π</sup>(s) = E [∑<sup>∞</sup><sub>t=0</sub>R(s<sub>t</sub>)∣π,s<sub>0</sub>=s]
* U<sup>π</sup>(s) represents the utility of a state *s*
* E represents the expected value
* R(s) represents the reward for state s
* The utility of a state is the sum of the rewards that an agent would encounter if it started at that state and followed the policy to the goal
* The expected reward for the first state is independent of the policy. While the expected reward of all future states (those between the state and the goal) depend on the policy.
* Equation tranforms to : U<sup>π</sup>(s) = R<sub>t</sub> + U<sup>π</sup>(s')
* Thus utiltiy of the state is an iterative process
* Optimal Policy: π<sup>*</sup>(s) = argmax E[U<sup>π</sup>(s)]
* In a state ss, the optimal policy \pi^*π 
∗ In a state ss, the optimal policy \pi^*π 
∗ In a state s, optimal policy will choose the action a that maximizes the utility of s (which, due to its iterative nature, maximizes the utilities of all future states too).

#### Value Iteration Algorithm

* Psuedo Code
* U' = 0
* loop until close enough (U,U')
* U = U'
* for s in S, do:
*      U(s)=R(s)+γmax Σ s,a,s )U(s)
* return U

* With every iteration, the algorithm will have a more and more accurate estimate of each state’s utility. The number of iterations of the algorithm is dictated by a function \textit{close-enough}close-enough which detects convergence. One way to accomplish this is to evaluate the root mean square error,

RMS = \frac{1}{|S|} \sqrt{\sum_{s}(U(s) - U'(s))^2}RMS= ∣
1
​	  
s
∑
​	 (U(s)−U 
′
 (s)) 
2
 
​	 

Once this error is below a predetermined threshold, the result has converged sufficiently.

RMS(U,U') < \epsilonRMS(U,U 
′
 )<ϵ

This algorithm finds the optimal policy to the MDP, regardless of what U'U 
′
  is initialized to (although the efficiency of the algorithm will be affected by a poor U'U 
′
 ).
               
               
       
       
     
          
        
           

