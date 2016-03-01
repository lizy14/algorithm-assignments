#include "ClosestPair.h"
#include "DivideAndConquer.h"
#include "BruteForce.h"
#include "timing.h"

void correctness_check();
void timing();

int main(){
	//correctness_check();
	timing();
	return system("pause");
}

void correctness_check(){

	const int N = 100;
	const int PROBLEM_SIZE = 233;

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
			wrong ++;
		}

	}
	cout << N << " samples, " << wrong << " of which wrong." << endl;

}

void timing(){
	const int TIMES = 10;
	int problemSize = 23333;

	Timing timer;
	timer.setDivisor(TIMES);

	Points problem;
	problem = createProblem(problemSize);


	Result r;


	timer.start();
	for(int i=0; i<TIMES; i++){
		r = DivideAndConquer().solve(problem);
	}
	timer.end();
	cout << "DC " << r;
	timer.reportCPUtime();

	timer.start();
	for(int i=0; i<TIMES; i++){
		r = BruteForce().solve(problem);
	}
	timer.end();
	cout << "BF " << r;
	timer.reportCPUtime();

}

