#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//// Data dependent settings ////
#define numInputs    13   // input data들의 개수
#define numPatterns  38  // training을 시켜 볼 data 집합의 개수


//// User defineable settings ////
#define numHidden 4

const int numEpochs = 500;  // 테스트 진행 할 숫자
							// 0~1사이의 상수값으로 learning rate를 정함. 변수를 다르게 잡은 이유는	값을 다르게 하기위해서임8
const double LR_IH = 0.7;   // Input~Hidden 사이의 learning rate
const double LR_HO = 0.07;  // Hidden ~ output 사이의 learning rate
const double LR_HH = 0.007;  // Hidden ~ Hidden 사이의 learning rate

							//// functions ////
void initWeights();        // 초기 weight값 임의의 값으로 설정s
void initData();           // test할 data를 초기화 ( 이 프로그램에서는 xor 테스트했음)
void calcNet();            // neural model을 통해 data값 test하는 function
void WeightChangesHO();      // hidden ~ output layer 사이의 weight값 조정 함수
void WeightChangesIH();      // input ~ hidden layer 사이의 weight 값 조정 함수 
void WeightChangesHH();  // hidden ~ hidden layer 사이의 weight 값 조정 함수
void calcOverallError();     // 전체 error값 도출 ( 딱히 필요 없어 보임)
void displayResults();       // data에 대한 실제 결과 와 neural model에 의해 최종 예측된 값 display
double getRand();            // 임의의 double value 생성기


							 //// variables ////
int patNum = 0;             // test를 진행할 data 값 순서
double errThisPat = 0.0;    // 예측값에 대한 에러값 (weight 조정할 때 사용)
double outPred = 0.0;       // 예측값
double RMSerror = 0.0;      // 전체 network에 대한 error값

// the outputs of the hidden neurons
// 각 hidden layer에서 나온 output값
double hiddenVal[numHidden];
double hidden_2Val[numHidden];

// the weights
double weightsIH[numInputs][numHidden];  // input과 hidden 에 대한 weight 값들
double weightsHH[numHidden][numHidden];  // hidden, hidden layer 사이 
double weightsHO[numHidden];             // hidden에서 output layer 사이의 weight 값

										 
double trainInputs[numPatterns][numInputs]; // the data // data를 넣을 array 초기화 
int trainOutput[numPatterns];

//==============================================================
//************** function definitions **************************
//==============================================================

//***********************************
// calculates the network output
void calcNet(void)
{
	//calculate the outputs of the hidden neurons
	//hidden layer들의 각각 output들을 계산
	//the hidden neurons are tanh
	int i = 0;
	for (i = 0; i<numHidden; i++) // test할 데이터에 대한 모든 hidden layer를 각각 돌림
	{
		hiddenVal[i] = 0.0; //처음에 hidden layer output 값을 0.0으로 초기화

		for (int j = 0; j<numInputs; j++) // input 개수만큼 돌면서 
		{
			//wi변수를 weightsIH[], xi를 tranInputs[], yi를 hiddenVal[]로 선언
			//hidden layer의 i번째 output을 patNum번째의 input데이터 * j번째 hidden layer의 weight값
			hiddenVal[i] = hiddenVal[i] + (trainInputs[patNum][j] * weightsIH[j][i]);
		}
		hiddenVal[i] = tanh(hiddenVal[i]);  // activation function --> tanh(x) 사용해서 hidden layer의 value값 정함 (sigmoid계열 tanh 사용)
	}


	for (i = 0; i < numHidden; i++) {
		hidden_2Val[i] = 0.0;

		for (int j = 0; j < numHidden; j++) {
			hidden_2Val[i] = hidden_2Val[i] + (hiddenVal[j] * weightsHH[j][i]);
		}
		hidden_2Val[i] = tanh(hidden_2Val[i]);   // 범위를 -1 ~ 1 사이로 만들기 위해서 tanh 사용
	} 

	//calculate the output of the network
	//the output neuron is linear
	outPred = 0.0; // 최종 예측 output data를 0으로 초기화

				   //hidden node 마다 각각 데이터에 대한 값이 정해져 있고 그 값들을 합쳐서 하나의 output으로 만듦
	for (i = 0; i<numHidden; i++)
	{
		// 최종 예측 output 값을 구함 (각각 hidden layer값 * weight 값)
		// activation fucntion f() = 1을 사용함
		outPred = outPred + hidden_2Val[i] * weightsHO[i];
	}
	//calculate the error 
	// 예측값에서 실제 나와야 하는 결과값을 빼서 오차값을 구함
	errThisPat = outPred - trainOutput[patNum];    // back propagation algorithm part

}


//************************************
//adjust the weights hidden-output
// hidden layer와 output layer사이의 weight를 조정

void WeightChangesHO(void)
{
	for (int k = 0; k < numHidden; k++) // hidden layer 개수 만큼
	{
		double weightChange = LR_HO * errThisPat * hidden_2Val[k]; // weight 변화 값
		weightsHO[k] = weightsHO[k] - weightChange;    // 기존 weight에서 변화값을 빼줌, weithChange를 -로 연산한 이유는 델타의 계산과 errThisPat계산이 뒤바뀌었기 때문.
        
		//regularisation on the output weights 
		// output weight들을 정규화 시킴
		if (weightsHO[k] < -5)              
		{
			weightsHO[k] = -5;
		}
		else if (weightsHO[k] > 5)
		{
			weightsHO[k] = 5;
		}
	}
}

//************************************
// adjust the weights input-hidden
// input layer와 hidden layer 사이의 weight를 조정

void WeightChangesHH(void) {

	for (int i = 0; i<numHidden; i++)  // hidden 개수만큼
	{
		for (int k = 0; k<numHidden; k++)  // hidden과 연결된 각각의 input layer의 weight를 조정
		{
			double x = 1 - (hidden_2Val[i] * hidden_2Val[i]); // hyperbolic tangent함수의 1차미분
			 //Gradient Descent Rule에 기반한 학습알고리즘
			x = x * weightsHO[i] * errThisPat * LR_HH; //  weightsHO[i] * errThisPat =  역전파된 delta값
			x = x * hiddenVal[k];  // test했던 data 순서에 맞는 input값들을 곱해줌
			double weightChange = x;         // weight 변화 값 설정
			weightsHH[k][i] = weightsHH[k][i] - weightChange;   // 기존의 weight값에서 변화값 빼줌
		}
	}
}

//************************************
// adjust the weights input-hidden
// input layer와 hidden layer 사이의 weight를 조정

void WeightChangesIH(void)
{
	for (int i = 0; i<numHidden; i++)  // hidden 개수만큼
	{
		for (int k = 0; k<numInputs; k++)  // hidden과 연결된 각각의 input layer의 weight를 조정
		{
			double weight = 1;
			double x = 1 - (hiddenVal[i] * hiddenVal[i]); // hyperbolic tangent함수의 1차미분
														  //Gradient Descent Rule에 기반한 학습알고리즘
			for (int j = 0; j < numHidden; j++) {
				weight = weight * weightsHH[i][j];
			}
			x = x * weight * errThisPat * LR_IH; //  weightsHO[i] * errThisPat =  역전파된 delta값
			x = x * trainInputs[patNum][k];  // test했던 data 순서에 맞는 input값들을 곱해줌
			double weightChange = x;         // weight 변화 값 설정
			weightsIH[k][i] = weightsIH[k][i] - weightChange;   // 기존의 weight값에서 변화값 빼줌
		}
	}
}

//************************************
// random하게 숫자를 생성
double getRand(void)
{
	return ((double)rand()) / (double)RAND_MAX;
}



//************************************
// weight array를 임의의 값으로 초기화 함
void initWeights(void)
{

	for (int j = 0; j<numHidden; j++)
	{
		weightsHO[j] = (getRand() - 0.5) / 2; // hidden - output layer 이어지는 weight값 초기화
		for (int i = 0; i<numInputs; i++)
		{
			weightsIH[i][j] = (getRand() - 0.5) / 5;
			printf("Weight = %f\n", weightsIH[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < numHidden; i++) {
		for (int j = 0; j < numHidden; j++) {
			weightsHH[i][j] = (getRand() - 0.5) / 5;
		}
	}

}


//************************************
// read in the data
// traininput --> xor data를 테스트 위함
// trainoutput --> 나와야 하는 결과 값임

void initData(void)
{
	int i = 0;
	FILE * fp1 = fopen("tottenham1.txt", "r");
	if (fp1 == NULL) {
		puts("File open error!\n");
		exit(1);
	}
	FILE * fp2 = fopen("tottenham2.txt", "r");
	if (fp2 == NULL) {
		puts("File open error!\n");
		exit(1);
	}

	printf("initialising data\n");
	
	while (!feof(fp1)) {
		fscanf(fp1, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
			&trainInputs[i][0], &trainInputs[i][1], &trainInputs[i][2],
			&trainInputs[i][3], &trainInputs[i][4], &trainInputs[i][5], 
			&trainInputs[i][6], &trainInputs[i][7], &trainInputs[i][8], 
			&trainInputs[i][9], &trainInputs[i][10], &trainInputs[i][11]);
		trainInputs[i][12] = 1;
		i++;
	}

	i = 0;
	// win = 2 lose = 1 draw = -1
	while (!feof(fp2)) {
		fscanf(fp2, "%d", &trainOutput[i]);
		i++;
	}

	fclose(fp1);
	fclose(fp2);
	
}


//************************************
// display results
void displayResults(void)
{
	for (int i = 0; i<numPatterns; i++)
	{
		patNum = i;
		calcNet(); // 최종으로 조정된 weight 값을 가지고 계산
		printf("pat = %d actual = %d neural model = %f\n", patNum + 1, trainOutput[patNum], outPred);
		// trainOutput[patNum] = 실제 나와야 하는 값
		//outPred = neural에 의한 예측 값(학습 이후)
	}
}


//************************************
// calculate the overall error
// 각 test당 전체 error 값을 도출
void calcOverallError(void)
{
	RMSerror = 0.0;
	for (int i = 0; i<numPatterns; i++)
	{
		patNum = i;
		calcNet();
		RMSerror = RMSerror + (errThisPat * errThisPat);
	}
	RMSerror = RMSerror / numPatterns;
	RMSerror = sqrt(RMSerror);
}



//==============================================================
//********** THIS IS THE MAIN PROGRAM **************************
//==============================================================

int main(void)
{
	// seed random number function
	srand(time(NULL));

	// initiate the weights
	initWeights();

	// load in the data
	initData();

	// train the network
	// 총 numEpochs만큼 train
	for (int k = 0; k < 100; k++) {
		for (int j = 0; j <= numEpochs; j++)
		{
			for (int i = 0; i < numPatterns; i++)
			{
				//select a pattern at random
				// 임의로 테스트할 데이터를 고름( 1~ 38번 데이터 중 1개 선택)
				patNum = rand() % numPatterns;

				//calculate the current network output
				//and error for this pattern
				// 선택한 데이터에 대한 계산을 하고 예측값을 구한 후 해당 예측값에 대한 에러 값을 구함
				calcNet();

				//change network weights
				//구한 에러값을 가지고 weight를 조정함
				WeightChangesHO();
				WeightChangesHH();
				WeightChangesIH();
			}
		}
	}

	//training has finished
	//display the results
	displayResults();

	return 0;
}
