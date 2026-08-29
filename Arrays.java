import java.util.Scanner;

public class Arrays {
    public static void main(String[] args) {
        try (Scanner teclado = new Scanner(System.in)) {

            System.out.print("Ingrese el tamaño del arreglo: ");

            int tam = teclado.nextInt();

            int[] array = new int[tam];

            System.out.println("Ingrese los elementos del arreglo:");
            for (int i = 0; i < tam; i++) {

                array[i] = teclado.nextInt();
            }

            System.out.println("Elementos del arreglo son:");
            for (int i = 0; i < tam; i++) {
                System.out.print(array[i] + " ");
            }


        }
    }
}
