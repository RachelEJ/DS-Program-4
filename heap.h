/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that simulates preemptive scheduling with a heap and a vector.
*/

#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "project.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ostream;

class Heap
{
private:
	// data
	Project** heapArray;
	int size;
	int elements;

	// operations
	void bubbleUp(int idx);
	void bubbleDown(int idx);
	void swap(int &idx1, int &idx2);

	// resize
	void reallocate();

public:
	// constructor and destructor
	Heap(int length);
	~Heap();

	// getters
	int getSize();
	int getElements();

	// add and remove
	void add(Project* task);
	bool remove(Project*& task);

	// display
	void displaySim(vector<Project*> taskList, int timeStep);

	// the reset button
	void reset(vector<Project*>& taskList, vector<Project*> taskList2, int& timeStep);

	// the step-related functions
	bool stepSingle(vector<Project*>& taskList, int& timeStep, bool& mode);
	bool stepMultiple(vector<Project*>& taskList, int& timeStep, bool& mode, int stepNum);
	bool runFull(vector<Project*>& taskList, int& timeStep, bool& mode);
	bool runNum(vector<Project*>& taskList, int& timeStep, bool& mode, int runTime);
};