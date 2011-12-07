package fr.pc2ron.trame;

public enum ETypeFanion {
	TrameNormale (0xFF),
	TrameSpeciale(0x00);
	
	private final int type;
	
	ETypeFanion(int type) {
		this.type = type;
	}
	
	public short getType() {
		return (short)this.type;
	}
        
        public static ETypeFanion getTypeFanion(byte type) {
            ETypeFanion eTypes[] = ETypeFanion.values();
            ETypeFanion eType = null;

            for(ETypeFanion typeCourant : eTypes) {
                if(typeCourant.getType() == type) {
                    eType = typeCourant;
                }
            }

            return eType;
        }
}
