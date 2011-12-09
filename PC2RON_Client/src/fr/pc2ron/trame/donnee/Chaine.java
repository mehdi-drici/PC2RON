package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IChaine;
import fr.pc2ron.interfaces.IVisiteur;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Chaine implements IChaine {
	private short nbOctets;
	private String chaine;
	
	public Chaine() {
		this.chaine = null;
		this.nbOctets = 0;
	}
	
	public Chaine(String chaine) {
		this.chaine = chaine;
		this.nbOctets = (short) chaine.getBytes().length;
	}
	
	public Chaine(short nbCaracteres) {
		this.nbOctets = nbCaracteres;
		this.chaine = new String();
	}
	
	@Override
	public String getChaine() {
		return chaine;
	}
	
        @Override
	public String toString() {
            String s = "";

            try {
                byte[] octets = this.getChaine().getBytes(CHARSET);
                s = ETypeDonnee.CHAINE.getStringType() + " \"";
                short octetNonSigne;

                for(int i=0; i < octets.length; i++) {
                    octetNonSigne = (short) (octets[i] & 0xff);

                    if(octets[i] < 32 || octets[i] > 127) {
                        s += "\\x" + Integer.toHexString(octetNonSigne).toUpperCase(); 
                    } else {
                       s += (char) (octetNonSigne); 
                    }
                }

                s += "\"";
            } catch (UnsupportedEncodingException ex) {
                Logger.getLogger(Chaine.class.getName()).log(Level.SEVERE, null, ex);
            }

            return s;
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
