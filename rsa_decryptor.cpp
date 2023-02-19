#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

void convertToLetters(vector <int> decoded);
bool isPrime(int n);
bool pKeyValid(int p, int q);
long long int modInverse(long long int e, long long int phi_n);

int main() {
  
  long long int e,n = 0;
  cin >> e;
  cin >> n;

  //turning input string into vector of ints
  int limit = 0;
  cin >> limit;
  cin.ignore();
  string input;
  getline(cin, input);
  istringstream iss(input);
  vector<int> encoded;

  int val;
  int count = 0;
  while (iss >> val && count < limit) {
    encoded.push_back(val);
    ++count;
  }

  // finding p and q using b^2 = a^2 - N
  long long int a = 0;
  a = ceil(sqrt(n));
  long long int bsqr = 0;
  long long int b = 0;

  while (true) {
    bsqr = (a * a) - n;
    if (ceil(sqrt(bsqr)) == floor(sqrt(bsqr))) {
      b = sqrt(bsqr);
      break;
    }
    a++;
  }

  long long int p = a + b;
  long long int q = a - b;

  
  // computing phi n
  long long int phi_n = 0;
  phi_n = (p - 1) * (q - 1);

  // check validity of p and q
  if (!pKeyValid(p, q)) {
    cout << "Public key is not valid!";
    return 0;
  }

  // check if e and phi n are coprime
  if (__gcd(e, phi_n) != 1) {
  cout << "Public key is not valid!";
  return 0;
  }

  //find d using mod inverse function
  long long d = modInverse(e, phi_n);
  
  //printing q, p, phi n, d
  cout << q << " " << p;
  
  cout << " " << phi_n;

  cout << " " << d << endl;

  // looping through vector of ints to decipher each int using D(C);
  vector<int> decoded; //contains int values after decoding
  
  for (int i = 0; i < encoded.size(); i++) { 
    long long decoded_value = 1;
    
    for(int j = 0; j<d; j++){
      //multiplying number by itself d times and applying mod n each iteration to avoid overflow
        decoded_value = (decoded_value*encoded.at(i))%n;
    }
    
    cout << decoded_value;

    if(i!=encoded.size()-1)
    cout << " ";
    decoded.push_back(decoded_value);
  }
  cout << endl;
  convertToLetters(decoded); //passing vector of decoded ints to change into letters

  return 0;
}

long long int modInverse(long long int e, long long int phi_n) {
  long long d = 0;
  for (int i = 0; i < phi_n; i++) {
    if (((phi_n * i) + 1) % e == 0) {
      d = ((phi_n * i) + 1) / e;
      break;
    }
  }
  return d;
}

void convertToLetters(vector <int> decoded){
  for(int i = 0; i<decoded.size(); i++){

    if(decoded.at(i)>32){
      if(decoded.at(i) == 33)
        cout << " ";
      
      if(decoded.at(i) == 34)
        cout << '"';

      if(decoded.at(i) == 35)
        cout << ",";

      if(decoded.at(i) == 36)
        cout << ".";
      
      if(decoded.at(i) == 37)
        cout << "'";      
      
    }
    else
      cout << (char(decoded.at(i) - 7 + 'A'));
  }
  
}
bool isPrime(int n) {
  
  if (n <= 1)
        return false;
 
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
 
    return true;
}

bool pKeyValid(int p, int q) {
  if (p == q) {
    return false;
  }

  if (!isPrime(p) || !isPrime(q)) {
    return false;
  }

  return true;
}