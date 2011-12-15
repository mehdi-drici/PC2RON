package com.pc2ron.game;

/**
 * Directions possibles d'un joueur
 * @author Mehdi Drici
 */
public enum EDirection {
    TOP(1),
    BOTTOM(2),
    LEFT(3),
    RIGHT(4);

    private final int dir;

    EDirection(int dir) {
        this.dir = dir;
    }

    public int getDirection() {
        return dir;
    }

    public static EDirection getEDirection(int dir) {
        EDirection eDirs[] = EDirection.values();
        EDirection result = null;

        for(EDirection currentDir : eDirs) {
            if(currentDir.getDirection() == dir) {
                result = currentDir;
            }
        }

        return result;
    }
}
