

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

string scramble(string s);

int main() {

	string word;
	string scrambled;
	string guess;
    while (word != "exit"){
		cout << "Enter word to be scrambled \n" ;
		cin >> word;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		scrambled = scramble(word);
		cout << scrambled << "\n";
		for(int i = 0; i < 5 ; i++){
			cout << "Enter guess " << i <<"\n";
			cin >> guess;
			if(guess.compare(word) == 0){
				cout << "Win \n";
				break;
			}
		}
	}	
}

string scramble(string s){
	
	int size = s.size()/2;
	if (size == 1 || size ==0){
		return s;
	}
	else if(size == 3){
		return scramble(s.substr(0,1)).append(scramble(s.substr(1)));
	}
	else if(size%2 == 0){
		string a = s.substr(0,size);
		string b = s.substr(size);
		return scramble(b).append(scramble(a));
	}
	else {
		
		string a = s.substr(0,size);
		string b = s.substr(size);
		return scramble(a).append(scramble(b));
	}

}