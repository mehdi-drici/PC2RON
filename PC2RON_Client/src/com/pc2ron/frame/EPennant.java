package com.pc2ron.frame;

/**
 * Les differents type de fanion
 * - Fanion normal
 * - Fanion pour trame speciale (fin de transmission)
 * @author Mehdi Drici
 */
public enum EPennant {
	NormalFrame (0xFF),
	SpecialFrame(0x00);
	
	private final short type;
	
	EPennant(int type) {
            this.type = (short) type;
	}
	
        /**
         * Recuperation du fanion
         * @return Le type de fanion au format short
         */
	public short getType() {
		return type;
	}
        
        /**
         * Recuperation du type enumere representant le type en byte
         * @param type Type de fanion au format short
         * @return Le type enumere
         */
        public static EPennant getPennant(short type) {
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
