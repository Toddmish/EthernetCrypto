//============================================================================
// Name        : EtheCrypto.cpp
// Author      : Todian Mishtaku
// Version     : v1.4.0
// Copyright   : Your copyright notice
// Description : CryptoGraphy in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cmath>


using namespace std;

const string task1Text="54686520736f6c7574696f6e2069733a2074686174776173746f6f65617379";

const string charset= "0123456789ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvwxyz-=[];',.!@#$%^&*()_+{}:|<>? " ;

const int charsetLen = charset.length();

string XOR2(string input, string key)
{
	string output; //THAT WAS MISSED

	for (unsigned i = 0; i < input.length(); i++)
	{
        char keyChar  = key[i % key.length()];
		char c = input[i] ^ keyChar;
		output += c;
	}
	return output;
}

// After my corrections it got symetric. It is not the same as XOR2 function
//because XOR here relies on a char set, but anyway it is symetric.

string XOR(string input, string key)
{
	string output; //THAT WAS MISSED

	for (unsigned i = 0; i < input.length(); i++)
	{
		unsigned posOfInputCharInCharset = max(0, (int)charset.find((char)input[i]));
        char keyChar  = key[i % key.length()];

        unsigned posOfKeyCharInCharset=max(0, (int)charset.find(keyChar));
        //cout<< "i="<<i<<"    "<<"keyChar = "<<keyChar<<" posOfKeyCharInCharset="<<posOfKeyCharInCharset<<" inputChar = "<<(char)input[i]<<"  ";
        //cout<<"posOfInputCharInCharset="<<posOfInputCharInCharset <<endl;

        int xorIndex = ((posOfInputCharInCharset) ^ (posOfKeyCharInCharset));

        // cout<<"xorIndex="<<xorIndex <<endl;

        //if(xorIndex<charsetLen)//That is WRONG!!!
		if(xorIndex>charsetLen)
		{
			xorIndex = posOfInputCharInCharset;
		}

	    char c= charset[xorIndex % charsetLen];

		//output -= charset[ xorIndex % charsetLen]; // WRONG!!!
		output += c;
	}
	return output;
}


string decrypt(string input, string key)
{

	char aInput[input.length()];
	//wcout<<"HI"<<input <<endl;
	int sum = 0;
	for (char v : key) {
		//wcout<<((char)v) <<endl;
		sum += int( (char)v)  >>  (1 << 1 << 1 + -0 ^ 1);
	}
	//cout<<"sum="<<sum <<endl;
	for (int i = 0; i < input.length(); i++) {
	  aInput[i] = (char)(input[i]) - char(i % sum);
	  //wcout<<aInput[i] <<endl;
	}
    return string(aInput);
}

bool isPalindromeStr(string word)
{
	int length= word.length();
	int half=length/2;
	//cout<<"half=" << half<<endl;
	//cout<<"length=" << length<<endl;
	for(int i=0;i<half; i++)
	{
		//cout<<"i="<< i<<endl;
		if(word[i]!=word[length-(i+1)])
		{
			return false;
		}
	}
	return true;
}

bool isPalindrome(int number)
{
	if(number<0)
	{
		number=-number;
	}
	string strnumb=to_string(number);
	return isPalindromeStr(strnumb);
}

int bruteForce2(const string input, const string output, string& returnKey)
{

	const int BitesNo=32;
	cout<<"Output contains : "<<output<<endl;
	cout<<"Brute Force 2 started ..."<<endl;
    string newKey;

	for (int i=0;i<256*256*256;i++)
		for (int j=0;j<8;j++)
		    for (int k=0;k<charsetLen;k++)
		    	for (int l=0;l<256*256*256;l++)
		    			for (int m=0;m<8;m++)
		    			    for (int n=0;n<charsetLen;n++)
			{

			    //bitset<BitesNo> bset(i);
				//newKey=bset.to_string(); //charset[i];
				//cout<<"newKey="<<newKey<<endl;
		    	newKey=charset[i];
		    	newKey+=(char)charset[j];
				newKey+=(char)charset[k];
				newKey+=charset[l];
				newKey+=(char)charset[m];
				newKey+=(char)charset[n];


				string decTask1 = XOR(input,newKey);
				int pos=decTask1.find(output);


				if(0<pos)
				{
					cout<<"pos="<<pos<<endl;
					cout<<"Key found =" <<newKey<<"  output =" <<decTask1<<endl;
					returnKey= string(newKey);
					//return 0; // Key found ,returned as third parameter
				}

			}

	return -1; // key not found
}

int bruteForce(const string input, const string output, string& returnKey)
{
    cout<<"Brute Force started ..."<<endl;
	string newKey;
	for (int i=0;i<charsetLen;i++)
		for (int j=0;j<charsetLen;j++)
			for (int k=0;k<charsetLen;k++)
			{
				newKey=charset[i];
				newKey+=(char)charset[j];
				newKey+=(char)charset[k];


				string decTask1 = decrypt(input,newKey);
				if( 0==decTask1.compare(output) )
				{
					//cout<<"Key found =" <<newKey<<"  output =" <<decTask1<<endl;
					returnKey= string(newKey);
					return 0; // Key found ,returned as third parameter
				}
				//cout<<"Task 1 output = " <<decTask1<<endl;
				//cout<<endl;

			}
	return -1; // key not found
}

void Task3() {
	cout << "Task 3" << endl;
	string input = "Eogukn";
	string output = "Energi";
	string keyToBefound;
	bruteForce(input, output, keyToBefound);
	cout << "Bruteforce routin found this key: " << keyToBefound << endl;
	cout << "Double check" << endl;
	cout << decrypt(input, keyToBefound) << dec << endl << endl;
}

void Task4() {
	//Task4 Write a routine that checks if a number is palindrome.
	cout << "Task 4" << endl;
	int numb = 0 + (rand() % 10000);
	;
	if (isPalindrome(numb)) {
		cout << "The number " << numb << " is " << " a palindrome number!"
				<< endl;
	} else {
		cout << "The number " << numb << " is NOT " << " a palindrome number!"
				<< endl;
	}
	cout << endl;
}

void Task1() {
	//Task1
	// I found : dec=The solution is: thatwastooeasy
	cout << "Task 1" << endl;
	string input = task1Text;
	string output = "The";
	string secretKey;
	if(bruteForce(input, output, secretKey)>-1)
	{
		cout << "Bruteforce routin found this key: " << secretKey << endl;
		cout << "Double check" << endl;
		cout << decrypt(input, secretKey) << dec << endl;
	}
	else
	{
		cout<<"No solution found!"<<endl;
	}
	cout<<endl;
}

void Task2() {
	//Task2
	cout << "Task 2" << endl;
	string sKey = "0000000000000001";
	cout << "dec=" << XOR("i04 CIR17QMJ G3: C8NU3IVIIIO3H", sKey) << endl;
	cout << endl;
}

int main()
{
	cout << endl;
	cout << "!!!Hello Crypto World !!" << endl<< endl; // prints !!!Hello World!!!

	//Task1

	// We see that the given text looks kind of hexdecimal format and we check that. After checking it comes that
	//decryption gives The solution is: thatwastooeasy
	Task1();


	//Task2
	Task2();

	//Task 3
	Task3();


	//Task4 Write a routine that checks if a number is palindrome.
	Task4();

    return 0;

}
