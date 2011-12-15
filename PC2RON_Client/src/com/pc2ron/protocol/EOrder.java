package com.pc2ron.protocol;

public enum EOrder {
	DROIT(1, "idle"),
	GAUCHE(2, "left"),
	DROITE(3, "right"),
	ABANDON(4, "abandon");
	
	private final int ordre;
	private final String sOrdre;
	
	EOrder(int ordre, String sOrdre) {
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
