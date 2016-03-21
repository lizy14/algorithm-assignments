/*
Zhaoyang Li, THSS, March 2016
*/



#pragma once

#include <vector>
#include <string>

using std::string;
using std::vector;

enum Operation{
	COPY,
	REPLACE,
	DELETE,
	INSERT,
	TWIDDLE,
	KILL
};

#define NUMBER_OF_OPERATIONS 6

typedef vector<Operation> Operations;


typedef int Cost;
class Costs : public vector<Cost>{
public:
	Costs(){
		resize(NUMBER_OF_OPERATIONS, 10);
	}
	/*
	assuming that the individual costs of
	the copy and replace operations 
	are less than the combined costs of 
	the delete and insert operations.
	*/
};

class EditDistance
{
private:
	string a, b;
	int n, m;
	Costs w;
	vector<vector<Cost> > d;
	vector<vector<Operations> > o;
public:

	EditDistance(const string& src, const string& dst, const Costs& c){
		w = c;
		b = src; m = b.length();
		a = dst; n = a.length();
	}
	void solve(){
		
		d.resize(m+1, vector<Cost>(n+1, -1)); // an (m+1) x (n+1) matrix
		o.resize(m+1, vector<Operations>(n+1)); // an (m+1) x (n+1) matrix
		
		
		//bottom-up dynamic programming
		
		d[0][0] = 0;

		for(int i=1; i<=m; i++){
			d[i][0] = i * w[DELETE];
		}
		for(int j=1; j<=n; j++){
			d[0][j] = j * w[INSERT];
		}
		for(int j=1; j<=n; j++){
			for(int i=1; i<=m; i++){

				//i over b, j over a

				d[i][j] = d[i][j-1] + w[INSERT];
				o[i][j] = o[i][j-1]; o[i][j].push_back(INSERT);


				if(b[i-1] == a[j-1]){
					update(i, j, i-1, j-1, COPY);
				}
				if(j>=2 && i>=2 && (b[i-1]==a[j-2]) && (b[i-2]==a[j-1])){
					update(i, j, i-2, j-2, TWIDDLE);
				}
				if(i==m){
					update(i, j, i, j, KILL);
				}

				update(i, j, i-1, j-1, REPLACE);
				update(i, j, i-1, j, DELETE);
				
			}
		}
	}
	void update(int i, int j, int ii, int jj, Operation op){
		auto _ = d[ii][jj] + w[op];
		if(_ < d[i][j] || d[i][j] < 0){
			d[i][j] = _;
			o[i][j] = o[ii][jj]; 
			o[i][j].push_back(op);
		}
	}
	Cost _min(Cost a, Cost b){
		return a<b? a: b;
	}
	Operations getOperations(){
		return o[m][n];
	}
	string getOperationsString(){
		string txt[] = {
			"COPY   ", 
			"REPLACE", 
			"DELETE ", 
			"INSERT ", 
			"TWIDDLE", 
			"KILL   "
		};
		string r = "Operations: \n";
		auto ops = getOperations();
		for(auto op : ops){
			r += (txt[op]);
			r += "\n";
		}
		return r;
	}
	Cost getCost(){
		return d[m][n];
	}
};
