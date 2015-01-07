#include <vector>
#include "common.h"

// Three Templated Classes...

//CyclicIter Class...
template <typename Tcont>
class CyclicIter
{
public:
	CyclicIter()
		:cont(NULL)
	{}
	void Init(Tcont * containerPtr)
	{
		cont = containerPtr;
		iter = cont->begin();
	}
	typename Tcont::iterator PeekNow()			{return iter; }
	typename Tcont::iterator PeekNext()
	{
		if (iter+1 == cont->end()) return cont->begin();
		else return iter+1;
	}
	void StepOn()
	{
		iter++;
		if (iter == cont->end()) iter = cont->begin();
	}
private:
	Tcont * cont;
	typename Tcont::iterator iter;
};

//DataPoint Class...
template <typename T>
class DataPoint
{
public:
	DataPoint(void) {}
	~DataPoint(void) {}
	unsigned int time;
	T value;
	bool mustBlend;
	T blend;
};


//BOX
//    ASPECT[] aspects
//        DATA actual
//        CYCLICITER ri
//        LIST[DATAPOINT_1A] route
//            int time,
//            DATA value,
//            enum fade,
//            DATA blend,

//Aspect Class...
template <typename T>
class Aspect
{
public:
	Aspect(void) {}
	~Aspect(void) {}
	void UpdateActual(unsigned int gc)
	{
		if (gc == cIter.PeekNext()->time)
		{
			cIter.StepOn();
			actual = cIter.PeekNow()->value;
		}
		else {
			if (cIter.PeekNow()->mustBlend == true)
			{
				actual = ApplyBlend(cIter.PeekNow()->value, cIter.PeekNow()->blend, gc - cIter.PeekNow()->time);
			}
		}
	}
	T GetActual()		{ return actual; }
	template <typename U>
	void SetRoute(U raw_route1D, unsigned int cycle, int offset)
	{
		route1D = raw_route1D;
		cIter.Init(&route1D);
		if (route1D.size() < 1) throw std::string("Zero values given for aspect!");
		else if (route1D.size() == 1) route1D.at(0).mustBlend=false;
		else {
			for (int i = 0; i<route1D.size(); i++, cIter.StepOn()) {
				if (cIter.PeekNow()-> mustBlend) {
					int now = cIter.PeekNow()->time;
					int next = cIter.PeekNext()->time;
					int interval = next - now;
					if (interval < 0) {
						interval = (cycle - now) + (next - 0);
					}
					cIter.PeekNow()->blend = CalculateBlend(cIter.PeekNow()->value, cIter.PeekNext()->value, interval);
				}
			}
		}
		cIter.Init(&route1D);
		//Load DataPoint immediately prior to offset...
		while (offset >= cIter.PeekNext()->time && cIter.PeekNext()->time > cIter.PeekNow()->time) {
			cIter.StepOn();
		}
		actual = cIter.PeekNow()->value;
	}
private:
	std::vector<DataPoint<T> > route1D;
	CyclicIter<typename std::vector<DataPoint<T> > > cIter;
	T actual;
};
