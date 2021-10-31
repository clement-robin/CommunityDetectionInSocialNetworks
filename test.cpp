#include "test.h"

using namespace std;



int main() {
    Date da;
    da.setJour(16);
    da.setMois(10);
    da.setAnne(2000);

    da.affiche_date();
    return 0;
}