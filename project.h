/*
Student Name: Rachel Jordan
Student NetID: rej168
Compiler: Visual Studio
Program Description: Program that simulates preemptive scheduling with a heap and a vector.
*/

#pragma once
#include <string>
#include <iostream>
#include <ostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;

class Project
{
public:
	// data
	string name;
	int priority;
	int length;
	int elapsed;
	int arrival;

	// constructors
	Project() : name(""), priority(0), length(0), elapsed(0), arrival(0) {}
	Project(string name, int priority, int length, int arrival) : name(name), priority(priority), length(length), elapsed(0), arrival(arrival) {}
	Project(string name, int priority, int length, int elapsed, int arrival) : name(name), priority(priority), length(length), elapsed(elapsed), arrival(arrival) {}
};