#include "djikstra.h"

bool outOfBounds(int x, int y, int z)
{
    //If any of these conditions are met, then we fail
    return (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y || z < 0 || z >= MAX_Z); //current element compared to map size
}

void drawStates(Node node[MAX_Z][MAX_Y][MAX_X])
{
    std::cout << '\n';
    for (int z = 0; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                if (node[z][y][x].state == 0)
                {
                    std::cout << ".";
                }
                else
                {
                    std::cout << node[z][y][x].state;
                }
            }
            std::cout << '\n';
        }
        std::cout << "\n\n";
    }
}

void evaluteAdjacent(Node (*node)[MAX_Y][MAX_X],Coord currentNode) //Graph,currentNode
{
    node[currentNode.z][currentNode.y][currentNode.x].state = 1; //close the current node
    int gValue = 0; //Are we moving diagonally or not? If yes, the value is 14, otherwise 10
    int z = 0; //z only used on stairs
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 || y == 0)   //If we're moving non-diagonally
                gValue = 10;
            else
                gValue = 14;
            if ((y == 0) && (x == 0) && (z==0))
            {
                //nothing
            }
            else if (!outOfBounds(currentNode.x+x,currentNode.y+y,currentNode.z+z))  //If the element is not out of bounds
            {
                if ((node[currentNode.z+z][currentNode.y+y][currentNode.x+x].state == 0))    //setundefined node
                {
                    //...then evalute it, or re-evaluate it
                    node[currentNode.z+z][currentNode.y+y][currentNode.x+x].state = 2;    //Make it available as an open node first
                    node[currentNode.z+z][currentNode.y+y][currentNode.x+x].gCost = node[currentNode.z][currentNode.y][currentNode.x].gCost + gValue; //Adjacent node gCost = oldGCost + distance to old current
                    //Link to old node
                    //node[currentNode.y+y][currentNode.x+x].prev = &node[currentNode.y][currentNode.x];
                }
                else if ((node[currentNode.z+z][currentNode.y+y][currentNode.x+x].state == 2))    //reevalute...
                {
                    if (node[currentNode.z+z][currentNode.y+y][currentNode.x+x].gCost > node[currentNode.z][currentNode.y][currentNode.x].gCost + gValue)   //...if changing it would give a better value...
                    {
                        node[currentNode.z+z][currentNode.y+y][currentNode.x+x].gCost = node[currentNode.z][currentNode.y][currentNode.x].gCost + gValue;
                        //Pointer to old node
                        //node[currentNode.y+y][currentNode.x+x].prev = &node[currentNode.y][currentNode.x];

                    }
                    //...Otherwise just exit.
                }
            }
            //std::cout << "bean" << std::endl;
        }
    }
    //Do cases for stairs here.
    if (board[currentNode.z][currentNode.y][currentNode.x] == 2
        || (!outOfBounds(currentNode.z,currentNode.y,currentNode.z-1)
        && board[currentNode.z-1][currentNode.y][currentNode.x] == 2)) //Check if the map tile is a staircase
    {

        //Up
        if (!outOfBounds(currentNode.x,currentNode.y,currentNode.z+1))
        {
            if (node[currentNode.z+1][currentNode.y][currentNode.x].state == 0) //Node not evaluated
            {
                node[currentNode.z+1][currentNode.y][currentNode.x].state = 2;
                node[currentNode.z+1][currentNode.y][currentNode.x].gCost = node[currentNode.z][currentNode.y][currentNode.x].gCost + 10;
            }
            else if (node[currentNode.z+1][currentNode.y][currentNode.x].state == 2) //Node has already been evaluated
            {
                if (node[currentNode.z+1][currentNode.y][currentNode.x].gCost > node[currentNode.z][currentNode.y][currentNode.x].gCost + 10)   //...if changing it would give a better value...
                {
                    node[currentNode.z+1][currentNode.y][currentNode.x].gCost = node[currentNode.z][currentNode.y][currentNode.x].gCost + 10;
                }
            }
        }
        //Down
        if(!outOfBounds(currentNode.x,currentNode.y,currentNode.z-1))
        {
            if  (node[currentNode.z-1][currentNode.y][currentNode.x].state == 0) //Node not evaluated
            {
                node[currentNode.z-1][currentNode.y][currentNode.x].state = 2;
                node[currentNode.z-1][currentNode.y][currentNode.x].gCost = node[currentNode.z][currentNode.y][currentNode.x].gCost + 10;
            }
            else if (node[currentNode.z-1][currentNode.y][currentNode.x].state == 2) //Node has already been evaluated
            {
                node[currentNode.z-1][currentNode.y][currentNode.x].gCost = node[currentNode.z][currentNode.y][currentNode.x].gCost + 10;
            }
        }
    }


    //drawStates(node);
}

void selectBestNode(Node node[MAX_Z][MAX_Y][MAX_X], Coord * currentNode)
{
    Coord bestNode;
    bestNode.x = MAX_X; //Non-reachable value
    bestNode.y = MAX_Y; //Non-reachable value
    bestNode.z = MAX_Z; //Non-reachable value'
    for (int z =0 ; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                if(bestNode.x == MAX_X && bestNode.y == MAX_Y && bestNode.z == MAX_Z && node[z][y][x].state == 2) //If there is no best value yet...
                {
                    //...we do this so we can actually compare the next node. Otherwise we'd be comparing the default (wrong) node!
                    bestNode.x = x;
                    bestNode.y = y;
                    bestNode.z = z;
                }
                //If open and less gCost than current best
                else if ((node[z][y][x].state == 2)  && (node[z][y][x].gCost) < (node[bestNode.z][bestNode.y][bestNode.x].gCost))
                {
                    bestNode.x = x;
                    bestNode.y = y;
                    bestNode.z = z;
                }
            }
        }
    }
    //The best node will be the next currentNode
    currentNode->x = bestNode.x;
    currentNode->y = bestNode.y;
    currentNode->z = bestNode.z;
    return;
}

void setUp(Node * node)
{
    for (int z = 0 ; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                if (board[z][y][x] == 1)
                {
                    (node+((z*MAX_Y*MAX_X)+(y*MAX_X)+x))->state = 1;  //blokd
                }
                else
                {
                    (node+((z*MAX_Y*MAX_X)+(y*MAX_X)+x))->state = 0;  //ready
                }
            }
        }
    }
    return;
}

int djikstra(int x2, int y2, int z2 , int x1, int y1, int z1, int getMap[MAX_Z][MAX_Y][MAX_X])
{
    for (int x = 0; x < MAX_X; x++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int z = 0; z < MAX_Z; z++)
            {
                board[z][y][x] = getMap[z][y][x];
            }
        }
    }
    Node node[MAX_Z][MAX_Y][MAX_X];    //All the nodes
    setUp(&node[0][0][0]);
    node[z1][y1][x1].gCost = 0; //Start point starts with no cost
    Coord currentNode;
    currentNode.x = x1;
    currentNode.y = y1;
    currentNode.z = z1;
    drawStates(node);
    while(true)
    {
        evaluteAdjacent(node,currentNode);
        drawStates(node);
        selectBestNode(node,&currentNode);
        if(currentNode.x == MAX_X && currentNode.y == MAX_Y && currentNode.z == MAX_Z) //Didn't work out: No path.
        {
            std::cout << "No path" << std::endl;
            return 10; //No path magic number
        }
        std::cout << currentNode.x << std::endl;
        std::cout << currentNode.y << std::endl;
        std::cout << currentNode.z << std::endl;
        std::cout << node[currentNode.z][currentNode.y][currentNode.x].gCost << std::endl;
        //If we find the end node.
        //if (currentNode.y == y2 && currentNode.x == x2)
        //{
        for (int y = -1; y <= 1; y++)
        {
            for (int x = -1; x <= 1; x++)
            {
                //Check for the up/down pathfinding stuff
                if (x == 0 && y == 0)
                {
                    if (!outOfBounds(currentNode.x,currentNode.y,currentNode.z+1) && currentNode.z+1 == z2 && currentNode.y == y2 && currentNode.x == x2)
                    {
                        std::cout << "going down" << std::endl;
                        return 8; //going up
                    }
                    if (!outOfBounds(currentNode.x,currentNode.y,currentNode.z-1) && currentNode.z-1 == z2 && currentNode.y == y2 && currentNode.x == x2)
                    {
                        std::cout << "going up" << std::endl;
                        return 9; //going down
                    }
                    //nothing
                }
                else if (currentNode.z == z2 && currentNode.y+y == y2 && currentNode.x+x == x2)
                {
                    //Return the movement value
                    std::cout << textCheck[y+1][x+1] << std::endl;
                    return moveCheck[y+1][x+1];
                }
            }
        }
            //return Coord(0,0);
        //}
    }
}
