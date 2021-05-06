#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;;

struct Tranzitie{
    int destinatie;
    char litera;
};

ifstream f ("date.in");
ofstream g ("date.out");


string DFA(int S, string cuv, int nr_stari, vector <int> stari, vector <vector<Tranzitie>> lista_adiacenta, vector <int> stari_fin){
    int stare_cur = S;
        int nr_litera = 0;
        bool ok = 1;
        while (nr_litera < cuv.size() && ok == 1){
            ok = 0; // pornesc cu presupunerea ca nu mai exista o stare care sa contina litera curenta din cuvant
            int l;
            // gasesc pe ce poz se afla in vectorul de stari
            for (int j = 0; j < nr_stari; j++){
                if (stare_cur == stari[j])
                    l = j;
            }
            for (int k = 0; k < lista_adiacenta[l].size(); k++){
                // daca litera curenta se afla in lista de vecini ai starii
                if (lista_adiacenta[l][k].litera == cuv[nr_litera]){
                    // starea curenta devine destinatia starii pe care am gasit-o mai sus (lista_adiacenta[l][k])
                    stare_cur = lista_adiacenta[l][k].destinatie;
                    nr_litera ++ ;
                    ok = 1; // am gasit o stare deci continuam ded parcurs cuvantul
                }
            }}

        bool da = 0;
        if (nr_litera == cuv.size()){
            for (int j = 0; j < stari_fin.size(); j++){
                if (stare_cur == stari_fin[j]){
                    da = 1; // starea curenta in care ne-am oprit este o stare finala
                }
            }
        }
        if (da == 1)
            return "DA";
        else
            return "NU";

}


int main(){
    int nr_stari,
        nr_tranzitii;
    vector <int> stari;
    
    f>>nr_stari;
    int stare;
    for (int i = 0; i < nr_stari; i++){
        f >> stare;
        stari.push_back(stare);
        }
    f >> nr_tranzitii;
    vector <vector<Tranzitie>> lista_adiacenta(nr_stari,vector<Tranzitie>());
    for (int i = 0; i < nr_tranzitii; i++){
        f >> stare;
        
        Tranzitie t;
        f >> t.destinatie;
        f >> t.litera;
        
        for (int j = 0; j < nr_stari; j++){
            if (stari[j] == stare)
                stare = j;
        }
        lista_adiacenta[stare].push_back(t);
    }

    int S; // starea initiala
    f >> S;
    int nrF; // stari finale
    f >> nrF;
    vector <int> stari_fin;
    int sf;
    for (int i = 0; i < nrF; i++){
        f >> sf;
        stari_fin.push_back(sf);
    }
    int nr_cuv;
    f >> nr_cuv;
    string cuv;
    for (int i = 0; i < nr_cuv; i++){
        f >> cuv;
        g << DFA(S, cuv, nr_stari, stari, lista_adiacenta,stari_fin) << endl;;

    }
    return 0;
}
