package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IDataUint8;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un entier non signe sur 8 bits conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataUint8 implements IDataUint8 {
    private short entier;

    public DataUint8() {
        entier = 0;
    }

    public DataUint8(short entier) {
        this.entier = (short) (entier & 0xff);
    }

    @Override
    public short getValue() {
        return entier;
    }

    @Override
    public String toString() {
        return EDataType.ENTIER_NON_SIGNE1.getStringType() + " " + getValue();
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
    public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
        return visiteur.visit(this, donnees);
    }
}
