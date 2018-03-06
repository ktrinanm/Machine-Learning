// Logistic regression and perceptron Algorithms for Machine Learning
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

// Function prototypes
void readDataFile(vector<double> &, vector<double> &, vector<int> &);
void splitData(vector<double> &, vector<double> &, vector<double> &,
		vector<double> &, vector<double> &, vector<double> &,
		vector<int> &, vector<int> &, vector<int> &);
void regression(vector<double> &theta, vector<double> &prevTheta,
		vector<double> &gradient, vector<double> &trainingInput1,
		vector<double> &trainingInput2, 
		vector<int> &trainingClass);
double sigmoid(double funcVal);
double calculateGradient(vector<double> &theta, int index, 
		vector<double> &trainingInput1, vector<double> &trainingInput2,
		vector<int> &trainingClass);

int main()
{
	vector<double> input1, input2, trainingInput1, trainingInput2,
		testingInput1, testingInput2, theta, prevTheta, gradient;
	vector<int> classification, trainingClass, 
		testingClass;

	readDataFile(input1, input2, classification); //reading data
	splitData(input1, trainingInput1, testingInput1, input2, trainingInput2,
			testingInput2, classification, trainingClass,
			testingClass); // Splitting data into training and 
									// testing

	cout << "Quadratic Logistic Regression Algorithm: " << endl;

	int counter = 0;

	// adding 6 items for Linear data
	for(int i = 0; i < 6; i++)
	{
		prevTheta.push_back(0);
		theta.push_back(0);
		gradient.push_back(100);
	}

	while(fabs(gradient[0]) > 0.001 || fabs(gradient[1]) > 0.001 
				|| fabs(gradient[2]) > 0.001 || fabs(gradient[3]) > 0.001
				|| fabs(gradient[4]) > 0.001 || fabs(gradient[5]) > 0.001)
	{
		counter++;

		regression(theta, prevTheta, gradient, 
				trainingInput1, trainingInput2, trainingClass);

		if(counter > 300000 )
		{
			break;
		}
	}

	cout << "\tIterations: " << counter << endl;
	cout << "\tQuadratic function: " << theta[0] << " + " << theta[1] 
		<< "*x_1 + " << theta[2] << "*x_2 + " << theta[3] 
		<< "*x_1*x_2 + " << theta[4] << "*x_1^2 + " << theta[5] 
		<< "*x_2^2" << endl << endl;

	int error = 0;

	for(int i = 0; i < testingInput1.size(); i++)
	{
		if(testingClass[i] != (sigmoid(theta[0] 
						+ theta[1]*testingInput1[i]
						+ theta[2]*testingInput2[i] 
						+ theta[3]*testingInput1[i]*testingInput2[i]
						+ theta[4]*pow(testingInput1[i],2)
						+ theta[5]*pow(testingInput2[i],2))
						< 0.5 ? 0 : 1))
		{
			error++;
		}
	}

	cout << "\tQuadratic Error: " << setprecision(4)
		<< (double)error*100.0/(double)testingClass.size() << "%" 
		<< endl << endl;


	cout << "Perceptron Algorithm: " << endl;

	counter = 0; 
	error = 100;
	theta[0] = 1;
	theta[1] = trainingInput1[0];
	theta[2] = trainingInput2[0];
	theta[3] = trainingInput1[0]*trainingInput2[0];
	theta[4] = pow(trainingInput1[0], 2);
	theta[5] = pow(trainingInput2[0], 2);

	while(error != 0)
	{
		error = 0; 
		counter++;

		for(int i = 0; i < trainingInput1.size(); i++)
		{
			if(trainingClass[i] == 0 && (theta[0] 
						+ theta[1] * trainingInput1[i] 
						+ theta[2] * trainingInput2[i] 
						+ theta[3] * trainingInput1[i]*trainingInput2[i]
						+ theta[4] * pow(trainingInput1[i], 2) 
						+ theta[5] * pow(trainingInput2[i], 2)) < 0)
			{
				theta[0] += 1;
				theta[1] += trainingInput1[i];
				theta[2] += trainingInput2[i];
				theta[3] += trainingInput1[i]*trainingInput2[i];
				theta[4] += pow(trainingInput1[i], 2);
				theta[5] += pow(trainingInput2[i], 2);
				error++;
			}
			else if(trainingClass[i] == 1 && (theta[0]
						+ theta[1] * trainingInput1[i] 
						+ theta[2] * trainingInput2[i] 
						+ theta[3] * trainingInput1[i]*trainingInput2[i]
						+ theta[4] * pow(trainingInput1[i], 2) 
						+ theta[5] * pow(trainingInput2[i], 2)) > 0)
			{
				theta[0] -= 1;
				theta[1] -= trainingInput1[i];
				theta[2] -= trainingInput2[i];
				theta[3] -= trainingInput1[i]*trainingInput2[i];
				theta[4] -= pow(trainingInput1[i], 2);
				theta[5] -= pow(trainingInput2[i], 2);
				error++;
			}
		}

		if(counter > 10000)
		{
			break;
		}
	}

	cout << "Iterations: " << counter << endl;
	cout << "\tPerceptron Equation: " << theta[0] << " + " << theta[1]
		<< "*x_1 + " << theta[2] << "*x_2 + " << theta[3] << "*x_1*x_2 + "
		<< theta[4] << "*x_1*x_1 + " << theta[5] << "x_2*x_2" 
		<< endl << endl;

	error = 0;

	for(int i = 0; i< testingClass.size(); i++)
	{
		if((testingClass[i] == 0 && (theta[0] + theta[1] * testingInput1[i]
					+ theta[2] * testingInput2[i]
					+ theta[3] * testingInput1[i]*testingInput2[i]
					+ theta[4] * pow(testingInput1[i], 2) 
					+ theta[5] * pow(testingInput2[i], 2)) < 0)
				|| (testingClass[i] == 1 && (theta[0] 
						+ theta[1] * testingInput1[i]
						+ theta[2] * testingInput2[i]
						+ theta[3] * testingInput1[i]*testingInput2[i]
						+ theta[4] * pow(testingInput1[i], 2) 
						+ theta[5] * pow(testingInput2[i], 2)) > 0))
		{
			error++;
		}
	}

	cout << "\tPerceptron error: " << setprecision(4)
		<< (double)error*100/(double)testingClass.size() << "%." << endl;
}

void regression(vector<double> &theta, vector<double> &prevTheta,
		vector<double> &gradient, vector<double> &trainingInput1,
		vector<double> &trainingInput2, 
		vector<int> &trainingClass)
{
	double alpha = 0.01;

	for(int i = 0; i < prevTheta.size(); i++)
	{
		prevTheta[i] = theta[i];
	}

	for(int i = 0; i < gradient.size(); i++)
	{
		gradient[i] = calculateGradient(prevTheta, i, trainingInput1,
				trainingInput2, trainingClass);
		theta[i] = prevTheta[i] + alpha*gradient[i];
	}
}

double calculateGradient(vector<double> &prevTheta, int index, 
		vector<double> &trainingInput1, vector<double> &trainingInput2,
		vector<int> &trainingClass)
{
	double gradient = 0.0;
	double coeff = 1.0;

	for(int i = 0; i < trainingInput1.size(); i++)
	{
		if(index == 1) coeff = trainingInput1[i];
		if(index == 2) coeff = trainingInput2[i];
		if(index == 3) coeff = trainingInput1[i]*trainingInput2[i];
		if(index == 4) coeff = pow(trainingInput1[i],2);
		if(index == 5) coeff = pow(trainingInput2[i],2);

		gradient += coeff*(trainingClass[i] - 
				sigmoid(prevTheta[0] + prevTheta[1]*trainingInput1[i]
					+ prevTheta[2]*trainingInput2[i] 
					+ prevTheta[3]*trainingInput1[i]*trainingInput2[i]
					+ prevTheta[4]*pow(trainingInput1[i],2)
					+ prevTheta[5]*pow(trainingInput2[i],2)));
	}

	return gradient;
}

double sigmoid(double funcVal)
{
	return (1.0/(1.0 + exp(-funcVal)));
}

void readDataFile(vector<double> &x1, vector<double> &x2, vector<int> &y)
{
	ifstream in("quadraticData.txt");

	if(!in)
	{
		cerr << "Unable to open file." << endl;
	}

	double input1, input2;
	int classification;

	while(in >> input1)
	{
		x1.push_back(input1);
		
		in >> input2;
		x2.push_back(input2);

		in >> classification;
		y.push_back(classification);
	}
}

void splitData(vector<double> &input1, vector<double> &trainingInput1, 
		vector<double> &testingInput1, vector<double> &input2, 
		vector<double> &trainingInput2, vector<double> &testingInput2,
		vector<int> &classification, vector<int> &trainingClass, 
		vector<int> &testingClass)
{

	default_random_engine randGenerator;

	int trainingSize = (int)(input1.size()*0.8);

	for(int i = 0; i < trainingSize; i++)
	{
		uniform_int_distribution<int> distribution(0, input1.size()-1);
		int randIndex = distribution(randGenerator);
		
		// choosing training data randomly
		trainingInput1.push_back(input1[randIndex]);
		trainingInput2.push_back(input2[randIndex]);
		trainingClass.push_back(classification[randIndex]);

		// removing training data from array
		input1.erase(input1.begin()+randIndex);
		input2.erase(input2.begin()+randIndex);
		classification.erase(classification.begin()+randIndex);
	}

	testingInput1 = input1;
	testingInput2 = input2;
	testingClass = classification;
}
