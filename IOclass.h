#pragma once
#include "Bunnies.h"


/*Input/Output class used for reading from files and writing to files*/
class IOclass {
public:
	class Invalid_fileIO {}; // Used for exceptions

	enum Prefix { born, aged, died }; 
	/*Input function which fills string vectors with names from input files*/
	static void input_from_file(std::vector<std::string>& male, std::vector<std::string>& female, std::vector<std::string>& surname, std::vector<std::string>& evil);

	/*Output function which uses ofstream to output data to "Output_file.txt"*/
	static void output_to_file(const Prefix & typee, const Bunny *data);
};

