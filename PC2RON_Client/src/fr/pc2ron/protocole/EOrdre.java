package fr.pc2ron.protocole;

public enum EOrdre {
	DROIT(1, "idle"),
	GAUCHE(2, "left"),
	DROITE(3, "right"),
	ABANDON(4, "abandon");
	
	private final int ordre;
	private final String sOrdre;
	
	EOrdre(int ordre, String sOrdre) {
		this.ordre = ordre;
		this.sOrdre = sOrdre;
	}
	
	public int getOrdre() {
		return ordre;
	}
	
	public String getStringOrdre() {
		return sOrdre;
	}
}
