//Linear Logistic Regression and perceptron Algorithm

#include <vector>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

// Function Prototypes
void readDataFromFile(vector<double> &, vector<double> &, vector<int> &);
void splitData(vector<double> &, vector<double> &, vector<double> &,
		vector<double> &, vector<double> &, vector<double> &, 
		vector<int> &, vector<int> &, vector<int> &); 
void regression(vector<double> &, vector<double> &, vector<double> &,
		vector<double> &, vector<double> &, vector<int> &);
double sigmoid(double);
double calculateGradient(int, vector<double> &, vector<double> &, 
		vector<double> &, vector<int> &);

int main()
{
	vector<double> input1, input2, trainingInput1, trainingInput2, 
		testingInput1, testingInput2, theta, prevTheta, gradient;
	vector<int> classification, trainingClass, testingClass;

	readDataFromFile(input1, input2, classification); 
	splitData(input1, trainingInput1, testingInput1, input2, trainingInput2,
			testingInput2, classification, trainingClass, testingClass);

	cout << "Logistic Regression: " << endl;

	int counter = 0; 

	for(int i = 0; i < 3; i++)
	{
		prevTheta.push_back(0);
		theta.push_back(0);
		gradient.push_back(100);
	}

	while(fabs(gradient[0]) > 0.001 || fabs(gradient[1]) > 0.001
			|| fabs(gradient[2]) > 0.001)
	{
		counter++;
		regression(theta, prevTheta, gradient, trainingInput1, 
				trainingInput2, trainingClass);

		if(counter > 300000)
		{
			break;
		}
	}

	cout << "\tIterations: " << counter << endl;
	cout << "\tLinear Function: " << theta[0] << " + " << theta[1]
		<< "*x_1 + " << theta[2] << "*x_2" << endl << endl;
	cout << "\tTesting: " << endl;

	int err = 0;

	for(int i = 0; i < testingInput1.size(); i++)
	{
		if(testingClass[i] != (sigmoid(theta[0] + theta[1]*testingInput1[i]
							+ theta[2]*testingInput2[i]) < 0.5 ? 0 : 1))
		{
			err++;
		}
	}

	cout << "\tError in testing data: " 
		<< (double)err/(double)testingClass.size() << "%" << endl << endl;


	// Perceptron
	cout << "Perceptron: " << endl;

	theta[0] = 1;
	theta[1] = trainingInput1[0];
	theta[2] = trainingInput2[0];
	counter = 0;
	int error = 100;

	while(error != 0)
	{
		error = 0;
		counter++;
		for(int i = 0; i < trainingInput1.size(); i++)
		{
			if(trainingClass[i] == 0 && (theta[0] 
						+ theta[1]*trainingInput1[i] 
						+ theta[2]*trainingInput2[i]) < 0)
			{
				theta[0] += 1;
				theta[1] += trainingInput1[i];
				theta[2] += trainingInput2[i];
				error++;
			}
			else if(trainingClass[i] == 1 && (theta[0] 
						+ theta[1]*trainingInput1[i] 
						+ theta[2]*trainingInput2[i]) > 0)
			{
				theta[0] -= 1;
				theta[1] -= trainingInput1[i];
				theta[2] -= trainingInput2[i];
				error++;
			}
		}

		if(counter > 1000)
		{
			break;
		}
	}

	cout << "Number of Iterations: " << counter << endl;
	cout << "\tPerceptron Function: " << theta[0] << " + "
		<< theta[1] << "*x_1 + " << theta[2] << "*x_2" << endl;

	error = 0;
	cout << "Testing Size: " << testingInput1.size() << endl;
	for(int i = 0; i < testingInput1.size(); i++)
	{
		if((testingClass[i] == 0 && (theta[0] 
					+ theta[1]*testingInput1[i] 
					+ theta[2]*testingInput2[i]) < 0)
				|| (testingClass[i] == 1 && (theta[0] 
					+ theta[1]*testingInput1[i] 
					+ theta[2]*testingInput2[i]) > 0))
		{
			error++;
		}
	}

	cout << "\tPerceptron Error: " << error << endl;
}


void regression(vector<double> &theta, vector<double> &prevTheta,
		vector<double> &gradient, vector<double> &trainingInput1, 
		vector<double> &trainingInput2, vector<int> &trainingClass)
{
	double alpha = 0.01;

	for(int i = 0; i < prevTheta.size(); i++)
	{
		prevTheta[i] = theta[i];
	}

	for(int i = 0; i < gradient.size(); i++)
	{
		gradient[i] = calculateGradient(i, prevTheta, trainingInput1, 
				trainingInput2, trainingClass);
		theta[i] = prevTheta[i] + alpha*gradient[i];
	}
}

double calculateGradient(int index, vector<double> &prevTheta,
		vector<double> &trainingInput1, vector<double> &trainingInput2,
		vector<int> &trainingClass)
{
	double gradient = 0;
	double coeff = 1.0;

	for(int i = 0; i < trainingInput1.size(); i++)
	{
		if(index == 1) coeff = trainingInput1[i];
		if(index == 2) coeff = trainingInput2[i];

		gradient += coeff * (trainingClass[i] - sigmoid(prevTheta[0]
					+ prevTheta[1] * trainingInput1[i]
					+ prevTheta[2] * trainingInput2[i]));
	}

	return gradient;
}

double sigmoid(double funcVal)
{
	return (1.0/(1.0 + exp(-funcVal)));
}

void readDataFromFile(vector<double> &input1, vector<double> &input2, 
		vector<int> &classification)
{
	double x, y;
	int z;
	fstream in("quadNoSep.txt");

	if(!in)
	{
		cerr << "Unable to open file." << endl;
	}

	while( in >> x)
	{
		input1.push_back(x);

		in >> y;
		input2.push_back(y);

		in >> z;
		classification.push_back(z);
	}

	in.close();
}

void splitData(vector<double> &input1, vector<double> &trainingInput1, 
		vector<double> &testingInput1, vector<double> &input2, 
		vector<double> &trainingInput2, vector<double> &testingInput2, 
		vector<int> &classification, vector<int> &trainingClass, 
		vector<int> &testingClass)
{
	default_random_engine randGenerator;
	int trainingSize = (int)(input1.size()*0.8); // only want 80% of data

	for(int i = 0; i  < trainingSize; i++)
	{
		uniform_int_distribution<int> distribution(0, input1.size()-1);
		int randIndex = distribution(randGenerator);

		// choosing training data randomly
		trainingInput1.push_back(input1[randIndex]);
		trainingInput2.push_back(input2[randIndex]);
		trainingClass.push_back(classification[randIndex]);

		//removing training data from array
		input1.erase(input1.begin()+randIndex);
		input2.erase(input2.begin()+randIndex);
		classification.erase(classification.begin()+randIndex);
	}

	// Setting testing data to whatever is left
	testingInput1 = input1;
	testingInput2 = input2;
	testingClass = classification;
}
