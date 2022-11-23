/**
 * Author: Simon Lindholm
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: Given N x N grid, each cell is either low or high land.
 * There are N trucks going straight from top to bottom and N truck
 * going straight from left to right.
 * Also a cost C is added if a truck hit a land from low to high or
 * high to low. We can also toggle the high of the cell and a cost D 
 * will be added. What is the minimum of total cost?
 * final position of f2N trucks should be at bottom and right. 
 * Solution is Connect every cell to its 
 * neighbor with capacity C. Connect every low cell to source with 
 * capacity D. Connect every high cell to sink with capacity D.
 * Status: tested
 */

