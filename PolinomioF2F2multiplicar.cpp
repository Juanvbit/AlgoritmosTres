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
        if (coef == 0.0f) return;

        Termino* nuevo = new Termino(coef, exp);

        if (cabeza == nullptr || exp > cabeza->exponente) {
            nuevo->sig = cabeza;
            cabeza = nuevo;
            return;
        }

        Termino* act = cabeza;
        Termino* ant = nullptr;

        while (act != nullptr && act->exponente > exp) {
            ant = act;
            act = act->sig;
        }

        if (act != nullptr && act->exponente == exp) {
            act->coeficiente += coef;
            delete nuevo;
        } else {
            ant->sig = nuevo;
            nuevo->sig = act;
        }
    }

    
    PolF2 multiplicar(PolF2 b) {
        PolF2 resultado;

        for (Termino* aux1 = this->cabeza; aux1 != nullptr; aux1 = aux1->sig) {
            for (Termino* aux2 = b.cabeza; aux2 != nullptr; aux2 = aux2->sig) {
                float nuevoCoef = aux1->coeficiente * aux2->coeficiente;
                int nuevoExp = aux1->exponente + aux2->exponente;

                resultado.insertarTermino(nuevoCoef, nuevoExp);
            }
        }

        return resultado; 
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

    
    PolF2 producto = p1.multiplicar(p2);

    cout << "\n===================================" << endl;
    cout << "Resultado (Objeto PolF2): ";
    producto.mostrar();
    cout << "===================================" << endl;

    return 0;
}