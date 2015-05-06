// Program to calculate the new pressure at a sprinkler head.
#include <iostream>
#include <cmath>
using namespace std;

void OutputAnswer(double pressure, double newq)
	{

	cout << "\nThe pressure (P) at this node is " << pressure << endl;
	cout << "The flow (Q) at this node is " << newq << endl;

	cout << "\nTo run the program again type any character and press enter. ";
	char zzz;
	cin >> zzz;
	cout << endl << endl;
	}

//Function for branches.
void CalculateBranch(double pressureprevious, double kprevious, double k, double pipeLength, double diameter)
	{
	// P5 + [P5^1.85/2]*[0.00064*L*(K5^1.85)/(d^4.8655)] - P4 = 0
	double pressure = 7;
	for (double count = pressure; count <= pressureprevious ; count + 0.0001)
		{
		pressure = pressure + 0.0001;
		double LHS = pressure + pow(pressure, 1.85/2)*0.00064*pipeLength*pow(k, 1.85)/pow(diameter, 4.8655) - pressureprevious;
		//double check = trunc(LHS * 100) / 100;
		//if (check == 0.000)
		if (LHS >= -0.001 && LHS <= 0.001)
			{
			double newq = k*sqrt(pressure);
			OutputAnswer(pressure, newq);
			break;
			}	
		}
	}

void CalculateNode(double pressureprevious, double q, double kprevious, double k, double pipeLength, double diameter)
	{
	// Find flow of previous pipe.
	double qprevious = kprevious*sqrt(pressureprevious);

	if (qprevious == 0)
		{
		qprevious = q;
		}

	//double friction = 0.002083 * pipeLength * pow(100/C, 1.85) * (pow(qprevious, 1.85) / pow(diameter, 4.8655));
	double h = 0.00064*pipeLength*pow(qprevious,1.85)/pow(diameter, 4.8655);

	// Pressure at the current node is pressure of previous node + pressure loss at that node.
	double pressure = h + pressureprevious;

	// New Q. 
	double newq = k*sqrt(pressure);
	
	OutputAnswer(pressure, newq);
	}



void GetInfo()
	{
	// Introduction to the program.
	//cout << "\nProgram for sprinkler system calculations." << endl << endl;	

	// Ask user which node we're dealing with. 
	int x; 
	cout << "If the node we're calculating is on a branch, type 1. \nIf the node isn't on a branch, type 2. ";
	cin >> x; 
	
	if (x == 1 || x == 2)
		{
		}
	else
		{
		cout << "\nError. Please enter the number 1 or the number 2." << endl;
		GetInfo();
		}

	// Ask for the input values.
	double pressure;
	cout << "\nEnter the pressure of the previous node. ";
	cin >> pressure;
		
	double q;
	cout << "Enter the Q of the previous node. ";
	cin >> q;

	double pk;
	cout << "Enter the K value for your previous node. ";
	cin >> pk;

	double k;
	cout << "Enter the K value for your current node. ";
	cin >> k;

	double pipeLength;
	cout << "Enter the pipe length in feet (convert any inches to a decimal). ";
	cin >> pipeLength;

	double diameter;
	cout << "Enter the diameter of your pipe (inches). ";
	cin >> diameter;

	// Pass the values into the calculate function.
	if (x == 1)
		{
		CalculateBranch(pressure, pk, k, pipeLength, diameter);
		}
	else 
		{
		CalculateNode(pressure, q,  pk, k, pipeLength, diameter);
		}
	}

int main()
	{
	GetInfo();
	return main();
	}