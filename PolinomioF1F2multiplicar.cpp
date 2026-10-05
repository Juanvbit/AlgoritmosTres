#include <iostream>
#include <cmath>

using namespace std;


class PolF1 {
private:
    int* vec;
    int tam;

public:
    
    PolF1() {
        tam = 1;
        vec = new int[1];
        vec[0] = 0; 
    }

    
    PolF1(int grado) {
        tam = grado + 2;
        vec = new int[tam]();
        vec[0] = grado; 
    }

    
    void setCoeficiente(int exp, float coef) {
        int grado = vec[0];
        if (exp <= grado) {
            
            vec[1 + (grado - exp)] = static_cast<int>(coef);
        }
    }

    
    void mostrar() const {
        int grado = vec[0];
        if (grado == 0 && vec[1] == 0) {
            cout << "0" << endl;
            return;
        }

        bool primero = true;
        for (int i = 0; i <= grado; i++) {
            int coef = vec[1 + i];
            int exp = grado - i;

            if (coef != 0) {
                if (!primero && coef > 0) cout << " + ";
                if (coef < 0) cout << " - ";

                int val = abs(coef);
                if (val != 1 || exp == 0) cout << val;

                if (exp > 0) cout << "x";
                if (exp > 1) cout << "^" << exp;

                primero = false;
            }
        }
        if (primero) cout << "0";
        cout << endl;
    }
};


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
                if (ant == nullptr) cabeza = act->sig;
                else ant->sig = act->sig;
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

    
    int getGrado() const {
        if (cabeza == nullptr) return 0;
        return cabeza->exponente;
    }

    
    PolF1 multiplicarAPolF1(PolF2 b) {
        
        PolF2 temp;

        for (Termino* aux1 = this->cabeza; aux1 != nullptr; aux1 = aux1->sig) {
            for (Termino* aux2 = b.cabeza; aux2 != nullptr; aux2 = aux2->sig) {
                float nuevoCoef = aux1->coeficiente * aux2->coeficiente;
                int nuevoExp = aux1->exponente + aux2->exponente;

                temp.insertarTermino(nuevoCoef, nuevoExp);
            }
        }

        
        int gradoResultado = temp.getGrado();

        
        PolF1 resultado(gradoResultado);

        
        for (Termino* aux = temp.cabeza; aux != nullptr; aux = aux->sig) {
            resultado.setCoeficiente(aux->exponente, aux->coeficiente);
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

    cout << "=== POLINOMIO 1 (PolF2) ===" << endl;
    p1.leer();

    cout << "\n=== POLINOMIO 2 (PolF2) ===" << endl;
    p2.leer();

    cout << "\nPolinomio 1 (PolF2): ";
    p1.mostrar();
    cout << "Polinomio 2 (PolF2): ";
    p2.mostrar();

    
    PolF1 resultadoF1 = p1.multiplicarAPolF1(p2);

    cout << "\n===================================" << endl;
    cout << "Resultado (Objeto retenido en PolF1): ";
    resultadoF1.mostrar();
    cout << "===================================" << endl;

    return 0;
}