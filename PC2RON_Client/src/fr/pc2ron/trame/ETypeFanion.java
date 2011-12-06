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
}
