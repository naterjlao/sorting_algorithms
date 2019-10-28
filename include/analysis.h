#ifndef ANALYSIS_H
#define ANALYSIS_H

#define ANALYSIS 0

#if ANALYSIS
#define COMPARE() ncompares++
#define SWAP() nmoves++
#define ANALYZE() printf("number of comparisons: %d number of moves: %d\n",ncompares,nmoves);\
	ncompares = 0;\
	nmoves = 0
#else
#define COMPARE()
#define SWAP()
#define ANALYZE()
#endif

#endif

