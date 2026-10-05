#include <iostream>
#include <cmath>

using namespace std;


struct Termino {
    float coeficiente;
    int exponente;
    Termino* sig;

    Termino(float c, int e) : coeficiente(c), exponente(e), sig(nullptr) {}
};

class PolF2 {
private:
    Termino* cabeza;

public:
    PolF2() : cabeza(nullptr) {}

    
    void insertarTermino(float coef, int exp) {
        if (abs(coef) < 1e-6f) return;

        Termino* act = cabeza;
        Termino* ant = nullptr;

        while (act != nullptr && act->exponente > exp) {
            ant = act;
            act = act->sig;
        }

        if (act != nullptr && act->exponente == exp) {
            act->coeficiente += coef;
            if (abs(act->coeficiente) < 1e-6f) {
                if (ant == nullptr) {
                    cabeza = act->sig;
                } else {
                    ant->sig = act->sig;
                }
                delete act;
            }
            return;
        }

        Termino* nuevo = new Termino(coef, exp);
        if (ant == nullptr) {
            nuevo->sig = cabeza;
            cabeza = nuevo;
        } else {
            ant->sig = nuevo;
            nuevo->sig = act;
        }
    }

    
    bool sonIguales(PolF2 b) const {
        Termino* aux1 = this->cabeza;
        Termino* aux2 = b.cabeza;

        while (aux1 != nullptr && aux2 != nullptr) {
            if (aux1->exponente != aux2->exponente || abs(aux1->coeficiente - aux2->coeficiente) > 1e-6f) {
                return false;
            }
            aux1 = aux1->sig;
            aux2 = aux2->sig;
        }

        return (aux1 == nullptr && aux2 == nullptr);
    }

    void leer() {
        int numTerminos;
        cout << "¿Cuantos terminos deseas ingresar? ";
        cin >> numTerminos;

        for (int i = 0; i < numTerminos; i++) {
            float coef;
            int exp;
            cout << "Ingresa el coeficiente: ";
            cin >> coef;
            cout << "Ingresa el exponente: ";
            cin >> exp;
            insertarTermino(coef, exp);
        }
    }

    void mostrar() const {
        if (cabeza == nullptr) {
            cout << "0" << endl;
            return;
        }

        Termino* aux = cabeza;
        bool primero = true;

        while (aux != nullptr) {
            if (!primero && aux->coeficiente > 0) cout << " + ";
            if (aux->coeficiente < 0) cout << " - ";

            float val = abs(aux->coeficiente);
            if (val != 1 || aux->exponente == 0) cout << val;

            if (aux->exponente > 0) cout << "x";
            if (aux->exponente > 1) cout << "^" << aux->exponente;

            primero = false;
            aux = aux->sig;
        }
        cout << endl;
    }
};

int main() {
    PolF2 p1, p2;

    cout << "=== POLINOMIO 1 ===" << endl;
    p1.leer();

    cout << "\n=== POLINOMIO 2 ===" << endl;
    p2.leer();

    cout << "\nPolinomio 1: ";
    p1.mostrar();
    cout << "Polinomio 2: ";
    p2.mostrar();

    cout << "\n===================================" << endl;
    if (p1.sonIguales(p2)) {
        cout << "Resultado: Los polinomios SON iguales." << endl;
    } else {
        cout << "Resultado: Los polinomios NO son iguales." << endl;
    }
    cout << "===================================" << endl;

    return 0;
}