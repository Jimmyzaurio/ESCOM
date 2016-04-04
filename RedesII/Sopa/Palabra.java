import java.io.*;
import java.util.*;

public class Palabra {
	String[] a;

	Set<String> damePalabras() {
		Archivo arc = new Archivo();
		a = arc.leeLista();
		Random ra = new Random();		
		int tam = ra.nextInt(14) + 15;

		Set<String> S = new HashSet<String>();
		for (;S.size() < tam;) 
			S.add(a[ra.nextInt(tam)]);		
		return S;
	}
}
