/**
 * Author: Simon Lindholm
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: Schedule N jobs on 2 machines to minimize completion time. 
 * i-th job takes ai and bi time to execute on 1st and 2nd machine, respectively. 
 * Each job must be first executed on the first machine, then on second. 
 * Both machines execute all jobs in the same order. 
 * solution -> sort jobs by key ai < bi ? ai : (oo-bi), i.e. first execute all jobs with ai < bi in order of increasing ai, then all other jobs in order of decreasing bi.
 * Status: tested
 */

