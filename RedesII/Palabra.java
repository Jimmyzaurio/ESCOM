import java.io.*;
import java.util.*;

public class Palabra {
	String[] A = {"OSO", "COTORRO", "PERICO", "ANA", "RECONOCER","SOMETEMOS", "LUNA", 
	"RODAR", "ORO", "AVE", "MOCOSO", "HADA", "MOTOR", "ROTO", "TROPA", "AMOR", "AROMA", 
	"VENUS", "ALMA", "BROMA", "TUMBAS", "LETRAS", "REDES"};

	Set<String> damePalabras() {
		Random ra = new Random();
		int tam = ra.nextInt(A.length - 9) + 9;

		Set<String> S = new HashSet<String>();
		for (;S.size() < tam;) {
			if (ra.nextInt(2) % 2 == 0)
				S.add( new StringBuilder(A[ra.nextInt(tam)]).
					reverse().toString()
					);
			else
				S.add(A[ra.nextInt(tam)]);
		}
		return S;
	}
}
