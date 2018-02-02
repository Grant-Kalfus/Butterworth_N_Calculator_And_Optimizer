//Grant Kalfus || 4/12/17 || main.cpp
#include<iostream>
#include"FunctionProto.h"
#include<math.h>
#include<fstream>
#include<string>

using namespace std;

void helpMenu();


void main()
{
	string pass = "low";
	int    wMax = 2000,
		   wMin = 5000;
	double aMax = 2,
		   aMin = 45;
	string userInput = "";
	double userInput2 = 0.0;
	int    userInput3 = 0;
	int    userInput4 = 0;

	//"Input wPass, wStop, aMin, aMax, and pass(high/low)\n";
	cout << "Butterworth Filter Creater and Optimizer; Type help for commands\n";
	
	cout << "Input wPass: ";
	cin >> wMax;
	
	cout << "Input wStop: ";
	cin >> wMin;

	cout << "Input aMin: ";
	cin >> aMin;

	cout << "Input aMax: ";
	cin >> aMax;

	cout << "Input pass(high/low): ";
	cin >> pass;

	ButterworthFilter myFilter(wMax, wMin, aMax, aMin, pass);
	myFilter.dispValues();

	while (true)
	{
		cout << "Enter Command:\n";
		cin >> userInput;

		if (userInput == "dispValues")
		{
			myFilter.dispValues();
		}
		if (userInput == "help")
		{
			helpMenu();
		}
		else if (userInput == "exit")
		{
			break;
		}
		else if (userInput == "changeAMax")
		{
			cout << "Enter new AMax value: ";
			cin >> userInput2;
			cout << endl;
			myFilter.changeAMax(userInput2);
			myFilter.dispValues();
		}
		else if (userInput == "changeAMin")
		{
			cout << "Enter new AMin value: ";
			cin >> userInput2;
			myFilter.changeAMin(userInput2);
			myFilter.dispValues();
			cout << endl;
		}
		else if (userInput == "changeWStop")
		{
			cout << "Enter new stop band frequency (in Hz): ";
			cin >> userInput3;
			myFilter.changeWstop(userInput3);
			myFilter.dispValues();
			cout << endl;
		}
		else if (userInput == "changeWPass")
		{
			cout << "Enter new pass band frequency (in Hz): ";
			cin >> userInput3;
			myFilter.changewPass(userInput3);
			myFilter.dispValues();
			cout << endl;
		}
		else if (userInput == "changeType")
		{
			cout << "Enter new pass type (high/low): ";
			cin >> userInput;
			cout << endl;
			myFilter.changePass(userInput);
			myFilter.dispValues();
			cout << endl;
		}
		else if (userInput == "generateTfFilter")
		{
			cout << myFilter.generateTf() << endl;
		}
		else if (userInput == "generateTf")
		{
			cout << "Enter N, Wo, and type(high/low)\n";
			cout << "N: ";
			cin >> userInput3; 
			cout << endl;
			cout << "Wo: ";
			cin >> userInput4; 
			cout << endl;
			cout << "Type(high/low): ";
			cin >> userInput;
			cout << endl;
			generateTf(userInput3, userInput4, userInput);
			cout << endl;
		}
		else if (userInput == "sweepN")
		{
			cout << "Enter highest value, step from number to number, and variable to modify(aMax/aMin)\n";
			cout << "Mod(aMax/aMin): ";
			cin >> userInput;
			cout << "Highest Value: ";
			cin >> userInput3;
			cout << "Step: ";
			cin >> userInput2;
			myFilter.sweepN(userInput3, userInput2, userInput);
		}
	}



	
	//myFilter.sweepN(5, 0.2, "aMax");
	
	//cout << myFilter.generateTf() << endl;
}


void helpMenu() 
{
	cout << endl;
	cout << "changeAMax  \n";
	cout << "changeAMin  \n";
	cout << "changeWStop \n";
	cout << "changeWPass \n";
	cout << "changeType  \n";
	cout << "dispValues  \n";
	cout << "generateTfFilter  \n";
	cout << "generateTf  \n";
	cout << "sweepN      \n";
	cout << "exit      \n\n";
}