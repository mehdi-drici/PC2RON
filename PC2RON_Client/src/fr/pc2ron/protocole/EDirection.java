package fr.pc2ron.protocole;

public enum EDirection {
	HAUT(1),
	BAS(2),
	GAUCHE(3),
	DROITE(4);
	
	private final int direction;
	
	EDirection(int direction) {
		this.direction = direction;
	}
	
	public int getDirection() {
		return direction;
	}
}
