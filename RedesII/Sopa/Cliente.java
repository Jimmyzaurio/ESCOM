import java.io.*;
import java.net.*;
import java.util.*;

public class Cliente {
	public static void main(String[] args) {
		// Nos conectamos al servidor
		try {
			String host = "localhost";
			int puerto = 7000;
			Socket cl = new Socket(host, puerto);
			
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			ObjectOutputStream oos = new ObjectOutputStream(cl.getOutputStream());
			ObjectInputStream  ois = new ObjectInputStream(cl.getInputStream());
			
			for (;;) {			
				System.out.println((String) ois.readObject());
				String nombre = br.readLine();
				oos.writeObject(nombre);
				oos.flush();
			
				System.out.println((String) ois.readObject());
				int dificultad = Integer.parseInt(br.readLine());
				oos.writeObject(dificultad);
				oos.flush();
				
				Tablero t = (Tablero) ois.readObject(); // Recibimos el tablero			
				for (;;) { // intentos infinitos			
					/* datos del juego */
					System.out.println("\nFaltan: " + t.sopa.size() + "\n");
					int conta = 0;
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
					/* fin datos del juego */
				
					String intento = "";
					intento = br.readLine();
					intento = intento.toUpperCase();
					if (t.respuesta.contains(intento)) {
						t.respuesta.remove(intento);
						char[] temp = intento.toCharArray();
						Arrays.sort(temp);
						t.sopa.remove(new String(temp));				
					} else {
						t.ayuda++;
					}
				
					boolean fin_juego = t.respuesta.size() == 0 ? true : false;
					if (fin_juego) break;
				}
				oos.writeObject(true);
				
				System.out.println((String) ois.readObject());
				String resp = br.readLine();
				oos.writeObject(resp);
				oos.flush();
			}
		} catch(Exception ex) {
		
		}
	}
}
