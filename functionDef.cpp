//Grant Kalfus || 4/12/17 || FunctionDef.cpp
#include"FunctionProto.h"



ButterworthFilter::ButterworthFilter()
{
	wPass = 100;
	wStop = 150;
	aMax = 60;
	aMin = 3;
	type = "low";
	n = calcN();
	e = calcE();
	Wo = calcWo();
}

ButterworthFilter::ButterworthFilter(int wPass_1, int wStop_1, double aMax_1, double aMin_1, std::string pass, bool rad)
{
	if (rad == false)
	{
		wPass = round(static_cast<double>(wPass_1) * (2.0 * 3.14159));
		wStop = round(static_cast<double>(wStop_1) * (2.0 * 3.14159));
	}
	else
	{
		wPass = wPass_1;
		wStop = wStop_1;
	}

	aMax = aMax_1;
	aMin = aMin_1;
	type = pass; 
	n = calcN();
	e = calcE();
	Wo = calcWo();
}

void ButterworthFilter::changeAMax(double x)
{
	aMax = x;
	n = calcN();
	e = calcE();
	Wo = calcWo();
}

void ButterworthFilter::changeAMin(double x)
{
	aMin = x;
	n = calcN();
	e = calcE();
	Wo = calcWo();
}

void ButterworthFilter::changeWstop(int x)
{
	wStop = x;
	n = calcN();
	e = calcE();
	Wo = calcWo();
}

void ButterworthFilter::changePass(std::string x)
{
	type = x;
	n = calcN();
	e = calcE();
	Wo = calcWo();
}

void ButterworthFilter::changewPass(int x)
{
	wPass = x;
	n = calcN();
	e = calcE();
	Wo = calcWo();
}


int ButterworthFilter::round(double x)
{
	int temp = 0;

	if ((x + 0.5) >= (int(x) + 1))
		temp = int(x) + 1;
	else
		temp = int(x);
	
	return temp;
}

void ButterworthFilter::dispValues()
{
	std::cout << std::endl;
	std::cout << "Type is " << type << " pass filter" << std::endl;
	std::cout << "N is: " << n << std::endl;
	std::cout << "E is: " << e << std::endl;
	std::cout << "Wo is: " << Wo << " rad/sec" << std::endl;
	std::cout<<  "Wo is: " << round(double(Wo)/(3.14159*2)) << " Hz" << std::endl;
}


int ButterworthFilter::calcN()
{
	double    top    = 0.0,
		      bottom = 0.0,
		      temp   = 0.0;


	top = pow(10, (0.1 * aMin));
	top = top - 1;


	bottom = pow(10, (0.1 * aMax));
	bottom = bottom - 1;

	top = log10(top / bottom);

	if (type == "low")
		bottom = 2.0 * log10(static_cast<double>(wStop) / static_cast<double>(wPass));
	else if (type == "high")
		bottom = (2.0 * log10(static_cast<double>(wPass) / static_cast<double>(wStop)));

	temp = top / bottom;

	 return int(temp) + 1;

}

double ButterworthFilter::calcE()
{
	e = pow(10, (0.1 * aMax)) - 1;

	if (type == "low")
		e = sqrt(e);
	else
		e = sqrt(pow(e, -1));
	
	return e;
}

int ButterworthFilter::calcWo()
{
	double temp = 0;

	temp = static_cast<double>(wPass) / pow(e, (1.0 / static_cast<double>(n)));

	return round(temp);

}

std::string ButterworthFilter::generateTf()
{
	std::string totalTf = "(";
	std::stringstream convert;

	if (n > 16)
		return "N/A";

	if (type == "high")
	{
		
		totalTf += "(s)^";
		convert << n;
		totalTf += (convert.str() + " / (");
		convert.str("");

	}
	else if (type == "low")
	{
		convert << Wo;
		totalTf += (convert.str() + ")^");
		convert.str("");
		
		convert << n;
		totalTf += (convert.str() + " / (");
		convert.str("");
	}
		
	
	if (n % 2 == 1)
	{
		for (int i = 0; i < (n/2); i++)
		{
			totalTf += "(s^2 + ";

			convert << ((1.0 / getQ(n, (i + 1))) * static_cast<float>(Wo));
			totalTf += (convert.str() + "s");
			convert.str("");

			totalTf += " + ";

			convert << Wo;
			totalTf += convert.str();
			totalTf += "^2)";
			convert.str("");
		}
		totalTf += "(s + ";
		convert << Wo;
		totalTf += (convert.str() + ")");
		convert.str("");
		totalTf += ")";
	}
	else if (n % 2 == 0)
	{
		
		for (int i = 0; i < n/2; i++)
		{
			totalTf += "(s^2 + ";
			
			convert << ((1.0 / getQ(n, (i + 1))) * static_cast<float>(Wo));
			totalTf += (convert.str() + "s");
			convert.str("");

			totalTf += " + ";

			convert << Wo;
			totalTf += convert.str();
			totalTf += "^2)";
		    convert.str("");
		}
		totalTf += ")";
	}
	return totalTf;
}

std::string generateTf(int n, int Wo, std::string type)
{
	std::string totalTf = "(";
	std::stringstream convert;

	if (n > 16)
		return "N/A";

	if (type == "high")
	{

		totalTf += "(s)^";
		convert << n;
		totalTf += (convert.str() + " / (");
		convert.str("");

	}
	else if (type == "low")
	{
		convert << Wo;
		totalTf += (convert.str() + ")^");
		convert.str("");

		convert << n;
		totalTf += (convert.str() + " / (");
		convert.str("");
	}


	if (n % 2 == 1)
	{
		for (int i = 0; i < (n / 2); i++)
		{
			totalTf += "(s^2 + ";

			convert << ((1.0 / getQ(n, (i + 1))) * static_cast<float>(Wo));
			totalTf += (convert.str() + "s");
			convert.str("");

			totalTf += " + ";

			convert << Wo;
			totalTf += convert.str();
			totalTf += "^2)";
			convert.str("");
		}
		totalTf += "(s + ";
		convert << Wo;
		totalTf += (convert.str() + ")");
		convert.str("");
		totalTf += ")";
	}
	else if (n % 2 == 0)
	{

		for (int i = 0; i < n / 2; i++)
		{
			totalTf += "(s^2 + ";

			convert << ((1.0 / getQ(n, (i + 1))) * static_cast<float>(Wo));
			totalTf += (convert.str() + "s");
			convert.str("");

			totalTf += " + ";

			convert << Wo;
			totalTf += convert.str();
			totalTf += "^2)";
			convert.str("");
		}
		totalTf += ")";
	}
	return totalTf;
}

void ButterworthFilter::sweepN(int high, double step, std::string type)
{
	std::cout << std::endl;
	int temp = 0;
	double taMax = aMax;
	double taMin = aMin;
	double best[2] = { 0,0 };
	char ans = 'a';

	if (type == "aMax")
	{
		std::cout << "Shifting values of aMax...\n";

		for (double i = 1; i < high + 1; i += step)
		{
			aMax = i;
			temp = calcN();
			std::cout << "With aMax of: " << aMax << ", N of " << temp << " is obtained!\n";
			if (temp < int(best))
			{
				best[0] = double(temp);
				best[1] = aMax;
			}
		}
		aMax = taMax;
		/*
		std::cout << "Best aMax found at: " << best[1] << ", with an N value of " << best[0] << std::endl;
		std::cout << "Change to best fit? (y/n)\n";
		std::cin >> ans;
		std::cout << std::endl;

		if (ans == 'y')
		{
			aMax = best[1];
			n = int(best[0]);
			std::cout << "Done!\n";
		}
		else
		{
			aMax = taMax;
		}
		*/
	}
	else if (type == "aMin")
	{
		std::cout << "Shifting values of aMin...\n";

		for (double i = 1; i < high + 1; i += step)
		{
			aMin = i;
			temp = calcN();
			std::cout << "With aMin of: " << aMin << ", N of " << temp << " is obtained!\n";
		}
		aMin = taMin;
	/*		if (temp < int(best))
			{
				best[0] = double(temp);
				best[1] = aMin;
			}
		}

		std::cout << "Best aMinfound at: " << best[1] << ", with an N value of " << best[0] << std::endl;
		std::cout << "Change to best fit? (y/n)\n";
		std::cin >> ans;
		std::cout << std::endl;

		if (ans == 'y')
		{
			aMin = best[1];
			n = int(best[0]);
			std::cout << "Done!\n";
		}
		else
		{
			aMax = taMax;
		}
		*/
	}

}



double getQ(int max, int row)
{
	double Q = 0;

	if (max == 2) 
		Q = 0.71;
	else if (max == 3)
		Q = 1;
	else if (max == 4) 
	{
		if (row == 1)
			Q = 0.54;
		else if(row == 2)
			Q = 1.31;
	}
	else if (max == 5)
	{
		if (row == 1)
			Q = 0.62;
		else if (row == 2)
			Q = 1.62;
	}
	else if (max == 6)
	{
		if (row == 1)
			Q = 0.52;
		else if (row == 2)
			Q = 0.71;
		else if (row == 3)
			Q = 1.93;
	}
	else if (max == 7)
	{
		if (row == 1)
			Q = 0.55;
		else if (row == 2)
			Q = 0.80;
		else if (row == 3)
			Q = 2.24;
	}
	else if (max == 8)
	{
		if (row == 1)
			Q = 0.51;
		else if (row == 2)
			Q = 0.60;
		else if (row == 3)
			Q = 0.90;
		else if (row == 4)
			Q = 2.56;
	}
	else if (max == 9)
	{
		if (row == 1)
			Q = 0.53;
		else if (row == 2)
			Q = 0.65;
		else if (row == 3)
			Q = 1.00;
		else if (row == 4)
			Q = 2.88;
	}
	else if (max == 10)
	{
		if (row == 1)
			Q = 0.51;
		else if (row == 2)
			Q = 0.56;
		else if (row == 3)
			Q = 0.71;
		else if (row == 4)
			Q = 1.10;
		else if (row == 5)
			Q = 3.20;
	}
	else if (max == 11)
	{
		if (row == 1)
			Q = 0.52;
		else if (row == 2)
			Q = 0.59;
		else if (row == 3)
			Q = 0.76;
		else if (row == 4)
			Q = 1.20;
		else if (row == 5)
			Q = 3.51;
	}
	else if (max == 12)
	{
		if (row == 1)
			Q = 0.50;
		else if (row == 2)
			Q = 0.54;
		else if (row == 3)
			Q = 0.63;
		else if (row == 4)
			Q = 0.82;
		else if (row == 5)
			Q = 1.31;
		else if (row == 6)
			Q = 3.83;
	}
	else if (max == 13)
	{
		if (row == 1)
			Q = 0.51;
		else if (row == 2)
			Q = 0.56;
		else if (row == 3)
			Q = 0.67;
		else if (row == 4)
			Q = 0.88;
		else if (row == 5)
			Q = 1.41;
		else if (row == 6)
			Q = 4.15;
	}
	else if (max == 14)
	{
		if (row == 1)
			Q = 0.50;
		else if (row == 2)
			Q = 0.53;
		else if (row == 3)
			Q = 0.59;
		else if (row == 4)
			Q = 0.71;
		else if (row == 5)
			Q = 0.94;
		else if (row == 6)
			Q = 1.51;
		else if (row == 7)
			Q = 4.47;
	}
	else if (max == 15)
	{
		if (row == 1)
			Q = 0.51;
		else if (row == 2)
			Q = 0.56;
		else if (row == 3)
			Q = 0.62;
		else if (row == 4)
			Q = 0.75;
		else if (row == 5)
			Q = 1.00;
		else if (row == 6)
			Q = 1.61;
		else if (row == 7)
			Q = 4.78;
	}
	else if (max == 16)
	{
		if (row == 1)
			Q = 0.50;
		else if (row == 2)
			Q = 0.52;
		else if (row == 3)
			Q = 0.57;
		else if (row == 4)
			Q = 0.65;
		else if (row == 5)
			Q = 0.79;
		else if (row == 6)
			Q = 1.06;
		else if (row == 7)
			Q = 1.72;
		else if (row == 8)
			Q = 5.10;
	}

	return Q;
}

