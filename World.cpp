#include "World.h"


/*Destructor for class World*/
World::~World() {
	if (goodBunny.size() > 0) { //If for some reason some sweet bunnies still exists they are destroyed and removed from list
		for (std::list<Sweet_Bunny*>::iterator i = goodBunny.begin(), end = goodBunny.end(); i != end;) {
			delete (*i);
			i = goodBunny.erase(i);
		}
	}
	if (badBunny.size() > 0) {// all evil bunnies are destroyed and removed from list 
		for (std::list<Evil_Bunny*>::iterator i = badBunny.begin(), end = badBunny.end();i != end;) {
			delete (*i);
			i = badBunny.erase(i);
		}
	}
}

/*Counts male and female bunny numbers */
void World::counting() {
	int temp_male = 0;
	int temp_female = 0;
	for (std::list<Sweet_Bunny*>::iterator p = goodBunny.begin(), end = goodBunny.end(); p != end; ++p) { //goes through goodBunny list and counts
		if ((*p)->gender() == Sweet_Bunny::Gender::female) ++temp_female;								// male and female bunnies, then updates it
		else ++temp_male;
	}
	male_bunny_numb = temp_male;
	female_bunny_numb = temp_female;
	if (male_bunny_numb + female_bunny_numb != goodBunny.size()) {
		throw Invalid_World{}; //if there are some problems with counting, exceptions is thrown
	}
}

/*This function is called from birth() function and it randomly "gives birth" to evil or sweet bunny*/
void World::is_evil(int a, std::string color) {
	for (int i = 0; i < a; ++i) {
		if (EVIL == rand() % EVIL_CHANCE + 1) {//if random number is 11, evil bunny is born
			badBunny.push_front(new Evil_Bunny());
			++vampire_bunny_numb;
			std::cout << "Radioactive Mutant Vampire Bunny " << badBunny.front()->bunny_name() << " was born!\n";
			IOclass::output_to_file(IOclass::Prefix::born, *badBunny.begin());//outputs evil bunny info to a file
		}
		else {
			if (color != "") goodBunny.push_front(new Sweet_Bunny(color));//if bunny is born from mother, it inherits mothers color
			else goodBunny.push_front(new Sweet_Bunny());
			IOclass::output_to_file(IOclass::Prefix::born, *goodBunny.begin()); //outputs bunny info to a file
			std::cout << "Bunny " <<  goodBunny.front()->bunny_name() << " was born!\n";
			counting();
		}
		
	}
}

/*Function responsible for birth of new bunnies*/
void World::birth() {
	if (turns == 0) { //if it's the first turn program initializes 5 bunnies
		is_evil(STARTING_NUMBER);
	}
	else {
		//first while goes through the list searching for male bunny 2 years old or older, if such a bunny exists,
		//second while goes searching for females 2 years old and older, if such a female bunny is found, new bunny is born
		if (female_bunny_numb > 0 && male_bunny_numb > 0) {
			std::list<Sweet_Bunny*>::iterator i = goodBunny.begin(), ii = goodBunny.begin();
			std::list<Sweet_Bunny*>::const_iterator end = goodBunny.end(), endd = goodBunny.end();
			while (i != end) {
				if (int((*i)->gender()) == Sweet_Bunny::Gender::male && (*i)->bunny_age() > 1) {
					while (ii != endd) {
						if (int((*ii)->gender()) == Sweet_Bunny::Gender::female && (*ii)->bunny_age() > 1) {
							is_evil(ONE, (*ii)->bunny_color());
						}
						++ii;
					}
					break; //break statement is used after finding one male bunny old enough
				}
				++i;
			}
		}
	}
}

/*Function responsible for aging and death of bunnies*/
void World::aging() { 
	if (male_bunny_numb == 0 && female_bunny_numb == 0) return;
	//Goes through goodbunny list and increases age for every bunny by one year
	//if bunny is older than 10 years it "dies" and is eraded from the list
	for(std::list<Sweet_Bunny*>::iterator i = goodBunny.begin(), end = goodBunny.end(); i != end;){
		(*i)->increase_age();
		if ((*i)->bunny_age() > 10) {
			std::cout << "Bunny " << (*i)->bunny_name() << " died from old age!\n";
			IOclass::output_to_file(IOclass::Prefix::died, *i);
			delete (*i); // deletes Bunny object 
			i = goodBunny.erase(i); // erases pointer to Bunny object
		}
		else {
			IOclass::output_to_file(IOclass::Prefix::aged, *i);
			++i;
		}
	}
	counting(); //updates male and female bunny counts

	//Goes through evilbunny list and increases age for every evil bunny by one year
	//if evil bunny is older than 50 years, it "dies" and is erased from the list
	for (std::list<Evil_Bunny*>::iterator i = badBunny.begin(), end = badBunny.end(); i != end;) {
		(*i)->increase_age();
		if ((*i)->bunny_age() > 50) {
			std::cout << "Radioactive Mutant Vampire Bunny " << (*i)->bunny_name() << " died from old age!\n";
			IOclass::output_to_file(IOclass::Prefix::died, *i); //outputs bunny info to a file
			delete (*i); // deletes Bunny object 
			i = badBunny.erase(i); // erases pointer to Bunny object
			--vampire_bunny_numb;
		}
		else {
			IOclass::output_to_file(IOclass::Prefix::aged, *i); //outputs bunny info to a file
			++i;
		}
	}
}

/*Function handles changing from Sweet_Bunny to Evil_Bunny and then deals with lists where they are stored */
void World::evolutions() {
	int end = 0;
	//looks for end conditions for a loop. If there are more evil bunnies than sweet bunnies, loop runs for goodBunny.size() times 
	//if there are more good bunnies, loop runs for badBunny.size() times
	badBunny.size() > goodBunny.size() ? end = goodBunny.size() : end = badBunny.size() ;
	for (int i = 0; i < end; ++i) {
		std::list<Sweet_Bunny*>::iterator j = next(goodBunny.begin(), (rand() % goodBunny.size())); //randomly chooses sweet bunny to turn to evil bunnie
		if ((*j)->gender() == Sweet_Bunny::Gender::female && female_bunny_numb >= 1) { //if bunny is a female
			std::cout << "Bunny " << (*j)->bunny_name() << " died and became EVIL!\n";
			--female_bunny_numb;
			IOclass::output_to_file(IOclass::Prefix::died, *j);//outputs bunny info to a file
			delete (*j); //deletes Bunny object
			goodBunny.erase(j); //erases sweet bunny from a list
			
		}
		else if ((*j)->gender() == Sweet_Bunny::Gender::male && male_bunny_numb >= 1) { //if bunny is a male
			std::cout << "Bunny " << (*j)->bunny_name() << " died and became EVIL!\n";
			 --male_bunny_numb;
			 IOclass::output_to_file(IOclass::Prefix::died, *j);//outputs bunny info to a file
			 delete (*j); //deletes Bunny object
			 goodBunny.erase(j); //erases sweet bunny from a list
		}
		else {
			throw Invalid_World{};
		}
		badBunny.push_front(new Evil_Bunny());//adds evil bunny to a list
		std::cout << "Radioactive Mutant Vampire Bunny " << badBunny.front()->bunny_name() << " was born!\n";
		IOclass::output_to_file(IOclass::Prefix::born, badBunny.front());//outputs bunny info to a file
		++vampire_bunny_numb;
		counting(); //updates male and female bunny counts
	}
}


/*Manages how the World works, starts it "running" ant stops it*/
void World::start() {
	if (!ONOFF) ONOFF = true;
	birth(); //initializes first bunnies
	while (ONOFF) {
		++turns;
		evolutions();
		birth();
		aging();
		std::cout << "Turn: " << turns << std::endl;
		std::cout << "GoodBunny size: " << goodBunny.size() << std::endl;
		if (goodBunny.size() == 0) ONOFF = false; // if there are no more bunnies the world seize to exist		
	}
}