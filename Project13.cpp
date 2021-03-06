#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<cmath>
using namespace std;

class logic_gate {

private:
	double w[10] = {};


public:
	double* learning_act(int n, double delta, double err_x[], double w[]) { // 오차를 가지고 weight 조정하기
		double delta_w[100] = {};
		double learning_rate = 0.2;
		for (int i = 0; i < n; i++) {
			delta_w[i] = learning_rate * delta * err_x[i];
			w[i] -= delta_w[i];
		}
		return w;
	}


	double output(int n, float bias, double x[], double w[]) { //x와 w들의 합을 구하기
		double xw = 0;
		for (int i = 0; i < n; i++) {
			xw += x[i] * w[i];//x와 w 들의 합 구하기

		}
		xw += bias;
		return xw;
	}

	double* weight(int n) {

		for (int i = 0; i < n; i++) {
			double b = (rand() % 201 - 100) / 100.0;//초기 weight 랜덤 설정(-1~1)
			w[i] = b;
		}
		return w;
	}

	double sigmoid(double x) {
		return 1 / (1 + exp(-x));
	}
	double relu(double x) {
		if (x >= 0) {
			return x;
		}
		else { return 0; }
	}
	double d_sigmoid(double x) {
		return sigmoid(x)*(1 - sigmoid(x));
	}
	double d_relu(double x) {
		if (x >= 0) {
			return 1;
		}
		else { return 0; }
	}

};


int main() {

	//hidden layer 1, hidden layer input

	int layer_num = 2;
	cout << "first hidden node :";
	cin >> layer_num;

	logic_gate logic;
	
	// input layer(2 node) 9data
	//double train_set_x[][2] = { {0.,0.},{0.,1.},{1.,0.},{1.,1.},{0.5,1.},{1.,0.5},{0.,0.5},{0.5,0.},{0.5,0.5} };
	double train_set_x[][2] = { {0.,0.},{0.,1.},{1.,0.},{1.,1.} };
	double train_set_y[] = { 0,1,1,0 };
	//double train_set_y[] = { 0,0,0,0,0,0,0,0,1 };
	srand(time(0));

	double weight[100][2] = {};
	// input-hidden weight random
	for (int i = 0; i < layer_num; i++) {
		double* asd = logic.weight(2);
		for (int j = 0; j < 2; j++) {
			weight[i][j] = asd[j];
		}
	}

	//check_weight
	for (int i = 0; i < layer_num; i++) {
		for (int j = 0; j < 2; j++) {
			cout << "weight" << i << weight[i][j] << endl;
		}
	}
	// hidden-last weight random
	double* weight2 = logic.weight(layer_num);
	//check weight2
	for (int i = 0; i < layer_num; i++) {
		cout << "weight2" << weight2[i] << endl;
	}


	double net = 0;
	double active_output = 0;
	double delta = 0;





	ofstream txt;
	txt.open("donut.txt");

	double net_a[100] = {};
	double save[100] = {};
	int count = 0;
	int iter = 0;
	double err = 1;

	while (err > 0.005) {//train 
		count = 0;
		iter++;

		cout << "iter: " << iter << endl;

		err = 0;
		
		for (int data = 0; data < 4; data++) {

			// make first hidden layer (layer_num node) 
			for (int i = 0; i < layer_num; i++) {
				net_a[i] = logic.output(2, 0.2, train_set_x[data], weight[i]);
				save[i] = logic.relu(net_a[i]);
			}


			// last layer (1 node)
			net = logic.output(layer_num, 0.2, save, weight2);
			active_output = logic.sigmoid(net);

			delta = train_set_y[data] - active_output;
			err += delta * delta / 2;

			double* before_weight = weight2;

			// hidden-final backpropa
			delta = -delta * logic.d_sigmoid(net);
			weight2 = logic.learning_act(layer_num, delta, save, weight2);//weight leraning



			// input-hidden backpropa
			for (int i = 0; i < layer_num; i++) {
				delta = delta * logic.d_relu(net_a[i])*before_weight[i];
				double* asd = logic.learning_act(2, delta, train_set_x[data], weight[i]);//weight learning
				for (int j = 0; j < 2; j++) {
					weight[i][j] = asd[j];
				}
			}


		}
		//txt save
		for (int i = 0; i < layer_num; i++) {
			for (int j = 0; j < 2; j++) {
				txt << weight[i][j] << " ";
			}
		}
		for (int i = 0; i < layer_num; i++) {
			txt << weight2[i] << " ";
		}
		txt << err << endl;

		cout << "err:  " << err << endl;
		
	}
	txt.close();
	cout << "~~~~~~~~~";
}