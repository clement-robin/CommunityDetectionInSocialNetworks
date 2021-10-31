#include <iostream>

using namespace std;

class Date {
    public:
        void setJour(int j) {
            jour = j;
        }
        void setMois(int m) {
            mois = m;
        }
        void setAnne(int a) {
            annee = a;
        }
        int getJour() {
            return jour;
        }
        int getMois() {
            return mois;
        }
        int getAnee() {
            return annee;
        }
        void affiche_date(){
            cout << "Date : ";
            if(jour<10) {
                cout << "0" ;
            }
            cout << jour << "/";
            if(mois<10) {
                cout << "0" ;
            }
            cout << mois << "/" << annee << endl;
        }
        

    protected:
        int jour;
        int mois;
        int annee;
};