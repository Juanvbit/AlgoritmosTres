#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class PolF1 {
private:
    float* vec; 
    int capacidad;

    
    void redimensionar(int nuevoGrado) {
        int nuevaCapacidad = nuevoGrado + 2;
        float* nuevoVec = new float[nuevaCapacidad]();
        
        nuevoVec[0] = static_cast<float>(nuevoGrado);

        int gradoActual = (vec != nullptr) ? static_cast<int>(vec[0]) : -1;
        if (vec != nullptr) {
            for (int exp = 0; exp <= min(gradoActual, nuevoGrado); ++exp) {
                int posAnt = 1 + (gradoActual - exp);
                int posNue = 1 + (nuevoGrado - exp);
                nuevoVec[posNue] = vec[posAnt];
            }
            delete[] vec;
        }

        vec = nuevoVec;
        capacidad = nuevaCapacidad;
    }

    
    void ajustarGrado() {
        int gradoActual = getGrado();
        while (gradoActual > 0 && abs(vec[1]) < 1e-6f) {
            float* nuevoVec = new float[gradoActual + 1]();
            nuevoVec[0] = static_cast<float>(gradoActual - 1);
            for (int exp = 0; exp <= gradoActual - 1; ++exp) {
                int posAnt = 1 + (gradoActual - exp);
                int posNue = 1 + ((gradoActual - 1) - exp);
                nuevoVec[posNue] = vec[posAnt];
            }
            delete[] vec;
            vec = nuevoVec;
            gradoActual--;
        }
    }

public:
    PolF1() {
        capacidad = 2;
        vec = new float[capacidad]();
        vec[0] = 0.0f; 
    }

    ~PolF1() {
        delete[] vec;
    }

    int getGrado() const {
        return static_cast<int>(vec[0]);
    }

    
    void insertar(int exp, float coe) {
        if (abs(coe) < 1e-6f) return; 

        int gradoActual = getGrado();

        
        if (exp > gradoActual) {
            redimensionar(exp);
            gradoActual = exp;
        }

        
        int pos = 1 + (gradoActual - exp);
        vec[pos] += coe;

        ajustarGrado();
    }

    
    void leerPorConsola() {
        int numTerminos;
        cout << "¿Cuantos terminos deseas ingresar? ";
        cin >> numTerminos;

        for (int i = 0; i < numTerminos; i++) {
            float coef;
            int exp;
            cout << "\nTermino " << (i + 1) << ":" << endl;
            cout << "  Ingresa el coeficiente: ";
            cin >> coef;
            cout << "  Ingresa el exponente: ";
            cin >> exp;

            
            insertar(exp, coef);
        }
    }

    void mostrar() const {
        int grado = getGrado();
        bool primero = true;

        for (int exp = grado; exp >= 0; --exp) {
            float coef = vec[1 + (grado - exp)];
            if (abs(coef) > 1e-6f) {
                if (!primero && coef > 0) cout << " + ";
                if (coef < 0) cout << " - ";

                float val = abs(coef);
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

int main() {
    PolF1 polinomio;

    cout << "=== INGRESO INTERACTIVO DE TERMINOS (PolF1) ===" << endl;

    polinomio.leerPorConsola();

    cout << "\n===================================" << endl;
    cout << "Polinomio resultante ingresado: ";
    polinomio.mostrar();
    cout << "===================================" << endl;

    return 0;
}