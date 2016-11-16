#include "world.h"
#include "room.h"
#include "player.h"
#include "utils.h"
#include "exit.h"
#include "SimpleAI.h"
#include "finalroom.h"
#include "FeederAI.h"
#include "ZombieAI.h"
#include "GoalAI.h"


World::World()
{
	puzzles_solved = new vector<bool>(2, false);

	// Rooms

	Room* control_bridge = new Room("Control bridge", "Everything is quiet... You can listen some background noises.");
	Room* hall1 = new Room("First hall", "You feel something cold, the noises get louder.");
	Room* bedroom = new Room("Bedroom", "All the broken beds lay in the floor.");
	Room* dinning_room = new Room("Dinning room", "All the tables are upside down and lots of dishes lay on the floor, broken.\nOnly a chest remains untouched in a corner of the room.");
	Room* hall2 = new Room("Second hall", "The lights aren't working properly, they blink sometimes. You still feel the cold.");
	Room* kitchen = new Room("Kitchen", "All the cooking utils are scattered in the floor, you see small flames in the furnitures.");
	Room* hall3 = new Room("Third hall", "You start to feel the freedom, just some more rooms!");
	Room* management_room = new Room("Management room", "Everything is covered with a strange substance. You can only see one escape pod capsule available.");
	Room* bathroom = new Room("Bathroom", "Everything is broken and dark. You can't stop listening to noises coming from the corners.");
	Room* emergency_room = new Room("Emergency room", "All the escape pods are broken but one, this one is just for you it's your key to the freedom.");
	Room* escape_pod = new FinalRoom("Escape pod", "The pod is all dark! The energy may be disconected.", "The door closes behind you leaving all the monsters there\nThe pod starts moving and launches itself to the space", puzzles_solved);

	entities.push_back(control_bridge);
	entities.push_back(hall1);
	entities.push_back(bedroom);
	entities.push_back(dinning_room);
	entities.push_back(hall2);
	entities.push_back(kitchen);
	entities.push_back(hall3);
	entities.push_back(management_room);
	entities.push_back(bathroom);
	entities.push_back(emergency_room);
	entities.push_back(escape_pod);

	// Player

	player = new Player("Max", "You are an space engineer left alone in a space ship.", control_bridge);
	player->Life = 10;

	entities.push_back(player);

	// Enemies

	Creature* feeder = new Creature("Feeder", "Beware of its hands, they will slash you in a second, but they are blind ;)", bedroom);
	feeder->AI = new FeederAI(feeder);
	feeder->MaxDefense = 1;
	feeder->MaxHitpoints = 3;
	feeder->MinHitpoints = 1;
	feeder->Life = 3;

	Creature* slasher1 = new Creature("Slasher", "Beware of	its blades or it will slash you in a second!", kitchen);
	slasher1->AI = new SimpleAI(slasher1);
	slasher1->MaxDefense = 1;
	slasher1->MaxHitpoints = 3;
	slasher1->Life = 2;
	slasher1->Target = player;

	Creature* headcrab = new Creature("Headcrab", "A little monster with blades as limbs", management_room);
	headcrab->AI = new GoalAI(headcrab, puzzles_solved->at(0), "After it died, the pod pilot became green!");
	headcrab->MaxHitpoints = 5;
	headcrab->MinHitpoints = 1;
	headcrab->Life = 2;
	headcrab->Target = player;

	Creature* zombie1 = new Creature("Zombie", "A really ugly zombie, beware of its fangs! But it misses half of its attacks.", bathroom);
	zombie1->AI = new ZombieAI(zombie1);
	zombie1->MaxDefense = 3;
	zombie1->MinDefense = 1;
	zombie1->MaxHitpoints = 4;
	zombie1->MinHitpoints = 2;
	zombie1->Life = 4;
	zombie1->Target = player;

	Creature* zombie2 = new Creature("Zombie", "A really ugly zombie, beware of its fangs! But it misses half of its attacks.", emergency_room);
	zombie2->AI = new ZombieAI(zombie2);
	zombie2->MaxDefense = 3;
	zombie2->MinDefense = 1;
	zombie2->MaxHitpoints = 4;
	zombie2->MinHitpoints = 2;
	zombie2->Life = 4;
	zombie2->Target = player;

	Creature* slasher2 = new Creature("Slasher", "Beware of	its blades or it will slash you in a second!", emergency_room);
	slasher2->AI = new SimpleAI(slasher2);
	slasher2->MaxDefense = 1;
	slasher2->MaxHitpoints = 4;
	slasher2->Life = 2;
	slasher2->Target = player;

	entities.push_back(feeder);
	entities.push_back(slasher1);
	entities.push_back(headcrab);
	entities.push_back(zombie1);
	entities.push_back(zombie2);
	entities.push_back(slasher2);

	// Items

	Item* laser_gun = new Item("LaserGun", "A simple laser gun.", control_bridge);
	laser_gun->ItemType = WEAPON;
	laser_gun->MaxValue = 3;
	laser_gun->MinValue = 1;

	Item* id_card = new Item("IdCard", "An IdCard, I can't read the name on it...", bedroom);
	id_card->ItemType = KEY;

	Item* chest = new Item("Chest", "A chest, it remains untouched unlike the room", dinning_room);
	chest->ItemType = CONTAINER;
	chest->Openable = true;
	chest->Closed = true;

	Item* proton_gun = new Item("ProtonGun", "A powerful proton gun", chest);
	proton_gun->ItemType = WEAPON;
	proton_gun->MaxValue = 5;
	proton_gun->MinValue = 2;

	Item* proton_shield = new Item("ProtonShield", "A powerful shield", slasher1);
	proton_shield->ItemType = ARMOUR;
	proton_shield->MaxValue = 5;
	proton_shield->MinValue = 2;

	Item* isaac_card = new Item("IsaacCard", "An IdCard, I can read the name Isaac on it...", slasher1);
	isaac_card->ItemType = KEY;

	Item* pod_key = new Item("PodKey", "The key of the pod!", zombie1);
	pod_key->ItemType = KEY;

	entities.push_back(laser_gun);
	entities.push_back(id_card);
	entities.push_back(chest);
	entities.push_back(proton_gun);
	entities.push_back(proton_shield);
	entities.push_back(isaac_card);
	entities.push_back(pod_key);

	// Exits
	Exit* control_hall1 = new Exit("south", "north", "A white door", control_bridge, hall1);

	Exit* hall1_bedroom = new Exit("west", "east", "This door is broken", hall1, bedroom);
	hall1_bedroom->Closed = false;

	Exit* hall1_dinning = new Exit("east", "west", "The unlock pannel is broken", hall1, dinning_room);
	hall1_dinning->Locked = true;

	Exit* hall1_hall2 = new Exit("south", "north", "Noises come from this door", hall1, hall2, id_card);

	Exit* hall2_kitchen = new Exit("east", "west", "Smells like chicken", hall2, kitchen);

	Exit* kitchen_dinning = new Exit("north", "south", "The unlock pannel seems to work", kitchen, dinning_room, id_card);

	Exit* hall2_hall3 = new Exit("south", "north", "The door is really cold", hall2, hall3);

	Exit* hall3_management = new Exit("west", "east", "This door is covered with lots of warning signs!", hall3, management_room, isaac_card);

	Exit* hall3_bathroom = new Exit("south", "north", "The door is wet...", hall3, bathroom);

	Exit* hall3_emergency = new Exit("east", "west", "This door smells like freedom.", hall3, emergency_room);

	Exit* emergency_pod = new Exit("east", "west", "The door pannel seems to be working!", emergency_room, escape_pod, pod_key);

	entities.push_back(control_hall1);
	entities.push_back(hall1_bedroom);
	entities.push_back(hall1_dinning);
	entities.push_back(hall1_hall2);
	entities.push_back(hall2_kitchen);
	entities.push_back(kitchen_dinning);
	entities.push_back(hall2_hall3);
	entities.push_back(hall3_management);
	entities.push_back(hall3_bathroom);
	entities.push_back(hall3_emergency);
	entities.push_back(emergency_pod);
}


World::~World()
{
	for (Entity* entity: entities)
	{
		delete entity;
	}

	delete puzzles_solved;
}

bool World::Tick(arglist& args)
{
	bool result = true;

	if (args.size() > 0)
	{
		result = ParseCommand(args);
	}

	GameLoop();
	return result;
}

bool World::AllPuzzlesSolved() const
{
	return all(*puzzles_solved);
}

bool World::IsPlayerAlive() const
{
	return player->IsAlive();
}

void World::GameLoop()
{
	for (Entity* entity : entities)
	{
		entity->Tick();
	}
}

bool World::ParseCommand(arglist& args)
{
	bool ret = true;

	// TODO: Improve that!!!
	if (str_equals(args[0], "look"))
	{
		player->Look(args);
	}
	else if (str_equals(args[0], "pick") || str_equals(args[0], "take"))
	{
		ret = player->Pick(args);
	}
	else if (str_equals(args[0], "drop"))
	{
		ret = player->Drop(args);
	}
	else if (str_equals(args[0], "north") || str_equals(args[0], "n") || str_equals(args[0], "south") || str_equals(args[0], "s")
		|| str_equals(args[0], "east") || str_equals(args[0], "e") || str_equals(args[0], "west") || str_equals(args[0], "w"))
	{
		complete_direction(args[0]);
		player->Move(args);
	}
	else if (str_equals(args[0], "open"))
	{
		player->Open(args);
	}
	else if (str_equals(args[0], "close"))
	{
		player->Close(args);
	}
	else if (str_equals(args[0], "unlock"))
	{
		ret = player->UnLock(args);
	}
	else if (str_equals(args[0], "lock"))
	{
		ret = player->Lock(args);
	}
	else if (str_equals(args[0], "inventory"))
	{
		player->Inventory();
	}
	else if (str_equals(args[0], "equip"))
	{
		ret = player->Equip(args);
	}
	else if (str_equals(args[0], "unequip"))
	{
		ret = player->UnEquip(args);
	}
	else if (str_equals(args[0], "attack"))
	{
		ret = player->Attack(args);
	}
	else if (str_equals(args[0], "stats"))
	{
		player->Stats(args);
	}
	else if (str_equals(args[0], "examine"))
	{
		ret = player->Examine(args);
	}
	else if (str_equals(args[0], "loot"))
	{
		ret = player->Loot(args);
	}
	else if (str_equals(args[0], "help"))
	{
		help();
	}
	else
	{
		ret = false;
	}

	return ret;
}
