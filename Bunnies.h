#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

 

/*files with bunny names and surnames to read from*/
const std::vector<std::string> FILE_NAMES{ "Male_names.txt", "Female_names.txt", "Surnames.txt", "Evil_names.txt" };
const std::vector<std::string> COLOR{ "white", "brown", "black", "spotted" };

constexpr int ONE = 1;
constexpr int EVIL_CHANCE = 50; // There is 1 in 50 chance that the vampire bunny is born
constexpr int EVIL = 11; // Random number between 1 and 50;


/* Base class used for creating Sweet_Bunny and Evil_Bunny classes*/
class Bunny {
public:
	std::string bunny_name() const { return name; }
	std::string bunny_color() const { return color; }
	bool bunny_vampire() const { return radioactive_mutant_vampire_bunny; }
	int bunny_age() const { return age; }

	void increase_age() { ++age; } //every turn bunny gets older 1 year

	/*operator << override. Gets relevant data from print(ostream& str) function*/
	friend std::ostream& operator<<(std::ostream& str,const Bunny & data){
		data.print(str);
		return str;
	}

protected:
	Bunny() {}
	virtual std::ostream& print(std::ostream& str)const = 0; //Virtual function used for output formatting 

	void set_name(const std::string& nam) { name = nam; } //Sets names for bunnies. Names are randomly generated at derived classes according to bunny type
	void set_color(const std::string& col) { color = col; }//Sets color for Sweet_Bunny class objects. Colors are randomly chosen at Sweet_Bunny member function
private:
	std::string name{ "NoName" };
	std::string color{};
	int age{ 0 };
	bool radioactive_mutant_vampire_bunny{ false };
};

/*class derived from base Bunny class*/
class Sweet_Bunny : public Bunny {
public:
	Sweet_Bunny();//Constructor for first five bunnies
	Sweet_Bunny(std::string mother);//Constructor for bunnies when color is inherited from mother

	enum Gender { male, female };
	Gender gender()const { return gdr; }

	void choose_a_name();//randomly chooses names according to bunnies gender
	std::ostream& print(std::ostream& str)const; //virtual function from base class. Does all the formating job before writing to file/console
private:
	Gender gdr;
};

/*class derived from base Bunny class*/
class Evil_Bunny : public Bunny {
public:
	Evil_Bunny() { choose_a_name(); }; //Constructor

	void choose_a_name();//randomly chooses names for evil bunnies
	std::ostream& print(std::ostream& str)const;//virtual function from base class. Does all the formating job before writing to file/console
};

