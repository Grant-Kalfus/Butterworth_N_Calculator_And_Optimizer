//Grant Kalfus || 4/12/17 || FunctionProto.cpp
#pragma once
#include<math.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

class ButterworthFilter
{
public:
	
	ButterworthFilter();
	
	ButterworthFilter(int wPass, int wStop, double aMax, double aMin, std::string pass = "low", bool rad = false);
	
	void changeAMax(double x);

	void changeAMin(double x);

	void changeWstop(int x);

	void changePass(std::string x);

	void changewPass(int x);


	// Returns value of N for given variables
	int calcN();
	
	//Returns value of E for given variables
	double calcE();
	
	//Regurns corner frequency
	int calcWo();

	//rounds to nearest whole number
	int round(double x);

	void dispValues();

	//generates a transfer function
	std::string generateTf();

	void sweepN(int high, double step, std::string type = "aMax");



private:
	
	std::string type;
	
	double aMax;
	double aMin;
	int wStop;
	int wPass;
	
	int n; 
	double e;
	int Wo;
};

std::string generateTf(int n, int Wo, std::string type);

double getQ(int max, int row);