#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include "World.h"
#include <ctime>

/*Exercise:
Write a program that creates a linked list of bunny objects.
Each bunny object must have
Sex: Male, Female (random at creation 50/50)
color: white, brown, black, spotted
age : 0-10 (years old)
Name : randomly chosen at creation from a list of bunny names.
radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation 2% chance of true)

At program initialization 5 bunnies must be created and given random colors.
Each turn afterwards the bunnies age 1 year.
So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older;
a new bunny is created each turn. (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn)
New bunnies born should be the same color as their mother.
If a bunny becomes older than 10 years old, it dies.
If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny.
(if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
Radioactive vampire bunnies do not die until they reach age 50.
The program should print a list of all the bunnies in the colony each turn along w/ all the bunnies details, sorted by age.
The program should also output each turns events such as
"Bunny Thumper was born!
Bunny Fufu was born!
Radioactive Mutant Vampire Bunny Darth Maul was born!
Bunny Julius Caesar died!
The program should write all screen output to a file.
When all the bunnies have died the program terminates.*/



extern std::vector <std::string> Name_male;
extern std::vector <std::string> Name_female;
extern std::vector <std::string> Surname;
extern std::vector <std::string> Name_evil;


int main()
try{
	srand(time(NULL));
	IOclass::input_from_file(Name_male, Name_female, Surname, Name_evil);// Reads names from files and stores them in vectors
	World earth;
	earth.start();


	return 0;
} 
catch (World::Invalid_World){
	std::cout << "Problem with bunny numbers\n";
	return 1;
}
catch (IOclass::Invalid_fileIO) {
	std::cout << "Problem with reading/writing files\n";
	return 2;
}