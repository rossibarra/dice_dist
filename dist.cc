
#include <iostream>
#include <vector>
#include <cstdio>
#include <numeric>
#include <utility>
#include <Sequence/SimParams.hpp>
#include <SimDataDIP.hpp>
#include <Sequence/PolySIM.hpp>
#include <Sequence/SeqConstants.hpp>
#include <Sequence/PolyTableFunctions.hpp>


using namespace std;
using namespace Sequence;

void dist(const SimDataDIP & d, const unsigned & mincount, const int popsize);

int main(int argc, char *argv[]) {
	std::vector<int> config;
	bool multipop = false;
	int mincount = 1;
	for(int arg = 1 ; arg < argc ; ++arg){
		if( string(argv[arg]) == "-I" ){
			multipop = true;
			int npop = atoi(argv[++arg]);
			for( int i=0;i<npop;++i ){
				config.push_back(atoi(argv[++arg]));
			}
		}
		else if (string(argv[arg]) == "-m"){
			mincount = atoi(argv[++arg]);
		}
	}
	int total = std::accumulate(config.begin(),config.end(),0,plus<int>());
	SimParams p;
	p.fromfile(stdin);
	SimDataDIP d;

	#if __GNUG__ && __GNUC__ >= 3
	std::ios_base::sync_with_stdio(true);
	#endif
// 	if(multipop){
// 		std::cout << "rep\tpop\n";
// 	}

	int rv;
	int rep=0;

	while( (rv=d.fromfile(stdin)) != EOF ){
		SimDataDIP d2;
		if(d.size() != total){
			std::cerr << "oh crap\n";
			exit(10);
		}
		int sum = 0;
		for(int i = 0 ; i < config.size() ; ++i){
			d2.assign(&*d.pbegin(),d.numsites(),&d[sum],config[i]);
			int popsize=config[i];
			sum += config[i];
			RemoveInvariantColumns(&d2);
//			cout << rep << '\t' << i << '\n';
			dist(d2,mincount,popsize);
		}
		++rep;
	} 
}

void dist(const SimDataDIP & d, const unsigned & mincount, const int popsize){

	PolySIM P(&d);
	cout << " " << popsize << "\n";
	for( int i=0; i<popsize-1; i++){
		cout << i << "        \t"; 
		for( int j=0; j<popsize-1; j++){
			if( j<i ){ cout << "\t"; }
			else{
				double a=0; double b=0; double c=0;
				for( int s=0; s<d.numsites(); s++){
					if( d[i][s]=='1' && d[j][s]=='1' ){ a++; }
					if( d[i][s]=='1' && d[j][s]=='0' ){ b++; }
					if( d[i][s]=='0' && d[j][s]=='1' ){ c++; }
					//cout << i << " " << j << " " << d[i][s] << ' ' << d[j][s] << ' ' << a << ' ' << b <<' ' << c << '\n';
	
				}
				double dice;
				if( a==0 && b==0 && c ==0 ){ dice=0; }
				else{ dice = (2*a)/(2*a+b+c); }
				/*for( int s=0; s<d.numsites(); s++){
					cout << d[i][s];
				}
				cout << endl;
				for( int s=0; s<d.numsites(); s++){
					cout << d[j][s];
				} */
				cout << 1-dice << '\t';
			}
			//cout << endl << i << " " << j << " " << dice << "\n";
		}
		cout << endl;
	}
	cout << popsize-1 << "          \n"; 
}
