package fr.pc2ron.trame;

public enum ETypeFanion {
	TrameNormale (0xFF),
	TrameSpeciale(0x00);
	
	private final short type;
	
	ETypeFanion(int type) {
		this.type = (short) type;
	}
	
	public short getType() {
		return type;
	}
        
        public static ETypeFanion getTypeFanion(byte type) {
            short typeNonSigne = (short) (type & 0xff);
            
            ETypeFanion eTypes[] = ETypeFanion.values();
            ETypeFanion eType = null;

            for(ETypeFanion typeCourant : eTypes) {
                if(typeCourant.getType() == typeNonSigne) {
                    eType = typeCourant;
                }
            }

            return eType;
        }
}
