#include "ClosestPair.h"
#include "DivideAndConquer.h"
#include "BruteForce.h"
#include "timing.h"

void correctness();
void timing();
void stress();

int main(){
	

	//stress();    //一百万
	//correctness(); //检查正确性
	timing();      //比较两种方案用时


	return system("pause");
}


void stress(){
	Timing timer;
	timer.start();
	Result r = DivideAndConquer().solve(createProblem(1e6));
	cout << r;
	timer.end();
	timer.reportCPUtime();
}


void correctness(){

	const int N = 100;
	int PROBLEM_SIZE = 2;
for(; PROBLEM_SIZE < 1e8; PROBLEM_SIZE *= 2){
	cout << endl << "Problem size " << PROBLEM_SIZE << endl;
	int wrong = 0;

	Result r1, r2;

	for(int i=0; i<N; i++){

		Points problem;
		problem = createProblem(PROBLEM_SIZE);
		r1 = DivideAndConquer().solve(problem);
		r2 = BruteForce().solve(problem);

		if(r1 == r2)
			;
		else{
			cout << "Sample #" << i << endl;
			cout << "DC: " << r1 << "BF: " << r2 ;
			wrong ++;
		}

	}
	cout << N << " samples, " << wrong << " of which may be wrong." << endl;
}

}

void timing(){
	int TIMES;
	int problemSize = 2;
for(; problemSize<2e6; problemSize*=2){
	if(problemSize < 10)
		TIMES = 100000;
	else if(problemSize < 1000)
		TIMES = 1000;
	else if(problemSize < 10000)
		TIMES = 10;
	else
		TIMES = 1;
	Timing timer;
	timer.setDivisor(TIMES);

	Points problem;
	


	Result r;


	timer.start();
	for(int i=0; i<TIMES; i++){
		problem = createProblem(problemSize);
		r = DivideAndConquer().solve(problem);
	}
	timer.end();
	cout << problemSize << '\t' << timer.getCPUtime();

	static bool flag = false;
	
	timer.start();
	for(int i=0; i<TIMES; i++){
		problem = createProblem(problemSize);
		r = BruteForce().solve(problem);
	}
	timer.end();
	cout << '\t' << timer.getCPUtime();

	cout << '\n';
}
}

