#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void readData(vector<double> &input, vector<double> &output);
double calculateGradient(vector<double> input, vector<double> output,
		vector <double> theta, int index);
unsigned int detectErrors(vector<double> &input, vector<double> &output, 
		vector <double> &theta);

int main()
{
	vector<double> input, output, theta, gradientOld(2), gradientCurr;
	double alpha = 0.000001;
	int i = 0;
	//set theta_0, theta_1 to 1
	theta.push_back(0);
	theta.push_back(0);
	//set gradientOld of theta_0 and theta_1 to a large number
	gradientCurr.push_back(10000);
	gradientCurr.push_back(10000);

	readData(input, output);

	cout << "Starting thetas = 0 and my constant alpha = 0.000001."<< endl;

	do
	{
		//cout << "Iteration " << i << ": " << endl;
		gradientOld[0] = gradientCurr[0];
		gradientOld[1] = gradientCurr[1];
		gradientCurr[0] = calculateGradient(input, output, theta, 0);
		gradientCurr[1] = calculateGradient(input, output, theta, 1);

		//cout << "\tNew Gradient for Theta_0: " << gradientCurr[0] << endl;
		//cout << "\tNew Gradient for Theta_1: " << gradientCurr[1] << endl;

		theta[0] = theta[0] + alpha*gradientCurr[0];
		theta[1] = theta[1] + alpha*gradientCurr[1];

		//cout << "\tNew Theta_0: " << theta[0] << endl;
		//cout << "\tNew Theta_1: " << theta[1] << endl;
		i++;
	}while((fabs(gradientCurr[0]) >= 0.0099) || 
			(fabs(gradientCurr[1]) >= 0.0099));

	//cout << "Absolute values of gradients are less than 0.01." << endl;
	
	cout << "New Theta_0: " << theta[0] << endl;
	cout << "New Theta_1: " << theta[1] << endl;

	unsigned int numErrors = detectErrors(input, output, theta);

	cout << "Number of Errors: " << numErrors << endl;

	return 0;
}

double calculateGradient(vector<double> input, vector<double> output, 
		vector<double> theta, int index)
{
	double gradient = 0;

	// sum
	for ( int i = 0; i < input.size(); i++)
	{
		gradient += (output[i] - (theta[0] + theta[1]*input[i]))
			* (index == 0 ? 1 : input[i]);
	}

	return gradient;
}

void readData(vector<double> &input, vector<double> &output)
{
	ifstream inFile("data2.txt");

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

unsigned int detectErrors(vector<double> &input, vector<double> &output, 
		vector <double> &theta)
{
	unsigned int numErrs = 0;
	double sumOfDiff = 0;
	vector<double> differences;

	for(int i = 0; i < input.size(); i++)
	{
		double expected = theta[0] + theta[1]*input[i];
		differences.push_back(expected - output[i]);
		sumOfDiff += fabs(differences[i]);
	}

	double meanOfDiff = sumOfDiff/(double)input.size();
	double stdDevOfDiff = 0;
	double sumOfMeanDiff = 0;

	for(int i = 0; i < input.size(); i++)
	{
		sumOfMeanDiff += pow(differences[i] - meanOfDiff, 2);
	}

	stdDevOfDiff = sqrt(sumOfMeanDiff/(input.size()-1));

	cout << "\tStd. Dev. of Error: " << stdDevOfDiff << endl;

	for(int i = 0; i < input.size(); i++)
	{
		if(fabs(differences[i]) > fabs(stdDevOfDiff))
		{
			numErrs++;
		}
	}

	return numErrs;
}
