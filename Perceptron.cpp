#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdlib.h>
using namespace std;

class logic_gate {

private:
	int delta = 0;
	int count = 0;
	int iteration = 1;
	//배열 선언
	int x[10] = {};
	int err_x[10] = {};
	double w[10] = {};
	int answer[4] = {};

public:
	double* learning(int n,int delta, int err_x[], double w[]) { // 오차를 가지고 weight 조정하기
		double delta_w[4] = {};
		float learning_rate = 0.23;
		for (int i = 0; i < n+1; i++) {
			delta_w[i] = learning_rate * delta * err_x[i];
			w[i] = w[i] + delta_w[i];
		}
		return w;
	}

	int output(int n, int x[], double w[]) { //x와 w들의 합을 구한후 1과 0으로 답을 만들기
		double xw = 0;
		for (int i = 0; i < n+1; i++) {
			xw += x[i] * w[i];//x와 w 들의 합 구하기
		}
		int result;
		if (xw >= 0) { //퍼셉트론에서 0보다 크면 1 작으면 0으로 답만들기
			result = 1;
		}
		else {
			result = 0;
		}
		return result;
	}

	int* answer_fuc(int gatenum,int answer[]) {//각 gate에 해당하는 정답 만들기
		if (gatenum == 1) {
			answer[0] = 0;
			answer[1] = 0;
			answer[2] = 0;
			answer[3] = 1;
			cout << "AND gate" << endl;
		}
		else if (gatenum == 2) {
			answer[0] = 0;
			answer[1] = 1;
			answer[2] = 1;
			answer[3] = 1;
			cout << "OR gate" << endl;
		}
		else if (gatenum == 3) {
			answer[0] = 0;
			answer[1] = 1;
			answer[2] = 1;
			answer[3] = 0;
			cout << "XOR gate" << endl;
		}
		else { 
			cout << "wrong input" << endl;
			exit(0);
		}
		return answer;
	}

	void run(int n ,int gatenum) {
		answer_fuc(gatenum, answer); //gate에 맞는 정답 만들기

		x[0] = -1;
		err_x[0] = -1;
		

		srand(time(0));
		for (int i = 0; i < n + 1; i++) {
			double b = (rand() % 21 - 10) / 10.0;//초기 weight 랜덤 설정(-1~1)
			w[i] = b;
		}

		while (count < 4) {
			cout << "iteration : " << iteration << endl;
			int num = 0;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					x[1] = i;
					x[2] = j;


					cout << " x,y배열의 확인" << endl;
					for (int i = 0; i < n+1; i++) {
						cout << "x" << "(" << i << ")" << x[i] << "  ";
						cout << "w" << "(" << i << ")" << w[i] << endl;
					}

					int result = output(n,x, w); //xw들의 합을 통해 1,0 판단

					cout << answer[num] << endl;
					if (result == answer[num]) {
						cout << "correct" << endl;
						count++;
					}
					else {
						cout << "wrong" << endl; //(0,0)(0,1)(1,0)(1,1) 순서에서 가장 마지막으로 못맞춘 것 부터 학습
						err_x[1] = x[1];
						err_x[2] = x[2];
						delta = answer[num] - result;
					}
					cout << endl;
					num++;
				}
			}
			cout << "맞은 개수" << count << endl << endl;

			if (count == 4) { break; } // 모두 정답이면 while문 반복 끝

			learning(n,delta, err_x, w); // weight값 수정

			iteration++;
			count = 0;
			if (iteration == 10000) {
				cout << "iteration:" << iteration << endl << "fail";
				exit(0);
			}
		}
		cout << "CORRECT!!!!!!~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
};

int main() {

	int n = 2;
	int gatenum = 1;
	cout << " AND gate면 1, OR gate 면 2, XOR gate 면 3을 입력하시오.: ";
	cin >> gatenum;
	logic_gate logic;

	logic.run(n, gatenum);
}
