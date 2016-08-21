#pragma once
#include "Bunnies.h"
#include "IOclass.h"

constexpr int STARTING_NUMBER = 5; //Starting number of bunnies in the World


/*Class which manages "life" of bunnies*/
class World {
public:
	class Invalid_World {}; //Used for exceptions
	World() {};
	
	void start(); //Starts the World "running"

	/*Function responsible for birth of new bunnies*/
	void birth();
	/*Function responsible for aging and death of bunnies*/
	void aging();
	/*Function handles changing from Sweet_Bunny to Evil_Bunny and then deals with lists where they are stored */
	void evolutions();
	/*Counts male and female bunny numbers */
	void counting();


	int turn() const { return turns; }

	int male_numb() const { return male_bunny_numb; }
	int female_numb() const { return female_bunny_numb; }
	int vampire_numb() const { return vampire_bunny_numb; }

	/*Destructor for class World*/
	~World();
private:
	/*This function is called from birth() function and it randomly "gives birth" to evil or sweet bunnies*/
	void is_evil(int a = 1, std::string color = "");//integer argument shows number of bunnies to be born, string argument deals with bunny color

	std::list<Sweet_Bunny*> goodBunny; //Stores a list of Sweet_Bunnies
	std::list<Evil_Bunny*> badBunny; //Stores a list of Evil_Bunnies

	int turns{ 0 };// counts turns since "start of the World"

	int male_bunny_numb{ 0 };
	int female_bunny_numb{ 0 };
	int vampire_bunny_numb{ 0 };

	bool ONOFF{ false }; // If conditions are right "stops the World" at start() function
};
