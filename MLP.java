package 인공신경망;

import java.util.*;
import java.io.*;
import java.math.*;
import java.time.*;

public class MLP {
	
	static final int numInput = 17;
	static final int numPattern = 268;
	static final int numHidden = 9;
	
	static final int numTest = 30000;
	static final double LR_IH = 0.7;
	static final double LR_HO = 0.065;
	static final double LR_HH = 0.0065;
	
	static final String[] test_input = {"이닝: ", "상대 타자 수: ", "투구수: ", "타수: ", "피안타: ", "피홈런: ", 
			                            "4사구: ", "삼진: ", "실점 : ", "자책: ", "평균 자책점: ", "득점 : ", "팀 안타: ", "팀 에러: ", "팀 볼: ", "홈 / 어웨이: " };
	
	static int patNum = 0;
	static double errThisPat = 0.0;
	static double outPred = 0.0;
	
    Random rand = new Random();
	
	static double[] hiddenVal = new double[numHidden];
	static double[] hidden_2Val = new double[numHidden];
	
	static double[][] weightsIH = new double[numInput][numHidden];
	static double[][] weightsHH = new double[numInput][numHidden];
	static double[] weightsHO = new double[numHidden];
	
	static double[][] trainInputs = new double[numPattern][numInput];
	static int[] trainOutput = new int[numPattern];
	
	
	double tanh(double x){
		return (2 / (1 + Math.exp(-2 * x)) -1 );
	}
	
	double getRand(){
		return ((rand.nextFloat()* 2 -1));
	}
	
	void initWeight() {
		
		for(int j=0; j<numHidden; j++){
			weightsHO[j] = (getRand() - 0.5) / 2;
			for(int i=0; i<numInput; i++){
				weightsIH[i][j] = (getRand() - 0.5) / 5;
			}
			
		}
		
		for(int i=0; i<numHidden; i++){
			for(int j=0; j<numHidden; j++){
				weightsHH[i][j] = (getRand() - 0.5) / 5;
			}
		}
		
	}
	
	
	void initData() throws FileNotFoundException {
		
		//System.out.println("Initializing Data");
		
		int i=0, j; 
		String fileName1 = "input.txt";
		String fileName2 = "output.txt";
		Scanner inputStream = new Scanner(new FileInputStream(fileName1));
		while(inputStream.hasNextDouble()){
			for(j=0; j<numInput -1; j++){
				trainInputs[i][j] = inputStream.nextDouble();
			}
			trainInputs[i][j] = 0.001;
			i++;
		}
		
		i=0;
		inputStream = new Scanner(new FileInputStream(fileName2));
		while(inputStream.hasNextInt()){
				trainOutput[i] = inputStream.nextInt();
				i++;
		}
		
	}
		
	void calcNet(){
		
		int i=0;
		for(i=0; i<numHidden; i++){
			hiddenVal[i] = 0.0;
			
			for(int j=0; j<numInput; j++){
				hiddenVal[i] = hiddenVal[i] + (trainInputs[patNum][j] * weightsIH[j][i]);
			}
			hiddenVal[i] = tanh(hiddenVal[i]);
		}
		
		for(i=0; i<numHidden; i++){
			hidden_2Val[i] = 0.0;
			for(int j=0; j<numHidden; j++){
				hidden_2Val[i] = hidden_2Val[i] + (hiddenVal[j] * weightsHH[j][i]);
			}
			hidden_2Val[i] = tanh(hidden_2Val[i]);
		}
		
		outPred = 0.0;
		
		for(i=0; i<numHidden; i++){
			outPred = outPred + hidden_2Val[i] * weightsHO[i];
		}
		
		errThisPat = outPred - trainOutput[patNum];
	}
	

	void calcNet(double test[]){
		
		int i=0;
		for(i=0; i<numHidden; i++){
			hiddenVal[i] = 0.0;
			
			for(int j=0; j<numInput; j++){
				hiddenVal[i] = hiddenVal[i] + (test[j] * weightsIH[j][i]);
			}
			hiddenVal[i] = tanh(hiddenVal[i]);
		}
		
		for(i=0; i<numHidden; i++){
			hidden_2Val[i] = 0.0;
			for(int j=0; j<numHidden; j++){
				hidden_2Val[i] = hidden_2Val[i] + (hiddenVal[j] * weightsHH[j][i]);
			}
			hidden_2Val[i] = tanh(hidden_2Val[i]);
		}
		
		outPred = 0.0;
		
		for(i=0; i<numHidden; i++){
			outPred = outPred + hidden_2Val[i] * weightsHO[i];
		}
	}
	
	void WeightChangesHO(){
		
		for(int i=0; i<numHidden; i++){
			double weightChange = LR_HO * errThisPat * hidden_2Val[i];
			weightsHO[i] = weightsHO[i] - weightChange;
			
			if(weightsHO[i] < -5)
				weightsHO[i] = -5;
			else if(weightsHO[i] > 5)
				weightsHO[i] = 5;
		}
	}
	
	void WeightChangesHH(){
		
		for(int i=0; i<numHidden; i++){
			for(int k=0; k<numHidden; k++){
				double x = 1 -(hidden_2Val[i] * hidden_2Val[i]);
				x = x* weightsHO[i] * errThisPat * LR_HH;
				x = x * hiddenVal[k];
				double weightChange = x;
				weightsHH[k][i] = weightsHH[k][i] - weightChange;
				
				//if(weightsHH[k][i] < -5)
				//	weightsHH[k][i] = -5;
		    	//if(weightsHH[k][i] > 5)
				//	weightsHH[k][i] = 5;
				
			}
		}
	}
	
	void WeightChangesIH(){
		
		for(int i=0; i<numHidden; i++){
			for(int k=0; k<numInput; k++){
				double weight = 1;
				double x = 1 - (hiddenVal[i] * hiddenVal[i]);
				
				for(int j=0; j<numHidden; j++){
					weight = weight * weightsHH[i][j];
				}
				x = x * weight * errThisPat * LR_IH;
				x = x * trainInputs[patNum][k];
				double weightChange = x;
				weightsIH[k][i] = weightsIH[k][i] - weightChange;
				
			//	if(weightsIH[k][i] < -2)
			//		weightsIH[k][i] = -2;
			//	if(weightsIH[k][i] > 2)
			//		weightsIH[k][i] =2;
				
			}
		}
	}
	
	void displayResults(){
		
		for(int i=0; i<numPattern; i++){
			patNum = i;
			calcNet();
			System.out.println("pat = " + (patNum+1) + " actual = " + trainOutput[patNum] + " neural model = " + outPred);
		}	
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		
		MLP test = new MLP();
		test.initWeight();
		test.initData();
		
		int i, j;
		double[] testData = new double[numInput];
		Scanner scan = new Scanner(System.in);
		
		System.out.println("Calucating..........");
		for(i=0; i<=numTest; i++){
			for(j=0; j<numPattern; j++){
				
				patNum = (int) (Math.random() * numPattern);
				
				test.calcNet();
				
				test.WeightChangesHO();
				test.WeightChangesHH();
				test.WeightChangesIH();
				
			}
		}
		
		System.out.println("Weight between input and hidden");
		for(i=0; i<numInput; i++){
			for(j=0; j<numHidden; j++){
				System.out.println("Weights: " + weightsIH[i][j]);
			}
		}
		System.out.println();
		
		System.out.println("Weight between hidden and hidden");
		for(i=0 ;i<numHidden; i++){
			for(j=0; j<numHidden; j++){
				System.out.println("Weights: " + weightsHH[i][j]);
			}
		}
		System.out.println();
		
		System.out.println("Weights between hidden and output");
		for(i=0; i<numHidden; i++){
			System.out.println("Weights: " + weightsHO[i]);
		}
		
		
		//n.displayResults();
		while(true){
		System.out.println("Enter the test sample data: ");
		System.out.println("Ex, 이닝: 4            상대 타자 수: 16            투구수: 44    	 타수: 10\n"
				         +     "피안타: 4        피홈런: 0          4사구: 5          삼진: 2\n"
				          +    "실점 : 5         자책: 1           평균 자책점: 7.44    팀 득점 : 12\n"
				         +     "팀 안타: 9       팀 에러: 2          팀 볼: 5           홈/어웨이: 홈 = 1, 어웨이 = -1\n");
		for(i=0; i<numInput-1; i++){
			System.out.print(test_input[i]);
			testData[i] = scan.nextDouble();
			testData[i] /= 1000;
		}
		testData[i] = 0.001;
		test.calcNet(testData);
		
		if(outPred > 0){
			System.out.println("This game will be win!\n");
		}
		else
			System.out.println("This game will be lose!\n");
		}
	}
}
