# Runway Rush
After a well-deserved and relaxing vacation, the CS department is finally at the airport, ready to catch their plane
to go back to Torino and continue working on Fortuna. Everything seems to be going according to plan, oddly enough...  
Wait! Where's Tom?! Oh no, it seems Tom didn't wake up, and is late, again! Luckily, anticipating this exact situation,
Stefano put in place a system to monitor the area between the airport and the hotel and to produce a map, in the shape
of a matrix, where every number represents the time needed to traverse a specific zone. Can you help Tom make it in time
by finding the shortest path to get to the airport?

## Instructions
You are provided with the file `runwayRush.cpp`, containing the function to generate the map, which is written to a .txt
file as a matrix of positive integers, and a general structure to follow. 
In the generated map, the starting point is always the top-left square, and the destination is always the bottom-right
square, both marked with a '0'. From each square, you are only allowed to move down or right. Implement the function 
`findShortestPath()`, which must find the shortest path between the starting point and the destination, where the shortest
path is defined as the one that minimizes the sum of the values of the squares making it up, print the sequence of moves making up 
said path, marking the moves with 'r' for right moves and 'd' for down moves, separated by spaces, and return the total traversal time of the found route.
You are free to define and use other functions, if deemed necessary. You aren't allowed to delete or otherwise modify the
provided code (except the findShortestPath() prototype and call, in which you can add parameters), but you may, 
if necessary, add statements in between the pre-written lines in the main
function. You can assume the input file is correct. In case of a tie, any shortest path is a valid output.

## Expected outputs
Provide the completed version of `runwayRush.cpp`.

## Challenge's score
Total score: 500