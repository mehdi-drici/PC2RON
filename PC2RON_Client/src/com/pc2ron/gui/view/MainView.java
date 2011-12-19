/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.view;

import com.pc2ron.gui.controller.GameController;
import com.pc2ron.gui.model.GraphicalGameModel;
import com.pc2ron.gui.model.DisplayModel;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.KeyListener;
import javax.swing.*;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

/**
 *
 * @author mehdi
 */
public class MainView extends JFrame {
    // Grille de jeu
    private GridView gridView;
    
    // Zone des messages du serveur (Pause, Start, Death, Win)
    //private JTextArea msgTextArea = new JTextArea(4, 20);
    
    // Zone de connexion et d'inscription au serveur
    public JButton connectButton = new JButton("Connect");
    public JButton registerButton = new JButton("Register");
    
    private GraphicalGameModel gameModel;
    private DisplayModel displayModel;
    
    public MainView() {
        this.setTitle("PC2RON Game");
        this.setLayout(new GridBagLayout());
        this.setMinimumSize(new Dimension(700, 700));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        
        // Creation des modeles
        gameModel = new GraphicalGameModel();
        displayModel = new DisplayModel();
        
        // Controlleur
        GameController controller = new GameController();
        controller.setModel(gameModel);
        controller.setModel(displayModel);
        
        makeGUI();
        //gridView.addKeyListener(controller);
        addKeyListener(controller);
        connectButton.addActionListener(controller);
        registerButton.addActionListener(controller);
        
        //setKeyListener(controller);
        //setActionListener(controller);
    }
    
    public void makeGUI() {
        // Zone de jeu
        gridView = new GridView(gameModel);
        //gridView.setFocusable(true);

        // Zone d'affichage des trames du serveur
        DisplayView displayView = new DisplayView(displayModel);
        displayView.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayView,
                                       JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
                                       JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        StyledDocument displayViewStyle = displayView.getStyledDocument();
        SimpleAttributeSet center = new SimpleAttributeSet();
        StyleConstants.setAlignment(center, StyleConstants.ALIGN_CENTER);
        displayViewStyle.setParagraphAttributes(0, displayViewStyle.getLength(), 
                                                center, false);
        
        // Zone des boutons de connexion et inscription
        JPanel controlPanel = new JPanel();
        controlPanel.setBackground(Color.lightGray);
        
        controlPanel.add(connectButton);
        controlPanel.add(registerButton);
        registerButton.setFocusable(false);
        connectButton.setFocusable(false);
        
        // Ajout des composants a la frame
        this.getContentPane().add(gridView, new GBC(0, 0).
               setFill(GBC.BOTH).setInsets(10).setIpad(500, 500).setInsets(10));
        
        this.getContentPane().add(scrollPane, new GBC(0, 1, 2, 1).setFill(GBC.HORIZONTAL).
              setAnchor(GBC.WEST).setIpad(150, 150).setWeight(100, 100).setInsets(10));
        
        this.getContentPane().add(new JTable(), new GBC(1, 0).
                setFill(GBC.VERTICAL).setIpad(100, 100).setInsets(10).setWeight(50, 150));
        
        this.getContentPane().add(controlPanel, new GBC(0, 2, 2, 1).
                                         setIpad(10, 10).setFill(GBC.HORIZONTAL));
        this.pack();
        this.setFocusable(true);
        
        //this.setAlwaysOnTop(true);
        this.setAutoRequestFocus(true);
        
        this.setVisible(true);
    }
    
    public void showError(String errMessage) {
        JOptionPane.showMessageDialog(this, errMessage);
    }
     
    public void setActionListener(ActionListener cal) {
        connectButton.addActionListener(cal);
        registerButton.addActionListener(cal);
    }
    
    public void setKeyListener(KeyListener listener) {
        addKeyListener(listener);
        //gridPanel.setFocusable(true);
        //gridPanel.setVisible(true);
    }
    
    public static void main(String[] args) {
        MainView pc2ronMainWindow = new MainView();
    }
}
