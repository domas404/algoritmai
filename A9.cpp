//Sveikojo skaičiaus konvertavimas iš m-tainės į n-tainę skaičiavimo sistemą.
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;
typedef numeric_limits<double> dbl;

// mazosios raides verciamos i didziasias
void toUpper(string &num){
    for (int i=0; i<num.length(); ++i){
        if (!isupper(num[i]))
            num[i]=toupper(num[i]);
    }
}
// funkcija duomenims ivesti
void Input(int &n, int &m, string &num){
    do{
        cout << setw(52) << left << "Is kokios skaiciavimo sistemos norite konvertuoti? ";
        cin >> m;
    } while (m < 2 || m > 36);
    do{
        cout << setw(52) << left << "I kokia skaiciavimo sistema norite konvertuoti? ";
        cin >> n;
    } while (n < 2 || n > 36);
    cout << setw(52) << left << "Iveskite skaiciu, kuri norite konvertuoti: ";
    cin >> num;
}
// funkcija isvedanti konvertuota skaiciu
template <typename T1, typename T2>
void Output(T1 num, T2 res){
    cout.precision(dbl::max_digits10);
    cout << setw(17) << left << "Entered number: " << num << endl;
    cout << setw(17) << left << "Result number: " << res << endl;
}
// funkcija konvertuojanti n-taine sk. sist. i desimtaine
double nBaseToDecimal (string num, string el, int m){
    int a=-1; // laipsnis, kuriuo bus keliamas m
    int b=0;
    double fnum=0;
    vector<char> v(num.begin(), num.end());
    if (v[0] == '-') b=1;
    for (int i=b; i<num.length(); i++){
        if (v[i] == '.') break;
        a++;
    }
    for (int i=b; i<num.length(); i++){
        for (int j=0; j<36; j++){
            if (v[i] == el[j]){
                fnum += (j)*pow(m, a);
                --a;
                break;
            }
        }
    }
    if (v[0] == '-') fnum*=(-1);
    return fnum;
}
// funkcija konvertuojanti desimtaine sk. sist. i n-taine
// num - desimtainis sk, n - base i kuria convertuojama, el - visi galimi simboliai
string decimal_to_nBase(double num, int n, string el){
    double r;
    int a, z=0;
    vector<int> liek;       // liekana
    long long rnum;         // sveikoji skaiciaus dalis
    bool isPositive = true; // ar skaicius teigiamas
    string fnum;            // n-taines sistemos sk
    if (num < 0){
        isPositive = false;
        num = abs(num);
    }
    rnum = floor(num);
    while(rnum!=0){
        liek.push_back(rnum%n);
        rnum=rnum/n;
        z++;
    }
    if (!isPositive)
        fnum = "-";
    if (z>0){
        for (int j=z-1; j>=0; j--)
            fnum += el[liek[j]];
    }
    num -= floor(num);  // atimama sveikoji skaiciaus dalis
    if (num != 0){
        if (z>0) fnum += ".";
        else fnum = "0.";
        for (int i=0; i<10; i++){  // 10 sk po kableliu tikslumas
            r = num*n;
            a = floor(r);
            r -= a;
            num = r;
            if (num-a == 0) break; // jei sk po kablelio maziau, ciklas baigiasi
            fnum += el[a];
        }
    }
    return fnum;
}
// funkcija vykdanti skaiciavimus pagal situacija
void Calculate(){
    string el = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string num, result;  // string tipo num ir res
    int m, n;            // m - from base, n - to base
    double res, nmb;     // double tipo num ir res
    Input(n, m, num);
    if (m == 10){
        stringstream convert(num);
        convert >> nmb;
        result = decimal_to_nBase(nmb, n, el);
        Output(num, result);
    }
    else if (n == 10){
        toUpper(num);
        res = nBaseToDecimal(num, el, m);
        Output(num, res);
    }
    else {
        toUpper(num);
        res = nBaseToDecimal(num, el, m);
        result = decimal_to_nBase(res, n, el);
        Output(num, result);
    }
}
int main(){
    bool repeat=true; // ciklo kartojimas
    string a;         // naudotojo input (y/n) ar testi cikla
    do {
        cout << endl;
        Calculate();
        cout << endl;
        cout << "Ar norite konvertuoti kita skaiciu? (y/n) ";
        cin >> a;
        if (a == "n") repeat=false;
    } while (repeat);
    return 0;
}