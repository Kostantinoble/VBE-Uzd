#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Mokiniai{
    string vardas;
    string pamoka;
    int pazSkaic;
    vector<int> pazymiai;
    float vidurkis;
};

struct Pamoka{
    string pavadinimas;
    vector<string> mokiniai;
    int kiekMok;
};


float vidurkisSkaic(Mokiniai mok){
    int suma = 0;
    float vidurkis = 0;
    for(int pazymis : mok.pazymiai){
        suma += pazymis;
    }
    vidurkis = (float)suma/mok.pazSkaic;

    return vidurkis;
}

bool pamokuTikrintojas(vector<Pamoka> &pamokos,string pamoka,string vardas){
    for(Pamoka &p : pamokos){
        if(pamoka == p.pavadinimas){
            p.kiekMok++;
            p.mokiniai.push_back(vardas);
            return true;
        } 


    }
    return false;
}

void rikiavimas(vector<Pamoka> &pamokos){
    for(Pamoka &pamoka : pamokos){
        for(Pamoka &pamoka1 : pamokos){
            if(pamoka.kiekMok > pamoka1.kiekMok){
                swap(pamoka,pamoka1);
            } else if(pamoka.kiekMok == pamoka1.kiekMok){
                if (pamoka.pavadinimas < pamoka1.pavadinimas){
                    swap(pamoka,pamoka1);
                }
            }
            
        } 
    }
}




int main(){
    ifstream fin;
    ofstream fout;
    Mokiniai mok[50];
    vector<Pamoka> pam;
    int mokSkaic = 0;
    fin.open("U2.txt");
    fin >> mokSkaic;
    for (int i = 0; i < mokSkaic; i++){
        fin >> mok[i].vardas;
        fin >> mok[i].pamoka;
        fin >> mok[i].pazSkaic;
        for(int j = 0; j < mok[i].pazSkaic; j++){
            int temp;
            fin >> temp;
            mok[i].pazymiai.push_back(temp);
        }
    }
    fin.close();

    for(int i = 0; i < mokSkaic; i++){
        mok[i].vidurkis = vidurkisSkaic(mok[i]);
    }

    for(int i = 0; i < mokSkaic; i++){
        if(mok[i].vidurkis >= 9 && !pamokuTikrintojas(pam, mok[i].pamoka, mok[i].vardas)){
            Pamoka naujaPamoka;
            naujaPamoka.pavadinimas = mok[i].pamoka;
            naujaPamoka.mokiniai.push_back(mok[i].vardas);
            naujaPamoka.kiekMok = 1;
            pam.push_back(naujaPamoka);
        }
    }

    rikiavimas(pam);

    fout.open("U2rez.txt");
    if(pam.empty()){
        fout << "Neatitinka vidurkis";
        return 1;
    }
    for(Pamoka p : pam){
        fout << p.pavadinimas << " " << p.kiekMok << endl;
        for(int i = 0; i < p.kiekMok; i++){
            fout << p.mokiniai.at(i) << endl;
        }
    }
    fout.close();
    return 0;
}