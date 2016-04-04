import java.io.*;
import java.net.*;
import java.util.*;

public class Servidor {
	public static void main(String args[]) {
		final int PUERTO = 7000;
		try {			
			ServerSocket server = new ServerSocket(PUERTO);
			System.out.println("Servidor iniciado, esperando jugadores.");
			int dificultad = 1;
			String nombre = "";
			
			for (;;) { // Recibir cliente
				Socket cl = server.accept();
				System.out.println("Cliente conectado");
				ObjectOutputStream oos = new ObjectOutputStream(cl.getOutputStream());
				ObjectInputStream  ois = new ObjectInputStream(cl.getInputStream());
				
				for (;;) { // for repetir juego		
					oos.writeObject(new String("Escribe tu nombre: "));
					oos.flush();
					nombre = (String) ois.readObject();
				
					oos.writeObject(new String("Dificultad: Facil(1) Intermedio(2)"));
					oos.flush();				
					dificultad = (int) ois.readObject();
								
					Tablero t = new Tablero();
					long inicio = new Date().getTime();
					if (dificultad == 1) t.setAyuda(1000);
				
					for (;;) { // Recibir todos los intentos					
						String intento = "";
					
						oos.writeObject(t); // Mandamos el tablero
						oos.flush();
						
						boolean fin_juego = (boolean) ois.readObject();					
						if (fin_juego) {
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
					} // for recibir intentos						
					oos.writeObject(new String("Quieres volver a jugar? [s/S]"));
					oos.flush();				
				
					String resp = (String) ois.readObject();
					if (resp.charAt(0) != 'S' && resp.charAt(0) != 's') break;
				} // fin for repetir juego
				oos.close();
				ois.close();
				cl.close();
			} // for recibir cliente
		} catch(Exception ex) {
		
		}
	}
}
