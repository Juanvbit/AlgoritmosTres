import java.util.Scanner;
public class Punteros {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int dato = 0;
        int[] numeros = new int[5];
        for (int i = 0; i < numeros.length; i++) {
            System.out.println("Ingrese numero entero "+(i + 1)+ ": "  );
            dato = scanner.nextInt();
            numeros[i] = dato;
        }
        int[] puntero = numeros; // puntero apunta al mismo arreglo que numeros
        System.out.println("Contenido del arreglo original:");
        for (int num : numeros) {
            System.out.print(num + " ");
        }
        // Modificando el arreglo a través del puntero
        puntero[0] = 10;
        System.out.println("\nContenido del arreglo después de modificar a traves del puntero:");
        for (int num : numeros) {
            System.out.print(num + " ");
        }
    }
}
