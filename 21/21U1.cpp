#include <iostream>
#include <fstream>
using namespace std;



struct Laikai{
    int diena = 0;
    int ryt_prad_val = 0;
    int ryt_prad_min = 0;
    int ryt_pab_val = 0;
    int ryt_pab_min = 0;
    int ryt_sug = 0;
    int vak_prad_val = 0;
    int vak_prad_min = 0;
    int vak_pab_val = 0;
    int vak_pab_min = 0;
    int vak_sug = 0;
};

int main(){
    ifstream fin;
    ofstream fout;
    Laikai valandos[31];
    fin.open("U1.txt");
    int kiekis=0;
    int minimum=999999;
    fin >> kiekis;
    for(int i = 0; i < kiekis; i++){
        fin >> valandos[i].diena;
        fin >> valandos[i].ryt_prad_val >> valandos[i].ryt_prad_min;
        fin >> valandos[i].ryt_pab_val >> valandos[i].ryt_pab_min;
        fin >> valandos[i].vak_prad_val >> valandos[i].vak_prad_min;
        fin >> valandos[i].vak_pab_val >> valandos[i].vak_pab_min;
        valandos[i].ryt_sug = (valandos[i].ryt_pab_val*60 + valandos[i].ryt_pab_min) - (valandos[i].ryt_prad_val*60 + valandos[i].ryt_prad_min);
        valandos[i].vak_sug = (valandos[i].vak_pab_val*60 + valandos[i].vak_pab_min) - (valandos[i].vak_prad_val*60 + valandos[i].vak_prad_min);
    }
    fin.close();

    for(int i = 0; i < kiekis; i++){
        if(valandos[i].ryt_sug != 0 && valandos[i].vak_sug != 0){
            if(valandos[i].ryt_sug + valandos[i].vak_sug < minimum){
                minimum = valandos[i].ryt_sug + valandos[i].vak_sug;
            }
        }
    }

    fout.open("U1rez.txt");
    fout << "Minimalus laikas" << endl;
    fout << minimum << endl;
    fout << "Dienos" << endl;
    for(int i = 0; i < kiekis; i++){
        if(valandos[i].ryt_sug + valandos[i].vak_sug == minimum){
            fout << valandos[i].diena << " ";
        }
    }

    return 0;
}