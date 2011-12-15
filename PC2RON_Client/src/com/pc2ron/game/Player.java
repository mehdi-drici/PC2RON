package com.pc2ron.game;

import com.pc2ron.interfaces.IPlayer;
import java.awt.Point;

/**
 * Representation d'un joueur avec les caracteristiques telles que
 * definies dans le protocole PC2RON
 * @author Mehdi Drici
 */
public class Player implements IPlayer {
    private int id;
    private String name;
    private int[] color;
    private Point position;
    private EDirection dir;
    private ESpeed speed;
    
    public Player() {
        this.color = new int[3];
        this.position = new Point();
        this.name = "No name";
    }
    
    public Player(int id) {
        this();
        this.id = id;
    }
    
    /* Getters */
    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public int getId() {
        return this.id;
    }

    @Override
    public int[] getRGB() {
        return this.color;
    }

    @Override
    public Point getPosition() {
        return this.position;
    }

    @Override
    public EDirection getDir() {
        return this.dir;
    }

    @Override
    public ESpeed getSpeed() {
        return this.speed;
    }
    
    /* Setters */
    @Override
    public void setRGB(int[] color) {
        this.color[0] = color[0];
        this.color[1] = color[1];
        this.color[2] = color[2];
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }

    @Override
    public void setId(int id) {
        this.id = id;
    }

    @Override
    public void setPosition(Point pt) {
        this.position.setLocation(pt);
    }

    @Override
    public void setDir(EDirection dir) {
        this.setDir(dir);
    }

    @Override
    public void setSpeed(ESpeed speed) {
        this.speed = speed;
    }
    
    @Override
    public String toString() {
        String playerString = "";
        
        playerString += "Nom: " + getName() + "\n";
        playerString += "Id: " + getId() + "\n";
        playerString += "Position: " + getPosition().toString() + "\n";

        return playerString;
    }
}

