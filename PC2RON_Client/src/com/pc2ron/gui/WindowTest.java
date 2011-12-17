package com.pc2ron.gui;

import com.pc2ron.interfaces.*;
import com.pc2ron.protocol.Protocol;
import java.awt.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;

/**
 *
 * @author mehdi
 */
public class WindowTest extends JFrame {
    // Instance du protocole
    private IProtocol protocol = Protocol.getInstance();
    
    // Grille de jeu
    private GridPanel gridPanel;
    
    // Zone des messages du serveur (Pause, Start, Death, Win)
    private JTextArea msgTextArea;
    
    // Zone de connexion et d'inscription au serveur
    public JButton connectButton = new JButton("Connect");
    public JButton registerButton = new JButton("Register");
    
    public WindowTest(){
        this.setTitle("PC2RON Game");
        this.setMinimumSize(new Dimension(700, 500));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
         
        this.initComponents();
        this.addKeyListener(gridPanel);
        
        // On cache le bouton d'inscription par defaut
        this.registerButton.setVisible(false);
        
        this.setFocusable(true);        
        this.setVisible(true);
        
        for(;;) {
            try {
                Thread.sleep(2);
                this.gridPanel.updatePositions();
                this.gridPanel.repaint();
            } catch (InterruptedException ex) {
                Logger.getLogger(WindowTest.class.getName()).log(Level.SEVERE, null, ex);
            }
            
        }
    }
    
    private void initComponents() {
        // Grille de jeu
        JPanel panel = new JPanel();
        gridPanel = new GridPanel();
        gridPanel.setPreferredSize(new Dimension(680, 350));
        //gridPanel.setBackground(Color.red);
        panel.add(gridPanel);
        
        // Zone des messages du serveur
        msgTextArea = new JTextArea();
        msgTextArea.setText("Test");
        msgTextArea.append("\nTOTO");
        msgTextArea.setPreferredSize(new Dimension(700, 100));
        msgTextArea.setEditable(false);
        
        JScrollPane scrollPane = new JScrollPane(msgTextArea,
                                        JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
                                        JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        
        // Zone des boutons de connexion et inscription
        JPanel controlPanel = new JPanel();
        controlPanel.setBackground(Color.lightGray);
        controlPanel.setPreferredSize(new Dimension(500, 50));
        controlPanel.setLayout(new FlowLayout());
        controlPanel.add(connectButton, FlowLayout.LEFT);
        controlPanel.add(registerButton, FlowLayout.CENTER);
        
        // Ajout des composants a la frame
        this.getContentPane().add(panel, BorderLayout.NORTH);
        this.getContentPane().add(scrollPane, BorderLayout.CENTER);
        this.getContentPane().add(controlPanel, BorderLayout.SOUTH);
    }
  
    public static void main(String[] args){
        new WindowTest();
    }
}