package fr.pc2ron.interfaces;

import fr.pc2ron.protocole.EOrdre;

public interface ITrameBuilder {
	public ITrame creerTrameInit();
	public ITrame creerTrameConnect(short r, short v, short b, String nom);
	public ITrame creerTrameOrder(EOrdre ordre);
}
