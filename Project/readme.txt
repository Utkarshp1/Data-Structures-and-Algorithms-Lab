For storage of different trees structure has been used.
Price= p*h*d; weight= c*p*h; 
profit= price+ profit earned by domino effect i.e. price of other tree that fall due to domino effect
direc stores the direction in which the tree should be cut so as to get the max profit

vector v stores the information of all the tree
c_x and c_y stores the information about the current x,y coordinates i.e. the coordinates of the most recently cut tree
n_x and n_y stores the coordinates of the next tree that has to be cut

t is the time that has been given to us cut the tree(not the execution time of the program)
n represents the size of the grid
k represents the number of trees

calculate_profit() function
---------------------------
This function calculates the direction in which the profit is maximum and updates the profit of each tree in that direction

cutup_profit() function
-----------------------
This function first finds the nearest neighbour of the given tree(in the up direction) 
and then checks whether that tree can have a domino effect or not. Then it makes a recursive
call to find that whether the next nearest neighbour of the given tree(in the up direction)
can participate in the domino effect.
The function returns the extra-profit that can made by when the tree is cut in the up-direction
due to the domino effect.

Similar tasks are performed by cutright_profit(), cutdown_profit() and cutdown_profit() functions.

------------------------
Till this step we would have determined the best direction and profit that we can get while cutting 
the tree is cut in the best direction.

-------------------------
Now coming back to the main function

path() function
---------------
This function first computes the cost of cutting a tree i.e. the cost of reaching to that
tree plus the diameter of the tree. If this cost is less than the time left with us then 
it calculates the profit/time for that tree. Then it finds the maximum of this quantity among 
all the trees and the next tree to be cut will be the tree which has the maximum of this quantity.
----------------

Now coming back to the main function

printPath() function
--------------------
This function simply prints the path that is to be followed to reach a tree.

Now the consecutive if conditions prints the direction in which tree will be cut. The 
corresponding cut functions have been called because it gives us the updated list of 
which trees will be cut using domino effect.
Now from the time which has been given to us to cut the tree, we deduct the diameter of
the tree to be cut. Then the trees which will be cut using the domino effect will be 
removed from our database. Then the tree itself will be removed from our database. Then
the current coordinates will be equal to the next coordinates.
 