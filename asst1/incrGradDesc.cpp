#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

void readData(vector<double> &input, vector<double> &output);
double calculateGradient(double input, double output, vector<double> theta, 
		int index);
void shuffle(vector<double> &input, vector<double> &output);

int main()
{
	vector<double> input, output, theta, gradientOld(2), gradientCurr;
	double alpha = 0.0001;
	int j = 0;

	//set theta_0, theta_1 to 1
	theta.push_back(0);
	theta.push_back(0);

	//set gradientOld of theta_0 and theta_1 to a large number
	gradientCurr.push_back(10000);
	gradientCurr.push_back(10000);

	readData(input, output);

	do
	{
		cout << "Epoch " << j << ": " << endl;
		shuffle(input, output);

		for(int i = 0; i < input.size(); i++)
		{
			//Save Gradient from last iteration
			gradientOld[0] = gradientCurr[0];
			gradientOld[1] = gradientCurr[1];
			
			//Update Gradient
			gradientCurr[0] = 
				calculateGradient(input[i], output[i], theta, 0);
			gradientCurr[1] = 
				calculateGradient(input[i], output[i], theta, 1);

			theta[0] = theta[0] + alpha*gradientCurr[0];
			theta[1] = theta[1] + alpha*gradientCurr[1];

//			if((fabs(gradientCurr[0]) < 0.01) && 
//			(fabs(gradientCurr[1]) < 0.01))
//			{
//				break;
//			}
		}
	
		cout << "\tNew Gradient for Theta_0: " << gradientCurr[0] 
			<< endl;
		cout << "\tNew Gradient for Theta_1: " << gradientCurr[1] 
			<< endl;
	
		cout << "\tNew Theta_0: " << theta[0] << endl;
		cout << "\tNew Theta_1: " << theta[1] << endl;
		
		// Update the Epoch Count
		j++;
	}while((fabs(gradientCurr[0]) >= 0.01) || 
			(fabs(gradientCurr[1]) >= 0.01));

	cout << "Gradient at step k and step k-1 are similar to " 
		<< "two decimal places. " << endl;

	return 0;
}

double calculateGradient(double input, double output, vector<double> theta,
		int index)
{
	return (output - (theta[0] + theta[1]*input))
		*(index==0 ? 1 : input);
}

void readData(vector<double> &input, vector<double> &output)
{
	ifstream inFile("data1.txt");

	if(!inFile)
	{
		cerr << "Unable to open file." << endl;
		return;
	}

	double x,y;

	while(inFile >> x)
	{
		input.push_back(x);
		inFile >> y;
		output.push_back(y);
	}
}

void shuffle(vector<double> &input, vector<double> &output)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, input.size()-1);

	for(int i = 0; i < input.size(); i++)
	{
		double temp;
		int firstSwapIndex = distribution(generator);
		int secondSwapIndex = distribution(generator);

		temp = input[firstSwapIndex];
		input[firstSwapIndex] = input[secondSwapIndex];
		input[secondSwapIndex] = temp;

		temp = output[firstSwapIndex];
		output[firstSwapIndex] = output[secondSwapIndex];
		output[secondSwapIndex] = temp;
	}
}
