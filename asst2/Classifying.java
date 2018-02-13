import java.util.*;
import java.lang.Math;

// LOL this assignment would be so much easier in C++ or Go or like any
//	other language........

public class Classifying{
	
	public static double[] biasInput= new double[100];
	public static double[] xInput= new double[100];
	public static double[] yInput= new double[100];
	public static double[] zInput= new double[100];
	public static int m;	
	
	public static void main(String[] args) throws Exception{
		m= xInput.length;
		for(int i=0; i<m; i++){
			biasInput[i] = 1;
			xInput[i] = (i+1)/5.0 + Math.random();
			yInput[i] = (100-i)/0.3 + Math.random()*10; 
			zInput[i] = (i<(Math.random()*100))? 0 : 1;
//			System.out.printf(" %.2f    %.2f     %.2f \n",xInput[i],yInput[i], zInput[i]);
		}

		int errorLinear = logisticRegression();
		int errorQuadratic = 0;

		System.out.println("Linear Regression Error: " + errorLinear);

		if(errorLinear != 0)
		{
			errorQuadratic = quadraticRegression();

			System.out.println("Quadratic Regression Error: "
					+ errorQuadratic);

			if(errorLinear != errorQuadratic)
			{
				System.out.println("The best model for this data set is: "
					+ (errorLinear < errorQuadratic ? "linear." 
						: "quadratic."));
			}
			else
			{
				System.out.println("Both models have the same error.");
			}
		}

		//Perceptron Algorithm for Classification
		System.out.println("\n\nPerceptron Algorithm for Classification:\n-------------------------------------------\n\n");
 		double alpha = 0.01;
		
		double prevThetaZero= 0.0;
		double prevThetaOne = 0.0;		
		double prevThetaTwo = 0.0;		
		double newThetaZero = 0;
		double newThetaOne = 0;
		double newThetaTwo = 0;
		double partialDerZero = 0;
		double partialDerOne = 0;
		double partialDerTwo = 0;
		int counter=0;

		int loop = 0;
		int fixing = 0;
		do {
			if(counter == 99){
				counter = 0;
				fixing = 0;
			}
			loop++;
			if((zInput[counter] == 0) 
				&& (newThetaZero +  newThetaOne * xInput[counter] 
					+ newThetaTwo * yInput[counter]) < 0) {
				newThetaZero += biasInput[counter];
				newThetaOne += xInput[counter];
				newThetaTwo += yInput[counter];
				fixing++;
			}
			if((zInput[counter] == 1) && (newThetaZero +  newThetaOne * xInput[counter] + newThetaTwo * yInput[counter]) > 0) {
				newThetaZero -= biasInput[counter];
				newThetaOne -= xInput[counter];
				newThetaTwo -= yInput[counter];
				fixing++;
			}
			counter++;
			if(loop > 1000) break;
		}
		while (counter != 99 || fixing !=0);
		System.out.println("number of loop: " + loop + "\nTheta sub 0 is: " + newThetaZero +"\nTheta sub 1 is: " + newThetaOne +"\nTheta sub 2 is: " + newThetaTwo);	
	}
	
	public static int logisticRegression()
	{
		System.out.println("Batch implementation for Logistic "
				+ "Classification (Linear):\n--------------------------"
				+"-----------------\n\n");
		double alpha = 0.01;
		
		double prevThetaZero= 0.0;
		double prevThetaOne = 0.0;		
		double prevThetaTwo = 0.0;		
		double newThetaZero = 0;
		double newThetaOne = 0;
		double newThetaTwo = 0;
		double partialDerZero = 0;
		double partialDerOne = 0;
		double partialDerTwo = 0;
		int counter=0;
		int prevError;
		int currError = 100;

		//Batch implementation for Logistic Classification
		do{
			prevError = currError;
			currError = 0;
			prevThetaOne = newThetaOne;
			prevThetaZero = newThetaZero;
			prevThetaTwo = newThetaTwo;
			partialDerZero = partDerivative(prevThetaZero, prevThetaOne, 
					prevThetaTwo, 0);
			partialDerOne = partDerivative(prevThetaZero, prevThetaOne, 
					prevThetaTwo, 1);
			partialDerTwo = partDerivative(prevThetaZero, prevThetaOne, 
					prevThetaTwo, 2);
			newThetaZero = prevThetaZero + alpha*partialDerZero;
			newThetaOne = prevThetaOne + alpha*partialDerOne;
			newThetaTwo = prevThetaTwo + alpha*partialDerTwo;
			
			for (int i = 0; i < m; i++)
			{
				if (zInput[i] != ((sigmoid(newThetaZero + newThetaOne 
					* xInput[i] + newThetaTwo*yInput[i])) < 0.5 ? 0 : 1))
				{
					currError++;
				}
			}

			counter++;
			if (counter > 300000 || currError >= prevError)
			{
				System.out.println("Counter: " + counter);
				System.out.println("Previous Error: " + prevError);
				return currError;
			}

		}while(Math.abs(partialDerZero) >.001 
				|| Math.abs(partialDerOne)>.001 
				|| Math.abs(partialDerTwo) > 0.001);	

		System.out.println("It took " + counter + "\nTheta sub 0 is: " 
				+ newThetaZero +"\nTheta sub 1 is: " + newThetaOne 
				+"\nTheta sub 2 is: " + newThetaTwo);
		System.out.println("\npartialDerZero: " + partialDerZero 
				+ "\npartialDerOne: " + partialDerOne 
				+ "\npartialDerTwo: " +partialDerTwo);
		for (int i = 0; i < m; i++)
		{
			if (zInput[i] != ((sigmoid(newThetaZero + newThetaOne 
				* xInput[i] + newThetaTwo*yInput[i])) < 0.5 ? 0 : 1))
			{
				currError++;
			}
		}

		return currError;
	}

	public static int quadraticRegression()
	{
		System.out.println("Batch implementation for Logistic "
				+ "Classification (Quadratic):\n-------------------------"
				+ "------------------\n\n");
		double alpha = 0.01;
		
		double prevThetaZero= 0.0;
		double prevThetaOne = 0.0;		
		double prevThetaTwo = 0.0;		
		double prevThetaThree = 0.0;
		double newThetaZero = 0;
		double newThetaOne = 0;
		double newThetaTwo = 0;
		double newThetaThree = 0;
		double partialDerZero = 0;
		double partialDerOne = 0;
		double partialDerTwo = 0;
		double partialDerThree = 0;
		int counter=0;
		int prevError;
		int currError = 100;

		//Batch implementation for Logistic Classification
		do{
			prevError = currError;
			currError = 0;
			prevThetaOne = newThetaOne;
			prevThetaZero = newThetaZero;
			prevThetaTwo = newThetaTwo;
			prevThetaThree = newThetaThree;
			partialDerZero = partDerivativeQuadratic(prevThetaZero, 
					prevThetaOne, prevThetaTwo, prevThetaThree, 0);
			partialDerOne = partDerivativeQuadratic(prevThetaZero, 
					prevThetaOne, prevThetaTwo, prevThetaThree, 1);
			partialDerTwo = partDerivativeQuadratic(prevThetaZero, 
					prevThetaOne, prevThetaTwo, prevThetaThree, 2);
			partialDerThree = partDerivativeQuadratic(prevThetaZero,
					prevThetaOne, prevThetaTwo, prevThetaThree, 3);
			newThetaZero = prevThetaZero + alpha*partialDerZero;
			newThetaOne = prevThetaOne + alpha*partialDerOne;
			newThetaTwo = prevThetaTwo + alpha*partialDerTwo;
			newThetaThree = prevThetaThree + alpha*partialDerThree;
			
			for (int i = 0; i < m; i++)
			{
				if (zInput[i] != ((sigmoid(newThetaZero + newThetaOne 
					* xInput[i] + newThetaTwo*yInput[i] 
					+ newThetaThree*Math.pow(xInput[i],2))) < 0.5 ? 0 : 1))
				{
					currError++;
				}
			}

			counter++;
			if (counter > 300000 || currError >= 10+prevError)
			{
				System.out.println("Counter: " + counter);
				System.out.println("Previous Error: " + prevError);
				return prevError;
			}

		}while(Math.abs(partialDerZero) >.001 
				|| Math.abs(partialDerOne)>.001 
				|| Math.abs(partialDerTwo) > 0.001
				|| Math.abs(partialDerThree) > 0.001);	

		System.out.println("It took " + counter + "\nTheta sub 0 is: " 
				+ newThetaZero +"\nTheta sub 1 is: " + newThetaOne 
				+"\nTheta sub 2 is: " + newThetaTwo
				+ "\nTheta sub 3 is: " + newThetaThree);
		System.out.println("\npartialDerZero: " + partialDerZero 
				+ "\npartialDerOne: " + partialDerOne 
				+ "\npartialDerTwo: " +partialDerTwo
				+ "\npartialDerThree: " + partialDerThree);
		for (int i = 0; i < m; i++)
		{
			if (zInput[i] != ((sigmoid(newThetaZero + newThetaOne 
				* xInput[i] + newThetaTwo*yInput[i]
				+ newThetaThree*Math.pow(xInput[i],2))) < 0.5 ? 0 : 1))
			{
				currError++;
			}
		}

		return currError;
	}
	
	public static double partDerivative(double weightZero, double weightOne,
		   	double weightTwo, int index)
	{
		double partialDerValue=0.0;
		double coeff = 0.0;
		for(int i=0; i<m; i++){
			if (index == 0)	coeff = biasInput[i];
			if (index == 1) coeff = xInput[i];
			if (index == 2) coeff = yInput[i];
			partialDerValue += coeff * (zInput[i] - sigmoid(weightZero + weightOne * xInput[i] + weightTwo*yInput[i]));
		}
		return partialDerValue;
	}
		
	public static double partDerivativeQuadratic(double weightZero, 
			double weightOne, double weightTwo, double weightThree,
		   	int index)
	{
		double partialDerValue=0.0;
		double coeff = 0.0;
		for(int i=0; i<m; i++){
			if (index == 0)	coeff = biasInput[i];
			if (index == 1) coeff = xInput[i];
			if (index == 2) coeff = yInput[i];
			if (index == 3) coeff = Math.pow(xInput[i], 2);
			partialDerValue += coeff * (zInput[i] - sigmoid(weightZero 
				+ weightOne * xInput[i] + weightTwo*yInput[i] 
				+ weightThree * Math.pow(xInput[i],2)));
		}

		return partialDerValue;
	}

	public static double sigmoid (double x) {
		return (1.0/(1.0 + Math.exp(-x)));
	}
}
