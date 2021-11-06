/**
 * Author: Simon Lindholm
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: Consider a bipartite graph where the vertices are partitioned into left (L) and right (R) sets. 
 * Suppose there is a maximum matching which partitions the edges into those used in the matching (Em) and those not (E0). 
 * Let T consist of all unmatched vertices from L, as well as all vertices reachable from those (starting from vertices of T ) 
 * by going left-to-right along edges from E0 and right-to-left along edges from Em . 
 * This essentially means that for each unmatched vertex in L, we add into T all vertices that occur in a path alternating between edges from E0 and Em. 
 * minimum vertex cover : vertices in T are added if they are in R and subtracted if they are in L to obtain the minimum vertex cover.
 * There is a code above.
 * Status: tested
 */

#include <MinimumVertexCover.h>
