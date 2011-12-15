package com.pc2ron.interfaces;

import java.io.DataInput;

import com.pc2ron.frame.data.ETypeDonnee;

// @todo: revoir la conversion en Bytes
//        creer un visiteur s'occupant d'envoyer des donnees 
//		  et de les convertir en bytes a la volee.

public interface IData extends IVisitable {
	//public byte getNbOctets();
	//public void setValeur(DataInput in);
	//public int taille();
	public String toString();
	
	/* Decodage pour chaque type de donnees */
	//public IDonnee decoder(Byte[] tabOctets);
}
