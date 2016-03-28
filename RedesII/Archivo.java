import java.io.*;
import java.util.*;

public class Archivo {	
	ArrayList<Jugador> leeMarcador() {
		ArrayList<Jugador> lista = new ArrayList<Jugador>();
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

	String[] leeLista() {
		ArrayList<String> temp = new ArrayList<String>();
		String[] lista = null;
		try {
			File fin = new File("lista.txt");
			FileInputStream fis = new FileInputStream(fin);

			BufferedReader br = new BufferedReader(new InputStreamReader(fis));

			String line = null;
			while ((line = br.readLine()) != null) {
				temp.add(line);
			}
			lista = new String[temp.size()];
			lista = temp.toArray(lista);
			return lista;
		} catch(Exception ex) {
			System.out.println("Algo salio mal en leeLista");
			//ex.printStackTrace();
			return lista;
		}
	}
}
