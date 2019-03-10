// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files haarhar
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <iomanip>

class SimpletronData {
public:
	SimpletronData(void);
	SimpletronData(unsigned int newData);
	const unsigned int getMemLoc(void);
	const unsigned int getInstType(void);
	const unsigned int getRawData(void);
	void setValue(unsigned int newValue);
protected:

private:
	unsigned int memoryLocation{ 0 };
	unsigned int instructionType{ 0 };
};


class Simpletron {
public:
	Simpletron(void) {
		for (unsigned int i = 0; i < 100; ++i) {
			memory.push_back(SimpletronData(0));
		}
	}

	void Run(bool newStatus);




	std::vector<SimpletronData> memory{ 0 };
	int memBuffer = 0;
	
	
	enum class Operation {
		READ = 10,
		WRITE = 11,
		LOAD = 20,
		STORE = 21,
		ADD = 30,
		SUBSTRACT = 31,
		DIVIDE = 32,
		MULTIPLY = 33,
		BRANCH = 40,
		BRANCHNEG = 41,
		BRANCHZERO = 42,
		HALT = 43
	};
	//In/Out operations14515
	int accumulator{ 0 };

};

// TODO:
// Done - Extend simpletron memory to contain 1000 memory locations
// Allow the simulator to perform remainder calculations (modulus, extra instruction needed)
// Allow simulator to perform exponentiation calculations (extra instruction needed)
// Allow printing of a newline



#endif //PCH_H
