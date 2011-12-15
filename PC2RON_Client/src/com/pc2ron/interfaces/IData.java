package com.pc2ron.interfaces;

// @todo: revoir la conversion en Bytes
//        creer un visiteur s'occupant d'envoyer des donnees 
//		  et de les convertir en bytes a la volee.

/**
 * Interface representant une donnee generique
 * @author Mehdi Drici
 */
public interface IData extends IVisitable {
	public String toString();
}
