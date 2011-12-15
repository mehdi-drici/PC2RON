package com.pc2ron.frame.data;

/**
 * Les differents types de donnee et leur representation 
 * en chaine de caracteres conformement a la couche de transport 
 * definie par PC2RON
 * @author Mehdi Drici
 */
public enum EDataType {
    ENTIER_SIGNE1(0x01, 1, "int8"), 
    ENTIER_SIGNE2(0x02, 2, "int16"),
    ENTIER_SIGNE4(0x04, 4, "int32"),

    ENTIER_NON_SIGNE1(0x11, 1, "uint8"),
    ENTIER_NON_SIGNE2(0x12, 2, "uint16"),
    ENTIER_NON_SIGNE4(0x14, 4, "uint32"),

    CHAINE(0x20, "string"),
    FLOTTANT(0x30, 8, "double");

    private final byte type;
    private final int taille;
    private final String sType;

    EDataType(int type) {
        this.type = (byte) type;
        this.taille = 0;
        this.sType = "";
    }

    EDataType(int type, int taille) {
        this.type = (byte) type;
        this.taille = taille;
        this.sType = "";
    }

    EDataType(int type, String sType) {
        this.type = (byte) type;
        this.taille = 0;
        this.sType = sType;
    }

    EDataType(int type, int taille, String sType) {
        this.type = (byte) type;
        this.taille = taille;
        this.sType = sType;
    }

    public byte getType() {
        return this.type;
    }

    public int getTaille() {
        return taille;
    }

    public String getStringType() {
        return sType;
    }
    
    /**
     * Traitement effectue par un visiteur et relatif a la donnee courante
     * @param <Data>
     * @param <Result>
     * @param visitor Visiteur s'occupant du traitement
     * @param data Donnee a traiter
     * @return 
     */
    public static EDataType getTypeDonnee(short type) {
        EDataType eTypes[] = EDataType.values();
        EDataType eType = null;
        
        for(EDataType typeCourant : eTypes) {
            if(typeCourant.getType() == type) {
                eType = typeCourant;
            }
        }
        
        return eType;
    }
}
