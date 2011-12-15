package com.pc2ron.frame;

public enum EPennant {
	TrameNormale (0xFF),
	TrameSpeciale(0x00);
	
	private final short type;
	
	EPennant(int type) {
		this.type = (short) type;
	}
	
	public short getType() {
		return type;
	}
        
        public static EPennant getTypeFanion(short type) {
            short typeNonSigne = (short) (type & 0xff);
            
            EPennant eTypes[] = EPennant.values();
            EPennant eType = null;

            for(EPennant typeCourant : eTypes) {
                if(typeCourant.getType() == typeNonSigne) {
                    eType = typeCourant;
                }
            }

            return eType;
        }
}
