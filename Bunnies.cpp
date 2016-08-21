#include "Bunnies.h"


std::vector <std::string> Name_male;
std::vector <std::string> Name_female;
std::vector <std::string> Surname;
std::vector <std::string> Name_evil;

/*Helper function used for generating random names from two vectors*/
std::string rand_two_vectors(const std::vector <std::string> & names_vect, const std::vector <std::string> & surnames_vect) {
	int random_numb = rand() % (names_vect.size()); //takes random name
	std::string name = names_vect[random_numb] + " ";
	random_numb = rand() % (surnames_vect.size());
	return name + surnames_vect[random_numb]; // adds random surname to random name and returns
}

/*Helper function used for generating random names from one vector*/
std::string rand_one_vector(const std::vector <std::string> & vct) {
	return vct[rand() % (vct.size())];
}

/*Randomly chooses gender for Sweet_Bunny*/
Sweet_Bunny::Gender rand_gender() {
	int random_numb = rand() % 2; //generates random number between 0 and 1
	switch (random_numb)
	{
	case 0:
		return Sweet_Bunny::Gender::male;
		break;
	case 1:
		return Sweet_Bunny::Gender::female;
		break;
	default:
		std::cout << "error rand gender()\n";
		break;
	}
}

/*Function used for output formatting */
std::ostream& Sweet_Bunny::print(std::ostream& str)const {
	
	if (gender() == 0) return str << "Male,   it's name is " << bunny_name()  //if Bunny is male
		<< " color: " << bunny_color() << " and is " << bunny_age() << " years old\n";
	else return str << "Female, it's name is " << bunny_name() //if Bunny is female
		<< " color: " << bunny_color() << " and is " << bunny_age() << " years old\n";
}

/*Constructor for bunnies when color is inherited from mother*/
Sweet_Bunny::Sweet_Bunny(std::string mother)
	: gdr{ rand_gender() }
{ 
	choose_a_name(); 
	set_color(mother); //inherits color from its mother
}

/*Constructor for first bunnies*/
Sweet_Bunny::Sweet_Bunny()
	:gdr{ rand_gender() }
{
	choose_a_name();
	set_color(rand_one_vector(COLOR));
}

/*Chooses a name for bunny according to its gender*/
void Sweet_Bunny::choose_a_name() {
	switch (gdr)
	{
	case Sweet_Bunny::male:
		set_name(rand_two_vectors(Name_male, Surname));
		break;
	case Sweet_Bunny::female:
		set_name(rand_two_vectors(Name_female, Surname));
		break;
	default:
		std::cout << "error Sweet_Bunny::choose_a_name()\n";
		break;
	}
}

/*Function used for output formatting */
std::ostream& Evil_Bunny::print(std::ostream& str)const {
	return str << "Evil bunny, it's name is " << bunny_name()
		<< " and he is " << bunny_age() << " years old\n";
}

/*Chooses name for evil bunny*/
void Evil_Bunny::choose_a_name() {
	set_name(rand_one_vector(Name_evil));
}



