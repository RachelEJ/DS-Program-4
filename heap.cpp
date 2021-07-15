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
#include <iomanip>
#include <fstream>
#include <string>
#include "heap.h"
#include "project.h"

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::right;
using std::setfill;
using std::string;

// Constructor
Heap::Heap(int length)
{
	heapArray = new Project * [length];
	size = length;
	elements = 0;
}

// Destructor
Heap::~Heap()
{
	delete[] heapArray;
}

// Getter for Size
int Heap::getSize()
{
	return size;
}

// Getter for Elements
int Heap::getElements()
{
	return elements;
}

// Swaps 2 tasks in the heap
void Heap::swap(int &idx1, int &idx2)
{
	Project* temp = heapArray[idx1];
	heapArray[idx1] = heapArray[idx2];
	heapArray[idx2] = temp;
}

// Adds task to bottom of heap
void Heap::add(Project* task)
{
	heapArray[elements] = task;
	bubbleUp(elements);
	elements++;
}

// Removes task at top of heap
bool Heap::remove(Project* &task)
{
	if (elements == 0)
	{
		return false;
	}
	else if (elements == 1)
	{
		elements--;
		heapArray[0] = nullptr;
		return true;
	}
	else
	{
		elements--;
		task = heapArray[0];
		heapArray[0] = heapArray[elements];
		bubbleDown(0);
		return true;
	}
	
}

// Takes task at index and moves it up to its correct location based on priority
void Heap::bubbleUp(int index)
{
	if (index == 0) return;
	int parent = (index - 1) / 2;

	// lower priority int = higher location
	if (heapArray[index]->priority < heapArray[parent]->priority)
	{
		swap(index, parent);
		bubbleUp(parent);
	}

	// if priority is same with 2 tasks
	if (heapArray[index]->priority == heapArray[parent]->priority)
	{

		// lower arrival int = higher location
		if (heapArray[index]->arrival < heapArray[parent]->arrival)
		{
			swap(index, parent);
			bubbleUp(parent);
		}

		// if arrival is same with 2 tasks
		if (heapArray[index]->arrival == heapArray[parent]->arrival)
		{

			// higher elapsed int = higher location
			if (heapArray[index]->elapsed > heapArray[parent]->elapsed)
			{
				swap(index, parent);
				bubbleUp(parent);
			}

			// if elapsed is same with 2 tasks
			if (heapArray[index]->elapsed == heapArray[parent]->elapsed)
			{

				// lower name string = higher location
				if (heapArray[index]->name < heapArray[parent]->name)
				{
					swap(index, parent);
					bubbleUp(parent);
				}
				// can't have duplicates with this one
			}
		}
	}
}
	
// Takes task at top and moves it down to its correct location
void Heap::bubbleDown(int index)
{
	int max = index;
	int left = 2 * index + 1;
	int right = left + 1;

	// sets "max" task to either the left or right tasks depending on their values
	if (left > elements - 1) return;
	if (right > elements - 1) { max = left; }
	else 
	{
		// lower priority int = higher location
		if (heapArray[left]->priority < heapArray[right]->priority)
		{
			max = left;
		}

		// if priority is same with 2 tasks
		else if (heapArray[left]->priority == heapArray[right]->priority)
		{
			// lower arrival int = higher location
			if (heapArray[left]->arrival < heapArray[right]->arrival)
			{
				max = left;
			}

			// if arrival is same with 2 tasks
			else if (heapArray[left]->arrival == heapArray[right]->arrival)
			{

				// higher elapsed int = higher location
				if (heapArray[left]->elapsed > heapArray[right]->elapsed)
				{
					max = left;
				}
				
				// if elapsed is same with 2 tasks
				else if (heapArray[left]->elapsed == heapArray[right]->elapsed)
				{
					
					// lower name string = higher location
					if (heapArray[left]->name < heapArray[right]->name)
					{
						max = left;
					}
					else
					{
						max = right;
					}
					// can't have duplicates with this one
				}
				else
				{
					max = right;
				}
			}
			else
			{
				max = right;
			}
		}
		else
		{
			max = right;
		}
	}

	// redoes the comparisons except between the root and the set "max" task
	if (heapArray[index]->priority < heapArray[max]->priority)
	{
		max = index;
	}
	else if (heapArray[index]->priority == heapArray[max]->priority)
	{
		if (heapArray[index]->arrival < heapArray[max]->arrival)
		{
			max = index;
		}
		else if (heapArray[index]->arrival == heapArray[max]->arrival)
		{
			if (heapArray[index]->elapsed > heapArray[max]->elapsed)
			{
				max = index;
			}
			else
			{
				max = max;
			}
		}
		else
		{
			max = max;
		}
	}
	else
	{
		max = max;
	}
	if (max != index)
	{
		// swaps tasks at index
		swap(index, max);
		bubbleDown(max);
	}
}

// Resizes the heap. Didn't actually need this function but I included it anyway
void Heap::reallocate()
{
	Project** old = heapArray;
	size *= 2;
	heapArray = new Project * [size];
	for (int i = 0; i < elements; i++)
	{
		heapArray[i] = old[i];
	}
	delete[] old;
}

// Display Simulator Function
void Heap::displaySim(vector<Project*> taskList, int timeStep)
{
	// my fancy table data
	const char separator = ' ';
	const int info = 13;

	// displays next step
	if (timeStep == -1)
	{
		cout << left << setw(info) << setfill(separator) << "Next Step " << "= " << 0 << endl;
	}
	else
	{
		cout << left << setw(info) << setfill(separator) << "Next Step " << "= " << timeStep << endl;
	}

	// displays current task
	cout << left << setw(info) << setfill(separator) << "Current Task " << "= ";
	if (elements == 0)
	{
		cout << "None" << endl;
	}
	else
	{
		cout << heapArray[0]->name << " @ " << heapArray[0]->priority << " for " << heapArray[0]->elapsed << " out of " << heapArray[0]->length << " arriving at " << heapArray[0]->arrival << endl;
	}

	// displays unscheduled tasks
	cout << "Tasks yet to be scheduled" << endl;
	for (int i = 0; i < taskList.size(); i++)
	{
		cout << "\t" << taskList[i]->name << " @ " << taskList[i]->priority << " for " << taskList[i]->elapsed << " out of " << taskList[i]->length << " arriving at " << taskList[i]->arrival << endl;
	}
	cout << endl;
}

// Single Step Function
bool Heap::stepSingle(vector<Project*>& taskList, int &timeStep, bool &mode)
{
	const char separator = ' ';
	const int titles = 13;
	const int rightCol = 15;

	// checks if the heap and task are empty
	if ((elements == 0) && (taskList.size() == 0))
	{
		cout << "There are currently no tasks running, waiting to be scheduled, or waiting to execute." << endl;
		cout << "Returning to Scheduling mode..." << endl << endl;
		mode = false;
		timeStep == -1;
		return false;
	}

	// adds 1 to the -1 timestep for aesthetic reasons
	if (timeStep == -1)
	{
		timeStep++;
	}

	// displays current time step
	cout << left << setw(titles) << setfill(separator) << "Time Step " << "= " << timeStep << endl;

	// adds tasks with arrival value equal to time step
	int addCount = 0;
	for (int i = 0; i < taskList.size(); i++)
	{
		if (taskList[i]->arrival == timeStep)
		{
			add(taskList[i]);
			cout << right << setfill(separator) << setw(rightCol) << "Added " << taskList[i]->name << " @ " << taskList[i]->priority << " for " << taskList[i]->elapsed << " out of " << taskList[i]->length << " arriving at " << taskList[i]->arrival << endl;
			addCount++;
		}
	}
	// creates new vector without the tasks added in the last loop; basically removing elements without removing them
	if (addCount > 0)
	{
		vector<Project*> altTaskList;
		for (int i = 0; i < taskList.size(); i++)
		{
			if (taskList[i]->arrival != timeStep)
			{
				altTaskList.push_back(taskList[i]);
			}
		}
		taskList.clear();
		taskList = altTaskList;
	}

	// displays current task when there are no elements
	if (elements == 0)
	{
		cout << left << setw(titles) << setfill(separator) << "Current Task " << "= None" << endl;
	}
	else 
	{
		// displays the finished task
		if (heapArray[0]->elapsed == heapArray[0]->length)
		{
			cout << left << setw(titles) << setfill(separator) << "" << "  " << heapArray[0]->name << " has finished" << endl;
			remove(heapArray[0]);
		}

		// displays the current task
		if (elements != 0)
		{
			heapArray[0]->elapsed++;
			cout << left << setw(titles) << setfill(separator) << "Current Task " << "= " << heapArray[0]->name << " @ " << heapArray[0]->priority << " for " << heapArray[0]->elapsed << " out of " << heapArray[0]->length << " arriving at " << heapArray[0]->arrival << endl;

		}

		// displays the current task when it doesn't exist but there are still things to schedule and stuff
		else
		{
			if (elements != 0 && taskList.size() != 0)
			{
				cout << left << setw(titles) << setfill(separator) << "Current Task " << "= " << "None" << endl;
			}
		}
	}

	// increments the time step
	timeStep++;
	cout << endl;
	return true;
}

// Multiple Step Function calls stepSingle() however many times the user said to
bool Heap::stepMultiple(vector<Project*>& taskList, int& timeStep, bool& mode, int stepNum)
{
	for (int i = 0; i < stepNum; i++)
	{
		if (stepSingle(taskList, timeStep, mode) == false)
		{
			return false;
		}
	}
	return true;
}

// Full Run Function does all the steps
bool Heap::runFull(vector<Project*>& taskList, int& timeStep, bool& mode)
{
	// when time step is -1 you gotta add extra steps
	int run = 1;

	// finds minimum arrival time
	if (elements == 0)
	{
		int min = taskList[0]->arrival;
		for (int i = 0; i < taskList.size(); i++)
		{
			if (taskList[i]->arrival < min)
			{
				min = taskList[i]->arrival;
			}
		}

		// adds it to the run integer
		run += min;
	}

	// adds up lengths of all tasks in the heap and vector
	for (int i = 0; i < elements; i++)
	{
		run = run + (heapArray[i]->length - heapArray[i]->elapsed);
	}
	for (int i = 0; i < taskList.size(); i++)
	{
		run = run + (taskList[i]->length - taskList[i]->elapsed);
	}

	// basically just calls stepMultiple() until it's done
	if (stepMultiple(taskList, timeStep, mode, run) == 0)
	{
		return false;
	}
	return true;
}

// Number Run Function calls single step until the time step matches the user's specified run time
bool Heap::runNum(vector<Project*>& taskList, int& timeStep, bool& mode, int runTime)
{
	// it acts weirdly at the beginning so it gets special treatment
	if (timeStep == -1)
	{
		// starts with tempTS being equal to timeStep before calling stepSingle()
		int tempTS = timeStep;
		while (tempTS < runTime)
		{
			if (stepSingle(taskList, timeStep, mode) == false)
			{
				return false;
			}
			tempTS++;
		}
	}
	else
	{
		// subtracts 1 from time step
		int tempTS = timeStep - 1;
		while (tempTS < runTime)
		{
			// also calling stepSingle()
			if (stepSingle(taskList, timeStep, mode) == false)
			{
				return false;
			}
			tempTS++;
		}
	}
	return true;
}

// clears the heap, sets the time step to -1, and sets all elapsed values back to 0
void Heap::reset(vector<Project*>& taskList, vector<Project*> taskList2, int& timeStep)
{
	timeStep = -1;
	int resetCount = elements;
	if (elements != 0)
	{
		for (int i = 0; i < resetCount; i++)
		{
			remove(heapArray[i]);
		}
	}
	taskList.clear();
	taskList = taskList2;
	for (int i = 0; i < taskList.size(); i++)
	{
		taskList[i]->elapsed = 0;
	}
}