package com.pc2ron.frame.data;

import java.io.UnsupportedEncodingException;

import com.pc2ron.interfaces.IDataString;
import com.pc2ron.interfaces.IVisitor;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Representation d'une chaine de caracteres conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataString implements IDataString {
    private short nbOctets;
    private String chaine;

    public DataString() {
            this.chaine = null;
            this.nbOctets = 0;
    }

    public DataString(String chaine) {
            this.chaine = chaine;
            this.nbOctets = (short) chaine.getBytes().length;
    }

    public DataString(short nbCaracteres) {
            this.nbOctets = nbCaracteres;
            this.chaine = new String();
    }

    @Override
    public String getContent() {
            return chaine;
    }
	
    @Override
    public String toString() {
        String s = "";

        try {
            byte[] octets = this.getContent().getBytes(CHARSET);
            s = EDataType.STRING.getTypeString() + " \"";
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
            Logger.getLogger(DataString.class.getName()).log(Level.SEVERE, null, ex);
        }

        return s;
    }
    
    /**
     * Traitement effectue par un visiteur et relatif a la donnee courante
     * @param <Data>
     * @param <Result>
     * @param visitor Visiteur s'occupant du traitement
     * @param data Donnee a traiter
     * @return 
     */
    @Override
    public <Data, Result> Result accept(IVisitor<Data, Result> visitor, Data data) {
        return visitor.visit(this, data);
    }
}
