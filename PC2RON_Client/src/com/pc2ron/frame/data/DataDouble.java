package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IDataDouble;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un flottant en double precision conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataDouble implements IDataDouble {
    private double flottant;

    public DataDouble() {
        flottant = 0.0;
    }

    public DataDouble(double flottant) {
        this.flottant = flottant;
    }

    @Override
    public double getDouble() {
        return flottant;
    }
    
    @Override
    public String toString() {
        return EDataType.DOUBLE.getTypeString() + " " + getDouble();
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
