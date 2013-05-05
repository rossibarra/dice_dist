#include <Sequence/SimData.hpp>
#include <cstdio>

namespace Sequence {
	class SimDataDIP : public Sequence::SimData    {
   	private:
      	unsigned totsam;

    	public:
      	virtual int fromfile( FILE * openedfile );
      	SimDataDIP();
 	};
}
