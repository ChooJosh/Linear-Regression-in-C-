/*
 * Project1.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: JoshChoo
 */

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

double sumVec(vector<double> vec){
	double sum = 0;
	for(int i = 0; i < vec.size(); ++i)
	{
	sum += vec[i];
	}
	return sum;
}

double meanVec(vector<double> vec){
	return sumVec(vec)/vec.size();
}

double wEstimate(vector<double> vec1, vector<double> vec2){
	vector<double> temp1;
		for(int i = 0; i < vec1.size();i++){
			//store new values into temp1 vector
			temp1.push_back((vec1[i]-meanVec(vec1))*(vec2[i]-meanVec(vec2)));
		}
		double sum1 = 0;
		for(int i = 0; i< temp1.size();i++){
			sum1+= temp1[i];
		}

	vector<double> temp2;
		for(int i = 0; i < vec1.size();i++){
				//store new values into temp2 vector
				temp2.push_back(pow(vec1[i]-meanVec(vec1), 2.0));
			}
		double sum2 = 0;
		for(int i = 0; i< temp2.size();i++){
			sum2+= temp2[i];
		}

		return sum1/sum2;
}
double bEstimate(vector<double> vec1, vector<double> vec2){
	return meanVec(vec2) -  wEstimate(vec1, vec2) * meanVec(vec1);
}

double cov(vector<double> vec1, vector<double> vec2){
	vector<double> temp;
	for(int i = 0; i < vec1.size();i++){
		//store new values into temp vector
		temp.push_back((vec1[i]-meanVec(vec1))*(vec2[i]-meanVec(vec2)));
	}
	return sumVec(temp)/(temp.size()-1);
}

double SD(vector<double> vec){
	double var = 0;
	for(int i = 0; i < vec.size();i++){
		var += pow(vec[i] - meanVec(vec), 2);
		}
	return sqrt(var/vec.size());
}

double cor(vector<double> vec1, vector<double> vec2){
	double temp = cov(vec1, vec2);
	//equation
	return temp/(SD(vec1)*(SD(vec2)));
}

double mse(vector<double> vec1, vector<double> vec2){
	vector<double> predicted;
	vector<double> temp;
	for(int i=0; i<vec1.size();i++){
	predicted.push_back(wEstimate(vec1, vec2)*vec1[i]+bEstimate(vec1, vec2));
	}
	for(int i=0;i<vec1.size();i++){
	 temp.push_back(pow(vec1[i]-predicted[i], 2.0));
	}
	double mse = meanVec(temp)/vec1[0];
	return mse;
}

double rmse(vector<double> vec1, vector<double> vec2){
return sqrt(mse(vec1, vec2));
}

int main()
{
	//calculate time
	clock_t begin, end;
	double time;
	begin = clock();

//Read through file

ifstream myFile;
vector<double> Vecrm;
vector<double> Vecmedv;
myFile.open("Boston.csv");

string rm;
string medv;

getline(myFile, rm, ',');
getline(myFile, medv);


	while (myFile.good()){
			getline(myFile, rm, ',');
			getline(myFile, medv);

			Vecrm.push_back(stod(rm));
			Vecmedv.push_back(stod(medv));
		}

	myFile.close();

	cout<<"W estimate: "<<wEstimate(Vecrm, Vecmedv)<<endl;
	cout<<"B estimate: "<<bEstimate(Vecrm, Vecmedv)<<endl;
	cout<<"Correlation: "<<cor(Vecrm, Vecmedv)<<endl;
	cout<<"Predicted values: "<<endl;
	vector<double> predicted;
	for(int i=0; i<Vecrm.size();i++){
	predicted.push_back(wEstimate(Vecrm, Vecmedv)*Vecrm[i]+bEstimate(Vecrm, Vecmedv));
	}
	for(int i=0; i<predicted.size();i++){
		cout<<predicted[i]<<endl;
	}
	cout<<"MSE: "<<mse(Vecrm, Vecmedv)<<endl;
	cout<<"RMSE: "<<rmse(Vecrm, Vecmedv)<<endl;

	end = clock();
	time = (double)(end - begin) / CLOCKS_PER_SEC;
	cout<<"Run time: "<<time<<endl;
	return 0;
}


