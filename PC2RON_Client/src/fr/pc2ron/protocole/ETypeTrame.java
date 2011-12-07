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
	
	private final byte type;
	
	ETypeTrame(int type) {
		this.type = (byte) type;
	}
	
	public byte getType() {
		return this.type;
	}
        
        public static ETypeTrame getTypeTrame(byte type) {
            ETypeTrame eTypes[] = ETypeTrame.values();
            ETypeTrame eType = null;

            for(ETypeTrame typeCourant : eTypes) {
                if(typeCourant.getType() == type) {
                    eType = typeCourant;
                }
            }

            return eType;
        }
}