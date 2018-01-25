#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void readData(vector<double> &input, vector<double> &output);
double calculateGradient(vector<double> input, vector<double> output,
		vector <double> theta, int index);

int main()
{
	vector<double> input, output, theta, gradientOld(2), gradientCurr;
	double alpha = 0.0001;
	int i = 0;
	//set theta_0, theta_1 to 1
	theta.push_back(0);
	theta.push_back(0);
	//set gradientOld of theta_0 and theta_1 to a large number
	gradientCurr.push_back(10000);
	gradientCurr.push_back(10000);

	readData(input, output);

	do
	{
		cout << "Iteration " << i << ": " << endl;
		gradientOld[0] = gradientCurr[0];
		gradientOld[1] = gradientCurr[1];
		gradientCurr[0] = calculateGradient(input, output, theta, 0);
		gradientCurr[1] = calculateGradient(input, output, theta, 1);

		if(2*fabs(gradientCurr[0]) < fabs(gradientOld[0])
				&& 2*fabs(gradientCurr[1]) < fabs(gradientOld[1]))
		{
			alpha = 2*alpha;
		}
		else if( fabs(gradientCurr[0]) > fabs(gradientOld[0])
				|| fabs(gradientCurr[1]) > fabs(gradientOld[1]))
		{
			alpha = alpha*0.5;
		}

		cout << "\tNew Gradient for Theta_0: " << gradientCurr[0] << endl;
		cout << "\tNew Gradient for Theta_1: " << gradientCurr[1] << endl;

		theta[0] = theta[0] + alpha*gradientCurr[0];
		theta[1] = theta[1] + alpha*gradientCurr[1];

		cout << "\tNew Theta_0: " << theta[0] << endl;
		cout << "\tNew Theta_1: " << theta[1] << endl;
		i++;
	}while((fabs(gradientOld[0]-gradientCurr[0]) >= 0.0099) || 
			(fabs(gradientOld[1]-gradientCurr[1]) >= 0.0099));

	cout << "Gradient at step k and step k-1 are similar to " 
		<< "two decimal places. " << endl;

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
