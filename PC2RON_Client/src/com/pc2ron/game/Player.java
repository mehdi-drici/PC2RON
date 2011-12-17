package com.pc2ron.game;

import com.pc2ron.interfaces.IPlayer;
import java.awt.*;
import java.util.ArrayList;

/**
 * Representation d'un joueur avec les caracteristiques telles que
 * definies dans le protocole PC2RON
 * @author Mehdi Drici
 */
public class Player implements IPlayer {
    //Identifiant unique
    private int id;
    
    // Nom du joueur
    private String name;
    
    // Couleur au format RGB
    private Color color;
    
    // Ensemble des positions du joueurs
    private ArrayList<Point> positions;
    
    // Direction du joueur
    private EDirection dir;
    
    // Vitesse du joueur
    private ESpeed speed;
    
    // Score du joueur
    private int score;
    
    public Player() {
        this.color = new Color(0);
        this.positions = new ArrayList<Point>();
        this.name = "No name";
        this.dir = EDirection.RIGHT;
        this.speed = ESpeed.NORMAL;
        this.score = 0;
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
    public Color getRGB() {
        return this.color;
    }

    @Override
    public ArrayList<Point> getPositions() {
        return this.positions;
    }
    
    @Override
    public Point getLastPosition() {
        if(this.positions.isEmpty()) {
            return null;
        } else {
            return positions.get(positions.size() - 1);
        }
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
    public void setRGB(Color color) {
        this.color = color;
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
    public void setDir(EDirection dir) {
        this.dir = dir;
    }

    @Override
    public void setSpeed(ESpeed speed) {
        this.speed = speed;
    }
    
    /* Les deplacements d'un joueur 
     * @todo mettre a jour le score du joueur
     *       et prendre en compte la vitesse du joueur
     */
    
    /**
     * Le joueur descend
     * Seule la derniere ordonnee est changee
     */
    @Override
    public void goDown() {
        Point newPosition = new Point(getLastPosition());
        
        newPosition.y++;
        this.positions.add(newPosition);
    }
    
    /**
     * Le joueur monte
     * Seule la derniere ordonnee est changee
     */
    @Override
    public void goUp() {
        Point newPosition = new Point(getLastPosition());
        
        newPosition.y--;
        this.positions.add(newPosition);
    }
    
    /**
     * Le joueur tourne a gauche
     * Seule la derniere abscisse est changee
     */
    @Override
    public void goLeft() {
        Point newPosition = new Point(getLastPosition());
        
        newPosition.x--;
        this.positions.add(newPosition);
    }
    
    /**
     * Le joueur tourne a droite
     * Seule la derniere abscisse est changee
     */
    @Override
    public void goRight() {
        Point newPosition = new Point(getLastPosition());
        
        newPosition.x++;
        this.positions.add(newPosition);
    }
    
    @Override
    public String toString() {
        String playerString = "";
        
        playerString += "Nom: " + getName() + "\n";
        playerString += "Id: " + getId() + "\n";
        playerString += "Position: " + getLastPosition().x + "\n";
        playerString += "Couleur: " + getRGB().toString() + "\n";
        
        return playerString;
    }
}

