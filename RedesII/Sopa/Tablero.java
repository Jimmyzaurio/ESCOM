// Examen primer parcial 
// Redes II
// Autor: Jesus Saucedo Perez
import java.io.*;
import java.util.*;

public class Tablero implements Serializable{
	final int TAM = 16;
	final int HORIZONTAL = 0;
	final int VERTICAL = 1;
	final int DIAG45 = 2;
	final int DIAG135 = 3;
	char[][] matriz;
	int ayuda;
	boolean es_ganador;
	ArrayList<String> sopa;
	ArrayList<String> respuesta;

	public Tablero() {
		Palabra pal = new Palabra();
		Set<String> aux = pal.damePalabras();
		respuesta = new ArrayList<String>();
		sopa = new ArrayList<String>();
		ayuda = 0;

		matriz = new char[TAM][TAM];
		for (int i = 0; i < TAM; i++)
			for (int j = 0; j < TAM; j++)
				matriz[i][j] = '#';
		
		int pos = 1;	
		for (String s : aux) {
			boolean colocada = false;
			pos = (pos+1)%4;
			switch (pos) {
				case HORIZONTAL:
					for (int i = 0; i < TAM && !colocada; ++i) {
						for (int j = 0; j < TAM - s.length() && !colocada; ++j) {
							if (matriz[i][j] == '#' || matriz[i][j] == s.charAt(0)) {
								boolean flag = true;
								for (int k = 0; k < s.length(); ++k)
									if (matriz[i][j + k] != '#' && 
										matriz[i][j + k] != s.charAt(k)) flag = false;
								
								if (!flag) continue; // No se puede colocar la palabra
								colocada = true;
								for (int k = 0; k < s.length(); ++k)
									matriz[i][j + k] = s.charAt(k);
							}
						}
					}
				break;

				case VERTICAL:
					for (int j = 0; j < TAM && !colocada; ++j) {
						for (int i = 0; i < TAM - s.length() && !colocada; ++i) {
							if (matriz[i][j] == '#' || matriz[i][j] == s.charAt(0)) {
								boolean flag = true;
								for (int k = 0; k < s.length(); ++k)
									if (matriz[i + k][j] != '#' &&
										matriz[i + k][j] != s.charAt(k)) flag = false;

								if (!flag) continue;
								colocada = true;
								for (int k = 0; k < s.length(); ++k)
									matriz[i + k][j] = s.charAt(k);
							}
						}
					}
				break;

				case DIAG135:
					for (int i = 0; i < TAM - s.length() && !colocada; ++i) {
						for (int j = 0; j < TAM - s.length() && !colocada; ++j) {
							if (matriz[i][j] == '#' || matriz[i][j] == s.charAt(0)) {
								boolean flag = true;
								for (int k = 0; k < s.length(); ++k)
									if (matriz[i + k][j + k] != '#' &&
										matriz[i + k][j + k] != s.charAt(k)) flag = false;

								if (!flag) continue;
								colocada = true;
								for (int k = 0; k < s.length(); ++k)
									matriz[i + k][j + k] = s.charAt(k);
							}
						}
					}
				break;

				case DIAG45:
					for (int i = TAM - 1; i >= s.length() - 1 && !colocada; --i) {
						for (int j = 0; j < TAM - s.length() && !colocada; ++j) {
							if (matriz[i][j] == '#' || matriz[i][j] == s.charAt(0)) {
								boolean flag = true;										
								for (int k = 0; k < s.length(); ++k) 
									if (matriz[i - k][j + k] != '#' &&
										matriz[i - k][j + k] != s.charAt(k)) flag = false;

								if (!flag) continue;
								colocada = true;
								for (int k = 0; k < s.length(); ++k)
									matriz[i - k][j + k] = s.charAt(k);									
							}
						}
					}
				break;
			}	
			if (colocada) respuesta.add(s);
		}		

		for (String s : respuesta) {
			char[] temp = s.toCharArray();
			Arrays.sort(temp);
			sopa.add(new String(temp));
		}

		Random ra = new Random();
		for (int i = 0; i < TAM; i++)
			for (int j = 0; j < TAM; j++)
				if (matriz[i][j] == '#')
					matriz[i][j] = (char)(ra.nextInt(26) + 'A');		
	}

	public void setAyuda(int n) {
		ayuda += n;
	}
}
