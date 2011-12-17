package com.pc2ron.frame.data;

/**
 * Les differents types de donnee et leur representation 
 * en chaine de caracteres conformement a la couche de transport 
 * definie par PC2RON
 * @author Mehdi Drici
 */
public enum EDataType {
    INT8(0x01, 1, "int8"), 
    INT16(0x02, 2, "int16"),
    INT32(0x04, 4, "int32"),

    UINT8(0x11, 1, "uint8"),
    UINT16(0x12, 2, "uint16"),
    UINT32(0x14, 4, "uint32"),

    STRING(0x20, "string"),
    DOUBLE(0x30, 8, "double");

    private final byte type;
    private final int size;
    private final String typeString;

    EDataType(int type) {
        this.type = (byte) type;
        this.size = 0;
        this.typeString = "";
    }

    EDataType(int type, int size) {
        this.type = (byte) type;
        this.size = size;
        this.typeString = "";
    }

    EDataType(int type, String typeString) {
        this.type = (byte) type;
        this.size = 0;
        this.typeString = typeString;
    }

    EDataType(int type, int size, String typeString) {
        this.type = (byte) type;
        this.size = size;
        this.typeString = typeString;
    }

    public byte getType() {
        return this.type;
    }

    public int getSize() {
        return size;
    }

    public String getTypeString() {
        return typeString;
    }
    
    /**
     * Traitement effectue par un visiteur et relatif a la donnee courante
     * @param <Data>
     * @param <Result>
     * @param visitor Visiteur s'occupant du traitement
     * @param data Donnee a traiter
     * @return 
     */
    public static EDataType getDataType(short type) {
        EDataType eTypes[] = EDataType.values();
        EDataType result = null;
        
        for(EDataType typeCourant : eTypes) {
            if(typeCourant.getType() == type) {
                result = typeCourant;
            }
        }
        
        return result;
    }
}
