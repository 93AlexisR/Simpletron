// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

SimpletronData::SimpletronData(unsigned int newData) {
	setValue(newData);
}

SimpletronData::SimpletronData(void) {
	SimpletronData(0);
}


void SimpletronData::setValue(unsigned int newInstruction){
	if (newInstruction > 9999) {
		std::cout << "Invalid value, exiting program... (range is 0-9999)\n";
		std::cin.get();
		abort();
	}
	else {
		instructionType = static_cast<unsigned int>(trunc(static_cast<double>(newInstruction) / 100.0));
		memoryLocation = newInstruction - static_cast<unsigned int>(instructionType * 100.0);
		//std::cout << "memloc is " << memoryLocation << "instruction type is " << instructionType << std::endl;
	}
}




const unsigned int SimpletronData::getMemLoc(void) {
	return memoryLocation;
}
const unsigned int SimpletronData::getInstType(void) {
	return instructionType;
}

const unsigned int SimpletronData::getRawData(void) {
	return getInstType()+getMemLoc();
}

void Simpletron::Run(bool newStatus) {


	std::cout << "*** Welcome to the Simpletron! ***\n"
		<< "*** Please enter your program one instruction ***\n"
		<< "*** (or data word) at a time.I will type the ***\n"
		<< "*** location number and a question mark(? ). ***\n"
		<< "*** You then type the word for that location. ***\n"
		<< "*** Type any value above 9999 to stop entering ***\n"
		<< "*** your program. ***" << std::endl << std::endl << std::endl;


	for (unsigned int i = 0; i < memory.size(); ++i){
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << i << " ?" << " +";
		std::cin.clear();
		std::cin >> memBuffer;
		if (memBuffer > 9999) {
			std::cout << "Sentinel value detected... compiling program\n";
			break;
		}
		else {
			memory[i] = SimpletronData(memBuffer);
		}
	}

	for (unsigned int i = 0; i < memory.size() - 1; i++) {
		//std::cout << memory[i].getInstType() << std::endl;
		std::cin.clear();
		switch (memory[i].getInstType()) {
			case static_cast<unsigned int>(Operation::READ) :
				std::cin.clear();
				std::cin >> memBuffer;
				memory[memory[i].getMemLoc()].setValue(memBuffer);
				//std::cout << memory[memory[i].getMemLoc()].getRawData() << std::endl;
				break;

			case static_cast<unsigned int>(Operation::WRITE) :
				std::cout << memory[memory[i].getMemLoc()].getRawData() << std::endl; //not a debug cout, keep it! 
				break;

				case static_cast<unsigned int>(Operation::LOAD) :
				//std::cout << "memory location we pull data from: " << memory[i].getMemLoc() << std::endl;
				accumulator = memory[memory[i].getMemLoc()].getRawData();
				//std::cout << "accumulator loaded with " << accumulator << std::endl;
				break;

				case static_cast<unsigned int>(Operation::STORE) :
				//std::cout << "storing " << accumulator << " into memory loc " << memory[i].getMemLoc() << std::endl;
				memory[memory[i].getMemLoc()] = SimpletronData(accumulator);
				break;

			case static_cast<unsigned int>(Operation::ADD) :
				accumulator += memory[memory[i].getMemLoc()].getRawData();
				//std::cout << "accumulator added value now " << accumulator << std::endl;
				break;

			case static_cast<unsigned int>(Operation::SUBSTRACT) :
				accumulator = memory[memory[i].getMemLoc()].getRawData() - accumulator;
				break;

			case static_cast<unsigned int>(Operation::MULTIPLY) :
				accumulator *= memory[memory[i].getMemLoc()].getRawData();
				break;

			case static_cast<unsigned int>(Operation::DIVIDE):
				accumulator = static_cast<unsigned int>(memory[memory[i].getMemLoc()].getRawData() - accumulator);
				break;

			case static_cast<unsigned int>(Operation::BRANCH) :
				i = memory[i].getMemLoc();
				break;

			case static_cast<unsigned int>(Operation::BRANCHNEG):
				if (accumulator < 0) {
					i = memory[i].getMemLoc();
				}
				break;

			case static_cast<unsigned int>(Operation::BRANCHZERO):
				if (accumulator == 0) {
					i = memory[i].getMemLoc();
				}
				break;

			case static_cast<unsigned int>(Operation::HALT) :
				std::cout << "Program complete. Press enter to exit...\n";
				std::cin.get();
				return;
			default: 
				std::cout << "Invalid code, please check entry..." << std::endl;
				return;
		}
	}

}


// In general, ignore this file, but keep it around if you are using pre-compiled headers.

