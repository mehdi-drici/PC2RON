package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IDataUInt32;
import com.pc2ron.interfaces.IDataInt32;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un entier sur 32 bits conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataInt32 implements IDataInt32 {
    private int entier;

    public DataInt32() {
        entier = 0;
    }

    public DataInt32(int entier) {
        this.entier = entier;
    }

    @Override
    public int getValue() {
        return entier;
    }

    public String toString() {
        return EDataType.ENTIER_SIGNE4.getStringType() + " " + getValue();
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
