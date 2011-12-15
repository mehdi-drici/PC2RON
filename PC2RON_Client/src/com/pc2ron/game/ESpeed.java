package com.pc2ron.game;

/**
 * Vitesses possibles d'un joueur
 * Elles correspondent au nombre de pas par centieme de seconde
 * @author Mehdi Drici
 */
public enum ESpeed {
    SLOW(1),
    NORMAL(3),
    SPEED(5),
    TURBO(7);

    private final int speed;

    ESpeed(int speed) {
        this.speed = speed;
    }

    public int getSpeed() {
        return speed;
    }
    
    public static ESpeed getESpeed(int speed) {
        ESpeed eSpeeds[] = ESpeed.values();
        ESpeed result = null;

        for(ESpeed currentSpeed : eSpeeds) {
            if(currentSpeed.getSpeed() == speed) {
                result = currentSpeed;
            }
        }

        return result;
    }
}
