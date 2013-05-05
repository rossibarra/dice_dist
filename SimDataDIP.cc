#include <SimDataDIP.hpp>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


namespace Sequence {

	SimDataDIP::SimDataDIP(): SimData() {}

	std::ostringstream is;
	int SimDataDIP::fromfile( FILE * openedfile ){
		char ch; 				
		int rv; //return value from fscanf   	
		while(1)	{
			rv = fscanf(openedfile,"%c",&ch);
			if (rv == EOF) return rv;	
			if ( ch=='/') {
				int token;
				float tempval;
				bool done = false;
		
				while (! done)	{
					token = fgetc(openedfile);
					if (  (!isspace(token)) && char(token) != '\n' && char(token) != '/' ) {
						ungetc(token,openedfile);
						fscanf(openedfile,"%f",&tempval);                
						is << tempval << ' ';
					}
					else if ( char(token) == '\n' ){
						done = true;
					}
				}
			}	
			
			if (ch == ':') break;
		}
		unsigned ss;
		rv = fscanf(openedfile,"%u",&ss);
		if (rv == EOF) return rv;
	
		std::vector<double> _positions;
		std::vector<std::string> _data;
				
		if (ss > 0) {
			_positions.resize(ss);
			
			while(1){
				rv=fscanf(openedfile,"%c",&ch);
				if (rv == EOF) return rv;	    
				if (ch == ':') break;
			}
			for (unsigned i = 0; i < ss; ++i){
				rv=fscanf(openedfile,"%lf",&_positions[i]);
				if (rv == EOF) return rv;
			}
			char *seq = new char[ss+2];
			int countdip=0;
			char *gentype = new char[ss+2];

			while(1) {
				rv=fscanf(openedfile,"%s",seq);
				
				if (rv == EOF) {
					rv=1;
					break;
				}
				else if ( strcmp(seq,"//") == 0) { 		
					int token;
					float tempval;
					bool done = false;
	
					while (! done) {
						token = fgetc(openedfile);
						if (  (!isspace(token)) && char(token) != '\n' && char(token) != '/' ) {
							ungetc(token,openedfile);
							fscanf(openedfile,"%f",&tempval);                
							is << tempval << ' ';
						}
						else if ( char(token) == '\n' ){
							done = true;
						}
					}
					break;
				}
				else {
					countdip++; 
					if(countdip==1){ strcpy(gentype, seq); } // printf("hap: %s\n",seq); }
					// turn the string of sites at each individual into separate chars
					// then into ints.  add, and determined dominance genotype
					if(countdip==2){
						for(unsigned i=0; seq[i]!='\0'; i++){ 
							gentype[i] |=seq[i];
						}
						//	printf("hap: %s\n",seq);
						//	printf("dip: %s\n",gentype);

						_data.push_back( std::string(gentype) ); 
						countdip=0;		
					}			
					//printf("\n");
				}
			}
			delete [] seq; delete [] gentype;
		}
		else if (ss == 0){
			_positions.resize(0);
			
			char *seq = new char[ss+2];
			while(1) {
				rv=fscanf(openedfile,"%s",seq);
				if (rv == EOF) {
					rv=1;
					break;
				}
				if ( strcmp(seq,"//") == 0) { 		
					int token;
					float tempval;
					bool done = false;
	
					while (! done) {
						token = fgetc(openedfile);
						if (  (!isspace(token)) && char(token) != '\n' && char(token) != '/' ) {
							ungetc(token,openedfile);
							fscanf(openedfile,"%f",&tempval);                
							is << tempval << ' ';
						}
						else if ( char(token) == '\n' ){
							done = true;
						}
					}
					break;
				}
			}
			delete [] seq;
			_data.resize(0);
		}
		//assign data into base class
		PolyTable::assign(&_positions[0],ss,&_data[0],_data.size());
		return rv;
	}
}
