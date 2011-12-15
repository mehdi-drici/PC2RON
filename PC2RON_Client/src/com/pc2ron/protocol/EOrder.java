package com.pc2ron.protocol;

/**
 * Les differents ordres d'un joueur
 * @author Mehdi Drici
 */
public enum EOrder {
    STRAIGHT(1, "idle"),
    LEFT(2, "left"),
    RIGHT(3, "right"),
    ABORT(4, "abandon");

    private final int order;
    private final String stringOrder;

    EOrder(int order, String stringOrder) {
        this.order = order;
        this.stringOrder = stringOrder;
    }

    public int getOrder() {
        return this.order;
    }

    public String getStringOrder() {
        return stringOrder;
    }
}
