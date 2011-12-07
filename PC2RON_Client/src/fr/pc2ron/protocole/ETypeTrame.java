package fr.pc2ron.protocole;

public enum ETypeTrame {
	TrameInit(0x49),
	TrameConnect(0x43),
	TrameAck(0x41),
	TrameRegistered(0x52),
	TrameUser(0x55),
	TrameFin(0x45),
	TramePause(0x50),
	TrameStart(0x53),
	TrameTurn(0x54),
	TrameDeath(0x44),
	TrameWin(0x57),
	TrameOrder(0x4F);
	
	private final short type;
	
	ETypeTrame(int type) {
            this.type = (short) type;
	}
	
	public short getType() {
            return this.type;
	}
        
        public static ETypeTrame getTypeTrame(byte type) {
            short typeNonSigne = (short) (type & 0xff);
            
            ETypeTrame eTypes[] = ETypeTrame.values();
            ETypeTrame eType = null;

            for(ETypeTrame typeCourant : eTypes) {
                if(typeCourant.getType() == typeNonSigne) {
                    eType = typeCourant;
                }
            }

            return eType;
        }
}