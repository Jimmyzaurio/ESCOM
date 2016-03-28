import java.io.*;
import java.util.*;

public class Jugador implements Comparable<Jugador>, Serializable{
	String nombre;
	long tiempo;

	public Jugador(String nombre, long tiempo) {
		this.nombre = nombre;
		this.tiempo = tiempo;
	}

	String getNombre() {
		return nombre;
	}

	long getTiempo() {
		return tiempo;
	}

	public String toString() {
		return this.nombre + "\t" + this.tiempo/1000 + "s";
	}

	public int compareTo(Jugador j) {
		// orden ascendente
		return (int)(this.tiempo - j.tiempo)/1000;
	}
}
