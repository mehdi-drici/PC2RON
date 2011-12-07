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

//	@Override
//	// @todo A revoir
//	public void setValeur(DataInput in) {
//		byte[] buffer = new byte[nbOctets];
//		
//		try {
//			in.readFully(buffer, 0, nbOctets);
//			chaine = new String(buffer, Charset.forName(CHARSET));
//			nbOctets = (short) chaine.length();
//		} catch (IOException e1) {
//			e1.printStackTrace();
//		}
//	}

	/*@Override
	public byte[] toBytes() {
		byte[] tab = null;
		
		
		try {
			tab = chaine.getBytes(CHARSET);
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		
		return tab;
	}*/
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		//debug
		String s = "";
		try {
			s = new String(chaine.getBytes(), "UTF-8");
			
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		System.out.println("chaine non encodee  : " + chaine);
		System.out.println("chaine encodee UTF-8 : " + s);
		System.out.println("Taille chaine : " + chaine.getBytes().length);
		System.out.println("Taille chaine encodee : " + s.getBytes().length);
		//debug
		
		ArrayList<Byte> tab=new ArrayList<Byte>();
		byte[] tab1 = null;
		try {
			tab1 = chaine.getBytes(CHARSET);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// Entete
		nbOctets = (short) tab1.length;
		tab.add(ETypeDonnee.CHAINE.getType());
		tab.add((byte) (nbOctets >>> 8));
		tab.add((byte) (nbOctets));
		
		// Valeur
		for(int i=0;i<tab1.length;i++){
			tab.add(tab1[i]);
		}
		
		
		return tab;
	}
	*/
//	@Override
//	public int taille() {
//		return ETypeDonnee.CHAINE.getTaille() + nbOctets + 3;
//	}
	
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
