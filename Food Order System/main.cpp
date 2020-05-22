/*
Project: 1011 A2
Author:  X3vvv
Data:    May 20, 2020
*/

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <iomanip>

using namespace std;


static string menu[16] = {"Cheese veggie sandwich", "Salmon & cheese sandwich",
						  "Chicken Caesar Sandwich", "(Quebec homemade) Quiche",
						  "Bagel with Cream Cheese", "(East Village Chicken) Pie",
						  "Coffee", "Green Tea", "Hot Chocolate", "Milk", "Juice",
						  "Refreshing Breakfast", "Best Value Breakfast", "Veggie Lunch",
						  "Power Lunch", "Afternoon Tea Set"}; //use menu index

static map<string, map<int, string>> sets;

static string item_codes[16] = {"A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2",
								"C3", "C4", "C5", "S1", "S2", "S3", "S4", "S5"}; //use menu index

static int prices[16] = {30, 34, 32, 28, 20, 28, 36, 28, 28, 26, 26, 48, 60, 50, 90, 50}; //use menu index

static string order_list[16]; //each item's itemCode will only be record once;
							  //the indexes are decided by the sequence of each item being ordered the first time.

static int item_numbers[16]; //the index is the menu index.

static string OIS; //Order Identification Code


void init()
{
	/*
	This function inicialize order_list, item_number, OIS and sets.
	*/

	for (int i = 0; i < 16; i++)
	{
		order_list[i] = "";
		item_numbers[i] = 0;
	}
	OIS = "";

	sets["S1"][0] = "C1"; // Coffee
	sets["S1"][1] = "B2"; // Bagel with	Cream Cheese

	sets["S2"][0] = "C4"; // Milk
	sets["S2"][1] = "A3"; // Chicken Caesar Sandwich
	sets["S2"][2] = "B2"; // Bagel with	Cream Cheese

	sets["S3"][0] = "C5"; // Juice
	sets["S3"][1] = "A1"; // Cheese veggie sandwich

	sets["S4"][0] = "C5"; // Juice
	sets["S4"][1] = "C1"; // Coffee
	sets["S4"][2] = "A2"; // Salmon& cheese sandwich
	sets["S4"][3] = "B3"; // Pie

	//S5: 4 possible combos: 0+2 0+3 1+2 1+3
	sets["S51"][0] = "C1"; // Coffee
	sets["S51"][2] = "B1"; // Quiche

	sets["S52"][0] = "C1"; // Coffee
	sets["S52"][3] = "B3"; // Pie

	sets["S53"][1] = "C2"; // Tea
	sets["S53"][2] = "B1"; // Quiche

	sets["S54"][1] = "C2"; // Tea
	sets["S54"][3] = "B3"; // Pie
}


void welcome()
{

	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|                                                           |" << endl;
	cout << "|   _       __     __                             __        |" << endl;
	cout << "|  | |     / /__  / /________  ____ ___  ___     / /_____   |" << endl;
	cout << "|  | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\   / __/ __ \\  |" << endl;
	cout << "|  | |/ |/ /  __/ / /__/ /_/ / / / / / /  __/  / /_/ /_/ /  |" << endl; //48 chars
	cout << "|  |__/|__/\\_____/\\_____________/_/ _______/   \\________/   |" << endl;
	cout << "|          /__  /    |__ \\|__  /   / ____/___ _/ __/__      |" << endl;
	cout << "|            / /_______/ / /_ <   / /   / __ `/ /_/ _ \\     |" << endl;
	cout << "|           / /_____/ __/___/ /  / /___/ /_/ / __/  __/     |" << endl;
	cout << "|          /_/     /____/____/   \\____/\\__,_/_/  \\___/      |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
}


void Oline(string code, string name, int price, int n = 0)
{
	/*
    This function output a formated food item line.
    By inputing the item ID, item name, item price and the number of the item,
	this function will output the information in an user-friendly format.
		e.g.1.
		Oline("A1", "Cheese veggie sandwich", "30");
			=> "| A1 | Cheese veggie sandwich---------------------------$30 |"
		e.g.2.
		Oline("A1", "Cheese veggie sandwich", "30", 3);
			=> "| A1 | Cheese veggie sandwich------------------- *3 ----$90 |"
   */

	cout << "| " << code << " | ";
	if (n == 0)
	{
		cout << setfill('-') << setw(47) << name + " ";
	}
	else
	{
		cout << setfill('-') << setw(40) << name + " ";
		cout << setw(7) << " *" + to_string(n) + " ";
		price = price * n;
	}

	cout << " $" << setfill(' ') << setw(4) << price << "|" << endl;
}


void showMenu()
{
	cout << left; //Align left;

	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                  _____ _____ _____ _____                  |" << endl;
	cout << "|                 |     |   __|   | |  |  |                 |" << endl; //18 spaces each side
	cout << "|                 | | | |   __| | | |  |  |                 |" << endl;
	cout << "|                 |_|_|_|_____|_|___|_____|                 |" << endl;
	cout << "|                                                           |" << endl;

	cout << "|___________________________________________________________|" << endl;
	cout << "|________________________SANDWICHES_________________________|" << endl;
	cout << "|                                                           |" << endl;

	Oline("A1", "Cheese veggie sandwich", 30);
	cout << "|    |                                                      |" << endl;
	Oline("A2", "Salmon & cheese sandwich", 34);
	cout << "|    |                                                      |" << endl;
	Oline("A3", "Chicken Caesar Sandwich", 32);
	cout << "|                                                           |" << endl;

	cout << "|                                                           |" << endl;
	cout << "|___________________________________________________________|" << endl;
	cout << "|_____________________SNACKS & DESSERTS_____________________|" << endl;
	cout << "|                                                           |" << endl;

	Oline("B1", "(Quebec homemade) Quiche", 28);
	cout << "|    |                                                      |" << endl;
	Oline("B2", "Bagel with Cream Cheese", 20);
	cout << "|    |                                                      |" << endl;
	Oline("B3", "(East Village Chicken) Pie", 28);
	cout << "|                                                           |" << endl;

	cout << "|                                                           |" << endl;
	cout << "|___________________________________________________________|" << endl;
	cout << "|__________________________DRINKS___________________________|" << endl;
	cout << "|                                                           |" << endl;

	Oline("C1", "Coffee", 36);
	cout << "|    |                                                      |" << endl;
	Oline("C2", "Green Tea", 28);
	cout << "|    |                                                      |" << endl;
	Oline("C3", "Hot Chocolate", 28);
	cout << "|    |                                                      |" << endl;
	Oline("C4", "Milk", 26);
	cout << "|    |                                                      |" << endl;
	Oline("C5", "Juice", 26);
	cout << "|                                                           |" << endl;

	cout << "|                                                           |" << endl;
	cout << "|___________________________________________________________|" << endl;
	cout << "|_________________________SET MEALS_________________________|" << endl;
	cout << "|                                                           |" << endl;

	Oline("S1", "Refreshing Breakfast", 48); //Coffee + Bagel with cream cheese
	cout << "|    |                                                      |" << endl;
	cout << "|    | B2 |  Bagel with Cream cheese                        |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | C1 |  Coffee                                         |" << endl;
	cout << "|    |                                                      |" << endl;
	cout << "|    |                                                      |" << endl;
	Oline("S2", "Best Value Breakfast", 60); //Milk + Chicken Caesar Sandwich + Bagel withCream Cheese
	cout << "|    |                                                      |" << endl;
	cout << "|    | A3 |  Chicken Caesar Sandwich                        |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | B2 |  Bagel with Cream Cheese                        |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | C4 |  Milk                                           |" << endl;
	cout << "|    |                                                      |" << endl;
	cout << "|    |                                                      |" << endl;
	Oline("S3", "Veggie Lunch", 50); //Juice + Cheese veggie sandwich
	cout << "|    |                                                      |" << endl;
	cout << "|    | A1 |  Cheese veggie sandwich                         |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | C5 |  Juice                                          |" << endl;
	cout << "|    |                                                      |" << endl;
	cout << "|    |                                                      |" << endl;
	Oline("S4", "Power Lunch", 90); //Juice + Coffee + Salmon & cheese sandwich + Pie
	cout << "|    |                                                      |" << endl;
	cout << "|    | A2 |  Salmon & cheese sandwich                       |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | B3 |  Pie                                            |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | C5 |  Juice                                          |" << endl;
	cout << "|    |    |                                                 |" << endl;
	cout << "|    | C1 |  Coffee                                         |" << endl;
	cout << "|    |                                                      |" << endl;
	cout << "|    |                                                      |" << endl;
	Oline("S5", "Afternoon Tea Set", 50); //Coffee or Tea + Quiche or Pie
	cout << "|    |                                                      |" << endl;
	cout << "|    | B1/3 | Quiche or Pie                                 |" << endl;
	cout << "|    |      |                                               |" << endl;
	cout << "|    | C1/2 | Coffee or Tea                                 |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
}


string enterSystemCommand()
{
	/*
	This function ask the user to enter or re-enter an valid system
	command(0 or 1) and return it,
	*/

	string command;
	while (true)
	{
		cin >> command;

		//if valid input
		if (command == "0" || command == "1")
		{
			break;
		}

		//re-enter prompt
		cout << "|-----------------------------------------------------------|" << endl;
		cout << "|                                                           |" << endl;
		cout << "| >   Invalid System Command.                               |" << endl;
		cout << "|     Please enter again:                                   |" << endl;
		cout << "|                                                           |" << endl;
		cout << "| >   ";
	}

	return command;
}


void prompt(string type)
{
	/*
	This function may prompt user to start/re-start order, order a new item,
	finish ordering or enter OIS.

	type: "start", "restart", "order", "finish", "OIS".
	*/

	if (type == "finish")
	{
		cout << "|-----------------------------------------------------------|" << endl;
		cout << "|                                                           |" << endl;
		cout << "| >   Order finished                                        |" << endl;
		cout << "|                                                           |" << endl;
		cout << "|-----------------------------------------------------------|" << endl;
		return;
	}
	else if (type == "bye")
	{
		system("cls");
		cout << "|===========================================================|" << endl;
		cout << "||  _____     ___  _____    ______      ____               ||" << endl;
		cout << "|| /__  /    |__ \\|__  /   / ____/___ _/ __/__             ||" << endl;
		cout << "||   / /_______/ / /_ <   / /   / __ `/ /_/ _ \\            ||" << endl;
		cout << "||  / /_____/ __/___/ /  / /___/ /_/ / __/  __/            ||" << endl;
		cout << "|| /_/   __/____/____/   _____/\\__,_/_/  \\___/             ||" << endl;
		cout << "||      | |     / /__  / /________  ____ ___  ___          ||" << endl;
		cout << "||      | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\         ||" << endl;
		cout << "||      | |/ |/ /  __/ / /__/ /_/ / / / / / /  __/         ||" << endl;
		cout << "||      |__/|__/\\___/_/\\___/\\\\___/_\\_/_\\ /_/\\___/          ||" << endl;
		cout << "||         ____  ___  _  __/ /_   / /_(_)___ ___  ___     /`/" << endl;
		cout << "||        / __ \\/ _ \\| |/_/ __/  / __/ / __ `__ \\/ _ \\   / /|" << endl;
		cout << "||       / / / /  __/>  </ /_   / /_/ / / / / / /  __/  /_/||" << endl;
		cout << "||      /_/ /_/\\___/_/|_|\\__/   \\__/_/_/ /_/ /_/\\___/  (_) ||" << endl;
		cout << "||                                                         ||" << endl;
		cout << "|===========================================================|" << endl;
		return;
	}

	cout << "|===========================================================|" << endl;
	cout << "|--------------------------CONSOLE--------------------------|" << endl;
	cout << "|                                                           |" << endl;
	if (type == "start")
	{
		cout << "| >   Start a new order?                                    |" << endl;
		cout << "|                                                           |" << endl;
		cout << "| 0 | Exit the system                                       |" << endl;
		cout << "| 1 | Start ordering                                        |" << endl;
	}
	else if (type == "order")
	{
		cout << "| >   Please order an item                                  |" << endl;
		cout << "|     (to order an item, enter the code before it)          |" << endl;
	}
	else if (type == "restart")
	{
		cout << "| >   Have you finish ordering?                             |" << endl;
		cout << "|                                                           |" << endl;
		cout << "| 0 | Order completed. Ready to check out                   |" << endl;
		cout << "| 1 | Continue this order                                   |" << endl;
	}
	else if (type == "OIS")
	{

		cout << "| >   What should we call you?                              |" << endl;
		cout << "|     (please enter one word with less than 40 characters)  |" << endl;
	}

	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
	cout << "| >   ";
}


string enterIC()
{
	/*
	This function ask the user to enter or re-enter an valid Item Code and reutrn it.
	*/

	string item_code;
	bool is_code_valid = false;

	while (is_code_valid == false)
	{

		//order an item
		cin >> item_code;

		//check whether valid input
		for (int i = 0; i < 16; i++)
		{
			if (item_code == item_codes[i])
			{
				is_code_valid = true;
				break;
			}
		}

		//re-enter prompt
		if (is_code_valid == false)
		{
			cout << "|-----------------------------------------------------------|" << endl;
			cout << "|                                                           |" << endl;
			cout << "| >   Invalid System Command.                               |" << endl;
			cout << "|     Please enter again:                                   |" << endl;
			cout << "|                                                           |" << endl;
			cout << "| >   ";
		}
	}
	return item_code;
}


int getItemIndex(string IC)
{
	/*
	This function receive an item code and return the item's index in the menu(string list).
	ASCII(A): 65
	ASCII(S): 83
	ASCII(1): 49
	ASCII(5): 53
	*/

	switch (IC[0] * IC[1])
	{
	case 65 * 49: //A1
		return 0;
	case 65 * 50: //A2
		return 1;
	case 65 * 51: //A3
		return 2;

	case 66 * 49: //B1
		return 3;
	case 66 * 50: //B2
		return 4;
	case 66 * 51: //B3
		return 5;

	case 67 * 49: //C1
		return 6;
	case 67 * 50: //C2
		return 7;
	case 67 * 51: //C3
		return 8;
	case 67 * 52: //C4
		return 9;
	case 67 * 53: //C5
		return 10;

	case 83 * 49: //S1
		return 11;
	case 83 * 50: //S2
		return 12;
	case 83 * 51: //S3
		return 13;
	case 83 * 52: //S4
		return 14;
	case 83 * 53: //S5
		return 15;
	}
}


int howManyTypes()
{
	/*
	This function return the max index of order_list.
	To do this, function will scan order_list and see how many un-empty string in there.
	(mustn't use item_numbers for item_numbers is always updated quite late,
	when howManyTypes has already been called)
	*/

	int n_types = 0;
	for (int i = 0; i < 16; i++)
	{
		if (order_list[i] != "")
		{
			n_types++;
		}
	}

	return n_types;
}


void add2list(string IC)
{
	/*
	This function add food item whose item code is IC into order_list and update item_numbers.
	*/

	int item_index = getItemIndex(IC);

	//if the item has been ordered before:  update item_numbers
	if (item_numbers[item_index] > 0)
	{
		item_numbers[item_index]++;
	}

	//if hasn't been ordered before:  add to order_list & item_numbers
	else
	{
		//get the next empty position's index of order_list
		//(synonymous with "the total types of items been ordered")
		int n_types = howManyTypes();

		order_list[n_types] = IC;
		item_numbers[getItemIndex(IC)] = 1;
	}
}


void showOrderList(string OIS)
{
	/*
	This function show the ordered items, their individual prices, and the final total of the order.
	Any order that is over $100 has a 5% discount.
	The total should have a fixed precision to 2 digits after the decimal point.
	*/

	int n = (59 - OIS.length()) / 2;

	cout << "|                                                           |" << endl;

	//prompt user's OIS
	cout << "|" << setfill(' ') << setw(n) << " " << OIS + "'s";
	cout << setw(59 - OIS.length() - n - 2) << " "
		 << "|" << endl;

	cout << "|           ___         _           _    _    _             |" << endl;
	cout << "|          / _ \\ _ _ __| |___ _ _  | |  (_)__| |_           |" << endl;
	cout << "|         | (_) | '_/ _` / -_) '_| | |__| (_-<  _|          |" << endl;
	cout << "|          \\___/|_| \\__,_\\___|_|   |____|_/__/\\__|          |" << endl;
	cout << "|___________________________________________________________|" << endl;
	cout << "|                                                           |" << endl;

	//get the max index of order_list (synonymous with "the total types of items been ordered")
	int n_types = howManyTypes();

	double total_price = 0;
	for (int i = 0; i < n_types; i++)
	{
		string IC = order_list[i];
		int item_index = getItemIndex(IC);

		Oline(IC, menu[item_index], prices[item_index], item_numbers[item_index]);
		cout << "|    |                                                      |" << endl;

		total_price += prices[item_index] * item_numbers[item_index];
	}

	if (total_price > 100)
	{
		total_price *= 0.9;
	}

	//prompt total price
	cout << "|" << setw(38) << "" << "Total Price:  ";
	cout << setw(7) << fixed << setprecision(2) << total_price << "|" << endl;
	cout << "|                                                           |" << endl;
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
}


void packageItems()
{
	/*
	This function package the possible items in order_list into set meals.
	Also update order_list and item_numbers.
	*/

	bool sth_has_changed = true; //if nothing change after a whole loop of sets, end the while loop

	//get the max index of order_list (synonymous with "the total types of items been ordered")
	int n_types = howManyTypes();

	while (sth_has_changed)
	{
		sth_has_changed = false;

		//STEP0: see whether some items in order_list can gather a set meal
		//		 by comparing map "sets" with order_list 		
		for (auto i : sets) //Traverse the the map "sets"  e.g. {"A1":[0,1,2],"A2":[0,1],...}
		{
			
			int n = -1; //when n becomes 0 => a set has been gathered
			
			for (auto j : i.second) //Traverse the map "sets[i.first]"  e.g. {0:"item1",1:"item2",...}
			{

				for (int item_index = 0; item_index < n_types; item_index++) //Traverse order_list
				{
					string IC = order_list[item_index]; //item code of current item in order_list

					if (j.second == IC)
					{
						//if n hasn't been changed after initialize
						if (n == -1)
						{
							n = sets[i.first].size();
						}

						n--;
					}
				}
			}

			//a set is gathered
			if (n == 0)
			{
				sth_has_changed = true;

				//STEP1: decrease the quantity of the items in sets[i.first] by 1.
				for (auto j : i.second)
				{
					item_numbers[getItemIndex(j.second)]--;
				}

				//STEP2: update order_list
				//	1): delete the items whose quantity become 0
				for (int k = 0; k < n_types; k++)
				{
					string IC = order_list[k];
					if (item_numbers[getItemIndex(IC)] == 0)
					{
						order_list[k] = "";
					}
				}

				//	2): resort the order_list(move all empty strings to the end)
				string temp_list[16]; //a temp list to remember the items in order_list
				int temp_index = 0;

				for (int k = 0; k < n_types; k++)
				{
					if (order_list[k] != "")
					{
						temp_list[temp_index] = order_list[k];
						temp_index++;
					}
				}
				for (int k = 0; k < n_types; k++)
				{
					order_list[k] = temp_list[k];
				}

				//update n_types
				n_types = howManyTypes();

				//STEP3: if haven't order this new set meal yet, add it into order_list
				string set_name = i.first; //the name of current gathered set

				if (set_name.substr(0, 2) == "S5") //if the set is S5
				{
					set_name = set_name.substr(0, 2); // set_name: "S5*" -> "S5"
				}

				bool is_in_list = false;
				for (int k = 0; k < n_types; k++)
				{
					if (order_list[k] == set_name)
					{
						is_in_list = true;
						break;
					}
				}

				if (!is_in_list)
				{
					order_list[n_types] = set_name;
				}

				//update n_types
				n_types = howManyTypes();

				//STEP4: increase the number of the set meal in item_numbers;
				item_numbers[getItemIndex(set_name)]++;
			}
		}
	}
}


int main()
{

	cout << left; //Align left;

	init(); //initialize order_list, item_numbers, OIS and sets.

	//STEP 1: System welcome message
	welcome();
	showMenu();

	//STEP 2: Start or Exit system
	bool is_new_order = true;

	while (true)
	{
		//STEP2: haven't order anything
		if (is_new_order)
		{

			init(); //initialize order_list, item_numbers, OIS and sets.

			//Ask the user whether start order
			prompt("start");

			string command = enterSystemCommand(); //get user's command of input

			//CASE 1: Exit the System
			if (command == "0")
			{
				prompt("bye");
				break;
			}

			//CASE 2: Start Ordering( do nothing here.)
		}

		//STEP 4: order an item, then continue or complete
		else
		{
			//ask user whether to start ordering
			system("cls");
			showMenu();
			showOrderList(OIS);
			prompt("order"); 

			string item_code = enterIC();

			add2list(item_code);

			packageItems(); //package the possiable items into set meals

			//Ask the user whether finish ordering
			system("cls");
			showMenu();
			showOrderList(OIS);
			prompt("restart");

			string command = enterSystemCommand(); //get user's command of input

			//CASE 1: goto STEP 5

			//STEP 5: Order complete and check-out
			if (command == "0")
			{			

				system("cls");
				showMenu();
				showOrderList(OIS);
				prompt("finish");

				//STEP 6: goto STEP 2
				is_new_order = true;
			}

			//CASE 2: Continue this order (goto STEP 4)
			continue;
		}

		is_new_order = false;

		//STEP 3: input the OIS
		system("cls");
		showMenu();
		prompt("OIS");
		cin >> OIS;
	}
	system("pause");
}