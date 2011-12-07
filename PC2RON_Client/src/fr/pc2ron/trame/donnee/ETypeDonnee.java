package fr.pc2ron.trame.donnee;

public enum ETypeDonnee {
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
	
	ETypeDonnee(int type) {
		this.type = (byte) type;
		this.taille = 0;
		this.sType = "";
	}
	
	ETypeDonnee(int type, int taille) {
		this.type = (byte) type;
		this.taille = taille;
		this.sType = "";
	}
	
	ETypeDonnee(int type, String sType) {
		this.type = (byte) type;
		this.taille = 0;
		this.sType = sType;
	}
	
	ETypeDonnee(int type, int taille, String sType) {
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
    
    public static ETypeDonnee getTypeDonnee(byte type) {
        ETypeDonnee eTypes[] = ETypeDonnee.values();
        ETypeDonnee eType = null;
        
        for(ETypeDonnee typeCourant : eTypes) {
            if(typeCourant.getType() == type) {
                eType = typeCourant;
            }
        }
        
        return eType;
    }
}
