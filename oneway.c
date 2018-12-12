/*
 **********************************************
 *  CS314 Principles of Programming Languages *
 *  Fall 2018                                 *
 *  File: oneway.c                            *
 *  Date: 11/25/2018                          *
 **********************************************
 */
#include "oneway.h"
#include "utils.h"

void extend_one_hand(int threadId, int threadNum, GraphData graph,
                     int nodeNum, int *nodeToProcess,
                     int *res, int *strongNeighbor)
{
    /* Your Code Goes Here */
	//printf("%d \n",strongNeighbor[2]);
	int i = threadId;
	int wc = (nodeNum + threadNum - 1) / threadNum;
	int beg = i * wc;
	int end;
	if( (beg+wc) < nodeNum){
		end = beg+wc;
	}else{
		end = nodeNum;
	}
	// end = min(beg + wc, nodeNum);

	//end = beg +5; testing done
	for(i=beg; i<end; i++){  //go through assigned vertices from nodetoprocess
		int idx = nodeToProcess[i];
		int degree = graph.degree[idx];
		int offset = graph.offset[idx];
		int poff = offset;
		int idx2 =0;
		int str;

		for(idx2 = 0; idx2 < degree;idx2++){
			str = graph.index[offset];
			offset++;
			if(res[str] == UNMATCHED){

				strongNeighbor[i] = str;
				idx2 =degree+1; // break loop
			}

		}

		//printf("%d %d %d %d %d %d %lf\n",idx, degree,poff,str,strongNeighbor[i],graph.index[0], graph.weight[0]);

	}



	//printf("%d \n",strongNeighbor[0]);

}

void check_handshaking(int threadId, int threadNum,
                       int nodeNum, int *nodeToProcess,
                       int *strongNeighbor, int *res)
{
    /* Your Code Goes Here */

	int i = threadId;
	int wc = (nodeNum + threadNum - 1) / threadNum;
	int beg = i * wc;
	int end;
	if( (beg+wc) < nodeNum){
		end = beg+wc;
	}else{
		end = nodeNum;
	}

	int idx;
	int str;
	for(i=beg; i<end; i++){
		idx = nodeToProcess[i];
		str = strongNeighbor[idx];
		if(strongNeighbor[str] == idx){ // match
		//	printf("%d %d %d %d\n",str,idx, strongNeighbor[str],strongNeighbor[idx]);
			res[idx] = str;
		}
	}



}


