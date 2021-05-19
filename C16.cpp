#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// tikrinama ar skaicius dalus is 3
bool isDivisibleBy3(int num){
    int suma=0;
    while(num > 0){
        suma += num%10;
        num /= 10;
    }
    if(suma%3 == 0) return true;
    else return false;
}
// tikrinama ar skaicius dalus is uz ji mazesniu pirminiu skaiciu
bool isDivisibleAtAll(int num, vector<int> prime){
    bool is_divisible;
    vector<int>::iterator it = prime.begin();
    for(it; it != prime.end(); ++it){
        if(num%(*it) == 0){
            is_divisible = true;
            break;
        }
    }
    if(is_divisible) return true;
    else return false;
}
// tikrinama ar palindromas
bool isPalindrome(int num){
    string reverse;
    int copy = num;
    while(copy > 0){
        reverse += to_string(copy%10);
        copy /= 10;
    }
    if(to_string(num) == reverse)
        return true;
    else return false;
}

// i konsole spausdinami tik tie pirminiai skaiciai, kurie yra palindromai
void palindromicPrimes(int a, int b, vector<int> &primes){
    int count=0;
    vector<int>::iterator it = primes.begin();
    while (((*it) < a) || !isPalindrome(*it)){
        ++it;
        if(it == primes.end()){
            cout << "Siame intervale palindrominiu pirminiu skaiciu nera." << endl;
            return;
        }
    }
    cout << "Palindrominiai pirminiai skaiciai intervale [" << a << ", " << b << "]:" << endl;
    cout << (*it);
    count++;
    ++it;
    for(it; it != primes.end(); ++it){
        if (isPalindrome(*it) && (*it) >= a){
            cout << ", " << (*it);
            count++;
        }
    }
    cout << endl;
    cout << "Palindrominiu pirminiu skaiciu siame intervale: " << count << endl;
}
// ieskomi visi pirminiai skaiciai nuo 0 iki b
void findPrimes(int b, vector<int> &primes){
    for (int i=0; i<=b; i++){
        if(i == 1) continue;
        if(i!=2 && i%2 == 0) continue;
        if(i!=3 && isDivisibleBy3(i)) continue;
        if(i!=5 && i%5 == 0) continue;
        if(isDivisibleAtAll(i, primes)) continue;
        primes.push_back(i);
    }
}
// intervalo ivedimas
void inputData(int &a, int &b){
    string pr, pab;
    cout << "Iveskite intervalo pradzia: ";
    cin >> pr;
    cout << "Iveskite intervalo pabaiga: ";
    cin >> pab;
    cout << endl;
    try {
        if(pr.find(".")!=pr.npos || pab.find(".")!=pab.npos)
            throw 303;
        a = stoi(pr);
        b = stoi(pab);
        if(b < 0 || a < 0)
            throw 404;
        else if(a > b)
            throw 505;
    }
    catch(int e){
        if(e == 303)
            cout << "Skaiciai turi buti \'int\' tipo." << endl;
        if(e == 404)
            cout << "Skaiciai turi buti neneigiami." << endl;
        else if(e == 505)
            cout << "Intervalo pradzia negali buti didesne uz pabaiga." << endl;
        cout << endl;
        inputData(a, b);
    }
}
// main funkcija
int main(){
    int a, b;
    vector<int> primes;
    inputData(a, b);
    auto start = chrono::high_resolution_clock::now();
    findPrimes(b, primes);
    palindromicPrimes(a, b, primes);
    primes.clear();
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << "programos veikimo laikas: ";
    cout << time_taken << " s" << endl;
}