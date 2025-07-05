#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;



bool KiemTra(int n){
    int can_bac_hai = round(sqrt(n));
    return pow(can_bac_hai,2) == n; 
}

int main(){
    int Val;
    ifstream inputFile("FSTREAM.inp");
    inputFile >> Val;
    ofstream outputFile("FSTREAM.out");
    if(KiemTra(Val)){
        outputFile<<"YES";
    }
    else{
    outputFile<<"NO";
    };
    inputFile.close();
    outputFile.close();

    return 0;
}