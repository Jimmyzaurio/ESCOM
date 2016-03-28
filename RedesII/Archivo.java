import java.io.*;
import java.util.*;

public class Archivo {
	String nombre;
	
	ArrayList<Jugador> leeMarcador() {
		ArrayList<Jugador> lista = new ArrayList();
		try {
			File f = new File("puntuacion.in");
			if (f.createNewFile()) // Crea el archivo si no existe y retorna true
				System.out.println("Creamos el archivo.");

			FileInputStream fin = new FileInputStream("puntuacion.in");
			ObjectInputStream ois = new ObjectInputStream(fin);			
			lista = (ArrayList<Jugador>)ois.readObject();
			ois.close();

			return lista;
		} catch(Exception ex) {
			System.out.println("Algo salio mal en leeMarcador");
			//ex.printStackTrace();
			return lista;
		}
	}

	boolean actualizaMarcador(Jugador j) {
		ArrayList<Jugador> lista = leeMarcador();
		lista.add(j);
		Collections.sort(lista);

		try {
			FileOutputStream fout = new FileOutputStream("puntuacion.in");
			ObjectOutputStream oos = new ObjectOutputStream(fout);
			oos.writeObject(lista);
			oos.close();
		} catch(Exception ex) {
			//ex.printStackTrace();
			System.out.println("Algo salio mal en actualizaMarcador");
			return false;
		}
		return true;
	}
}
