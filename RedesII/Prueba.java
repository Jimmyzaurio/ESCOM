import java.io.*;
import java.util.*;

public class Prueba {
	public static void main(String[] args) {
		/* Archivo.java 
		long inicio = new Date().getTime();		
		long fin = new Date().getTime() + 2000;
		Jugador j = new Jugador("Juan", fin - inicio);

		Archivo a = new Archivo();
		if (a.actualizaMarcador(j))
			System.out.println("Exito");
		else
			System.out.println("Error");

		ArrayList<Jugador> lista = a.leeMarcador();
		for (Jugador temp : lista)
			System.out.println(temp.toString());
		*/

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));		
		int dificultad = 1;
		String nombre = "";
		
		while (true) {
			try {
				nombre = br.readLine();
				dificultad = Integer.parseInt(br.readLine());
			} catch(Exception ex) {

			}

			Tablero t = new Tablero();
			long inicio = new Date().getTime();				
			if (dificultad == 1)
				t.setAyuda(10000);		

			for (;;) {
				int conta = 0;
				String intento = "";

				System.out.println("\nFaltan: " + t.sopa.size() + "\n");
				for (int i = 0; i < 16; ++i) {
					for (int j = 0; j < 16; ++j) 
						System.out.print(t.matriz[i][j] + " ");

					if (conta < t.sopa.size() && conta < t.ayuda)
						System.out.print("\t" + t.sopa.get(conta++));			

					System.out.println();
					System.out.printf("%40s", " ");

					if (conta < t.sopa.size() && conta < t.ayuda)
						System.out.print(t.sopa.get(conta++));

					System.out.println();
				}

				try {
					intento = br.readLine();
				} catch(Exception ex) {

				}

				intento = intento.toUpperCase();
				if (t.respuesta.contains(intento)) {
					t.respuesta.remove(intento);
					char[] temp = intento.toCharArray();
					Arrays.sort(temp);
					t.sopa.remove(new String(temp));				
				} else {
					t.ayuda++;
				}

				if (t.respuesta.size() == 0) {
					System.out.println("Ganador");			
					long fin = new Date().getTime();
					Archivo arc = new Archivo();
					if (arc.actualizaMarcador(new Jugador(nombre, fin - inicio)))
						System.out.println("Guardado");
					else
						System.out.println("Error");

					ArrayList<Jugador> lista = arc.leeMarcador();
					for (Jugador temp : lista)
						System.out.println(temp.toString());
					break;
				}
			}
			// Quieres volver a jugar?
			System.out.println("Quieres volver a jugar?");
			String resp = "";
			try {
				resp = br.readLine();
			} catch(Exception ex) {

			}
			if (resp.charAt(0) != 'S' && resp.charAt(0) != 's')
				break;
		}
	}
}
