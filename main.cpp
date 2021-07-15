/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that simulates preemptive scheduling with a heap and a vector.
*/

#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include "heap.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::istream;
using std::ifstream;
using std::stringstream;

// Register Task Function; Creates a task from the input given
bool registerTask(vector<Project*>& taskList, vector<Project*>& taskList2, string tName, int tPri, int tLen, int tArr)
{
	// search if task already exists
	for (int i = 0; i < taskList.size(); i++)
	{
		if (taskList[i]->name == tName)
		{
			cout << "Task " << tName << " has already been registered. Remove it first." << endl << endl;
			return false;
		}
	}

	// next 3 if statements check the integers for validity
	if (tPri < 0 || tPri > 100)
	{
		cout << "Failed to register task! Priority must be between 1 - 100." << endl << endl;
		return false;
	}

	if (tLen < 0)
	{
		cout << "Failure to register task! Length of task must be positive." << endl << endl;
		return false;
	}

	if (tArr < 0)
	{
		cout << "Failure to register task! Arrival time cannot be negative." << endl << endl;
		return false;
	}

	// Actually creating and putting the tasks in the vector
	Project* temp = new Project(tName, tPri, tLen, tArr);
	taskList.push_back(temp);
	cout << "Task " << tName << " has been registered." << endl << endl;
	return true;
}

// Remove Task Function; takes in name of task and searches through vector to delete it
bool removeTask(vector<Project*>& taskList, string tName)
{
	for (int i = 0; i < taskList.size(); i++)
	{
		if (taskList[i]->name == tName)
		{
			delete taskList[i];
			taskList.erase(taskList.begin() + i);
			cout << "Task " << tName << " has been removed from scheduling" << endl << endl;
			return true;
		}
	}
	// when it doesn't exist
	cout << "Task " << tName << " does not exist." << endl << endl;
	return false;
}

// Display Schedule Function; prints out everything in the scheduling vector
void displaySchedule(vector<Project*> taskList)
{
	cout << "Tasks yet to be scheduled" << endl;
	// in case there are no tasks yet
	if (taskList.size() == 0)
	{
		cout << "\t" << "No tasks have been entered" << endl << endl;
		return;
	}
		
	// actually prints useful info
	else
	{
		for (int i = 0; i < taskList.size(); i++)
		{
			cout << "\t" << taskList[i]->name << " @ " << taskList[i]->priority << " for " << taskList[i]->elapsed << " out of " << taskList[i]->length << " arriving at " << taskList[i]->arrival << endl;
		}
	}
}

// Parsing Function that reads all commands and calls functions accordingly; it's really long
void readLines(istream& is, bool isFile, bool mode, int timeStep, vector<Project*>& taskList, vector<Project*>& taskList2, Heap& pQueue)
{
	while (true)
	{
		string line;
		string cmd;
		string arg1;
		string arg2;
		string arg3;
		string arg4;
		if (isFile && is.eof()) return;
		if (isFile == false)
		{
			if (mode == 0)
			{
				cout << "scheduling >> ";
			}
			else
			{
				cout << "simulation >> ";
			}
		}
		getline(is, line);
		stringstream ss(line);
		getline(ss, cmd, ' ');
		if (isFile == false)
		{
			cout << endl;
		}

		// Exits the program
		if (cmd == "exit") return;

		// Loads up a file and processes it
		if (cmd == "load")
		{

			// makes sure the user actually typed a file name in
			ifstream inFile;
			if (!getline(ss, arg1, ' '))
			{
				cout << "You must specify a file to open. Please try again" << endl << endl;
			}
			else
			{
				// opens and processes the file
				inFile.open(arg1);
				cout << "Attempting to open file..." << endl << endl;
				if (inFile.is_open())
				{
					readLines(inFile, true, mode, timeStep, taskList, taskList2, pQueue);
					cout << "File opened successfully" << endl << endl;
				}
				else
				{
					// whoa it didn't open
					cout << "Failed to open the file" << endl << endl;
				}
				inFile.close();
			}
		}

		// Simulate Mode Function; sets the mode to Simulation Mode. Shocker. 
		if (cmd == "simulate")
		{
			if (mode == true)
			{
				cout << "You're already in Simulation Mode. What do you want?" << endl << endl;
			}
			else
			{
				// also creates the heap and makes it the right size
				cout << "Switching to Simulation Mode..." << endl << endl;
				mode = true;
				taskList2 = taskList;
				pQueue = Heap(taskList.size()+1);
				
				//readLines(cin, false, mode, timeStep, taskList, taskList2, pQueue);
			}
		}

		// Schedule Mode Function; sets the mode to Scheduling Mode. Shocker. 
		if (cmd == "schedule")
		{
			if (mode == false)
			{
				cout << "You're already in Scheduling Mode. What do you want?" << endl << endl;
			}
			else
			{
				// also deletes the heap and resets the time steps
				//pQueue.~Heap();
				//timeStep = -1;
				pQueue.reset(taskList, taskList2, timeStep);
				taskList.clear();
				cout << "Clearing priority queue..." << endl << endl;
				cout << "Switching to Scheduling Mode..." << endl << endl;
				mode = false;
			}
		}

		// Display Command calls Display Function depending on mode
		if (cmd == "display")
		{
			if (mode == 0)
			{
				displaySchedule(taskList);
				cout << endl;
			}
			else if (mode == 1)
			{
				pQueue.displaySim(taskList, timeStep);
			}
			else
			{
				cout << "An error has occurred. Please try again" << endl << endl;
			}
		}

		// Register Task Command calls Register Task Function
		if (cmd == "register")
		{
			if (mode == 0)
			{
				if (!getline(ss, arg1, ' '))
				{
					cout << "You must specify a task name. Please try again." << endl << endl;
				}
				else
				{
					if (!getline(ss, arg2, ' '))
					{
						cout << "You must specify a task priority. Please try again." << endl << endl;
					}
					else
					{
						if (!getline(ss, arg3, ' '))
						{
							cout << "You must specify a task length. Please try again." << endl << endl;
						}
						else
						{
							// in case the user REALLY doesn't understand the task's values
							if (!getline(ss, arg4, ' '))
							{
								cout << "You must specify a task arrival. Please try again." << endl << endl;
							}
							else
							{
								// turns the strings into ints and catches the error if the string is just a regular string
								try
								{
									int arg2Int = stoi(arg2);
									int arg3Int = stoi(arg3);
									int arg4Int = stoi(arg4);
									registerTask(taskList, taskList2, arg1, arg2Int, arg3Int, arg4Int);
								}
								catch (...)
								{
									cout << "You must specify integers for priority, length, and arrival. Please try again" << endl << endl;
								}
							}
						}
					}
				}
			}
			else if (mode == 1)
			{
				cout << "You must be in Scheduling Mode to use this function. Please try again" << endl << endl;
			}
			else
			{
				cout << "An error has occurred. Please try again" << endl << endl;
			}
		}

		// Remove Command calls the Remove Function
		if (cmd == "remove")
		{
			if (mode == 0)
			{
				if (!getline(ss, arg1))
				{
					cout << "You must specify a task to remove. Please try again" << endl << endl;
				}
				else
				{
					removeTask(taskList, arg1);
				}
			}
			else if (mode == 1)
			{
				cout << "You must be in Scheduling Mode to use this function. Please try again" << endl << endl;
			}
			else
			{
				cout << "An error has occurred. Please try again" << endl << endl;
			}
			
		}

		// Clear Command calls the Clear Function on the 2 vectors
		if (cmd == "clear")
		{
			if (mode == 0)
			{
				taskList.clear();
				cout << "Scheduling vector has been cleared" << endl << endl;
			}
			else if (mode == 1)
			{
				cout << "You must be in Scheduling Mode to use this function. Please try again" << endl << endl;
			}
			else
			{
				cout << "An error has occurred. Please try again" << endl << endl;
			}
		}

		// Step Command calls the Step Functions depending on inputs
		if (cmd == "step")
		{
			if (mode == 0)
			{
				cout << "You must be in Simulation Mode to use this function. Please try again" << endl << endl;
			}
			else if (mode == 1)
			{
				if (!getline(ss, arg1))
				{
					pQueue.stepSingle(taskList, timeStep, mode);
				}
				else
				{
					// still converting strings to ints
					try
					{
						int arg1Int = stoi(arg1);
						pQueue.stepMultiple(taskList, timeStep, mode, arg1Int);
					}
					catch (...)
					{
						cout << "You must specify an integer as the number of steps to take. Please try again" << endl << endl;
					}
				}
			}
			else 
			{
				cout << "an error has occurred. Please try again" << endl << endl;
			}
		}

		// Run Command calls Run Functions based on user input
		if (cmd == "run")
		{
			if (mode == 0)
			{
				cout << "You must be in Simulation Mode to use this function. Please try again" << endl << endl;
			}
			else if (mode == 1)
			{
				if (!getline(ss, arg1, ' '))
				{
					// runs the whole thing until it's done
					pQueue.runFull(taskList, timeStep, mode);
				}
				else
				{
					// lot of things to check for in case the user isn't good at inputting stuff
					if (arg1 == "til")
					{
						if (!getline(ss, arg2, ' '))
						{
							cout << "You must specify a time step to run until. Please try again" << endl << endl;
						}
						else
						{
							try
							{
								int arg2Int = stoi(arg2);
								if (arg2Int < 0)
								{
									cout << "That time step is invalid. Please try again" << endl << endl;
								}
								else
								{
									if (arg2Int < timeStep)
									{
										cout << "Time step " << arg2 << " has already passed. Please try again" << endl << endl;
									}
									else if (arg2Int == timeStep-1)
									{
										cout << "The time step is currently " << arg2 << ". Please try again" << endl;
									}
									else
									{
										// runs until the time step requested is reached
										pQueue.runNum(taskList, timeStep, mode, arg2Int);
									}
								}
							}
							catch (...)
							{
								cout << "You must specify an integer as the time step to run until. Please try again" << endl << endl;
							}
						}
					}
					else
					{

						cout << "You must use the keyword \"til\" in order to use this command" << endl << endl;
					}
					
				}
			}
			else
			{
				cout << "An error has occurred. Please try again" << endl << endl;
			}
		}

		// Reset Command calls the Reset Function
		if (cmd == "reset")
		{
			if (mode == 0)
			{
				cout << "You must be in Simulation Mode to use this function. Please try again" << endl << endl;
			}
			else if (mode == 1)
			{
				timeStep = -1;
				pQueue.reset(taskList, taskList2, timeStep);
			}
			else
			{
				cout << "An error has occurred. Please try again" << endl << endl;
			}
		}
	}
}

// The very sparse Main Function
int main()
{
	// false is scheduling
	// true is simulation

	bool mode = false;
	int timeStep = -1;
	vector<Project*> taskList;
	vector<Project*> taskList2;
	Heap pQueue = Heap(0);

	readLines(cin, false, mode, timeStep, taskList, taskList2, pQueue);

	return 0;
}