#include "IOclass.h"

/*Input function which fills string vectors with names from input files*/
void IOclass::input_from_file(std::vector<std::string>& male, std::vector<std::string>& female, std::vector<std::string>& surname, std::vector<std::string>& evil)
{
	for (int i = 0; i < FILE_NAMES.size(); ++i) { // loops through different files and reads data from them
		std::string temp;
		std::string iname = FILE_NAMES[i];//chooses a files name to read from
		std::ifstream ist{ iname }; // ist is an input stream
		if (!ist) throw Invalid_fileIO{};  //if file can't be opened exception is thrown
		while (ist >> temp) {
			if (ist.bad()) throw Invalid_fileIO{}; // if something unexpected happens exception is thrown
			if (ist.eof()) break; //if end of file is reached break statement is used
			for (int j = 0; j < temp.size(); ++j)	if (temp[j] == ',') temp.erase(j); //loops through the string and erases comma if detected
			if (i == 0) male.push_back(temp);
			else if (i == 1) female.push_back(temp);
			else if (i == 2) surname.push_back(temp);
			else if (i == 3) evil.push_back(temp);
			else std::cout << "Something went bad in input section\n";
		}
		
	}
}

/*Output function which uses ofstream to output data to "Output_file.txt"*/
void IOclass::output_to_file(const Prefix & type, const Bunny *data) {
	std::ofstream ofst{ "Output_file.txt", std::ios_base::app }; // ofst is an output stream for a file named Output_file.txt
	if (!ofst) throw Invalid_fileIO{};  //if file can't be opened exception is thrown
	switch (type) { //decides output formating prefix
	case Prefix::born:
		ofst << "Born: " << *data;
		break;
	case Prefix::aged:
		ofst << "Aged: " << *data;
		break;
	case Prefix::died:
		ofst << "Died: " << *data;
		break;
	}
}