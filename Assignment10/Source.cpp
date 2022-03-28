#include <iostream>
#include <vector>
#include <string>

using namespace std;

string userInput;
vector<int> hamCode;

bool userInputCheck(string bits) { // determines if user input is valid
	if (!(bits.size() <= 0 || bits.size() > 7)) {
		for (int i = 0; i < bits.size(); i++) {
			char bit = bits[i];
			if (bit == 48 || bit == 49) {}
			else {
				bits.erase(bits.begin() + i);
				i -= 1;
			}
		}

		if (bits.size() == 7) {
			userInput = bits;
			for (int i = 0; i < userInput.size(); i++) {
				hamCode.push_back(userInput[i] - 48);
			}
			return true;
		}
	}

	return false;
}

int bitCheck(vector<int> vec) { // finds the incorrect bit if there is one
	int errorBit = 0;

	int a = (vec[0] + vec[2] + vec[4] + vec[6]) % 2;
	int b = (vec[1] + vec[2] + vec[5] + vec[6]) % 2;
	int c = (vec[3] + vec[4] + vec[5] + vec[6]) % 2;
	
	if (a != 0 || b != 0 || c != 0) {
		if (a == 1) {
			errorBit += a * 1;
		}

		if (b == 1) {
			errorBit += b * 2;
		}

		if (c == 1) {
			errorBit += c * 4;
		}

		return errorBit;
	}
	else {
		return -1;
	}
}

vector<int> codeCorrect(vector<int> vec, int bit) { // corrects hamming code
	if (vec[bit - 1] == 0) {
		vec[bit - 1] = 1;
	}
	else if (vec[bit - 1] == 1) {
		vec[bit - 1] = 0;
	}

	return vec;
}

void output1(vector<int> vec) { // outputs a given vector
	cout << "[ " << vec[0];
	for (int i = 1; i < vec.size() - 1; i++) {
		cout << vec[i];
	}
	cout << vec[vec.size() - 1] << " ]\n";
}

void finalOutput(vector<int> vec) { // outputs all the information
	cout << "                 input: ";
	output1(vec);
	if (bitCheck(vec) != -1) {
		cout << "incorrect bit location: " << bitCheck(vec) << "\n";
		vec = codeCorrect(vec, bitCheck(vec));
		cout << "       corrected input: ";
		output1(vec);
	}
	cout << "       decimal message: " << ((vec[2] * 8) + (vec[4] * 4) + (vec[5] * 2) + (vec[6] * 1)) << "\n\n";
}

int main() {
	vector<int> A = { 1, 1, 0, 1, 0, 1, 0 }; // 1101010
	finalOutput(A);

	vector<int> B = { 0, 0, 1, 0, 1, 1, 1 }; // 0010111
	finalOutput(B);

	vector<int> C = { 1, 0, 1, 0, 1, 0, 1 }; // 1010101
	finalOutput(C);

	vector<int> D = { 1, 0, 0, 1, 0, 0, 1 }; // 1001001
	finalOutput(D);

	vector<int> E = { 0, 1, 1, 0, 0, 1, 1 }; // 0110011
	finalOutput(E);

	// takes hamming code from user
	while (true) {
		cout << "give me 7 bits: ";
		string bits;
		cin >> bits;

		if (userInputCheck(bits)) {
			finalOutput(hamCode);
		}
		else {
			cout << "not valid hamming code\n\n";
		}

		cout << "would you like to go again(Y or N)? ";
		string answer;
		cin >> answer;

		if (answer != "Y" && answer != "y") {
			break;
		}

		cout << endl;

		hamCode.clear();
		userInput.clear();
	}

	cout << "Goodbye!\n";
}