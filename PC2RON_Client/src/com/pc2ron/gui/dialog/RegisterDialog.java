/**
 *
 * @author mehdi
 */
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.dialog;

import com.pc2ron.interfaces.IPlayer;
import com.pc2ron.game.*;

/**
 *
 * @author mehdi
 */
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class RegisterDialog extends JDialog {
    private IPlayer player = new Player();

    // Labels pour l'adresse et le port du serveur
    private JTextField nameField;
    private JColorChooser colorChooser = new JColorChooser();  

    /**
     * Constructeur
     * @param parent
     * @param title
     * @param modal
     */
    public RegisterDialog(JFrame parent, String title, boolean modal) {
        super(parent, title, modal);
        this.setMinimumSize(new Dimension(450, 150));
        //this.setSize(550, 500);
        this.setLocationRelativeTo(null);
        this.setResizable(false);
        this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
        this.initComponent();
    }


    public IPlayer showDialog(){
        this.setVisible(true);		
        return this.player;		
    }

    /**
     * Initialise le contenu de la boîte
     */
    private void initComponent(){
        /*
         * Zone d'inscription 
         */
        JPanel registerPanel = new JPanel();
        registerPanel.setBackground(Color.white);
        registerPanel.setMinimumSize(new Dimension(220, 60));
        registerPanel.setBorder(BorderFactory.createTitledBorder("Inscription"));
        registerPanel.setLayout(new GridLayout(2, 2));
        
        // Nom
        nameField = new JTextField();
        nameField.setSize(new Dimension(1, 1));
        
        registerPanel.add(new JLabel("Votre pseudo: "));
        registerPanel.add(nameField);

        // Couleur
        registerPanel.add(new JLabel("Votre couleur: "));
        JButton colorButton = new JButton("Choisir une couleur");
        colorButton.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0) {
                JOptionPane.showMessageDialog(null,colorChooser);
                player.setRGB(colorChooser.getColor());
            }			
        });
        
        registerPanel.add(colorButton);
        
        //JOptionPane.showMessageDialog(null,colorChooser);  
        System.out.println(colorChooser.getColor()); 
        
        /**
         * Zone de controle (Ok ou Annuler)
         */
        JPanel controlPanel = new JPanel();
        JButton okButton = new JButton("OK");

        okButton.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0) {				
                player.setName(nameField.getText());
                player.setRGB(colorChooser.getColor());
                
                setVisible(false);
            }			
        });

        JButton cancelButton = new JButton("Annuler");
        cancelButton.addActionListener(new ActionListener() {
        @Override
            public void actionPerformed(ActionEvent arg0) {
                setVisible(false);
            }			
        });

        controlPanel.add(okButton);
        controlPanel.add(cancelButton);

        this.getContentPane().add(registerPanel, BorderLayout.CENTER);
        this.getContentPane().add(controlPanel, BorderLayout.SOUTH);
    }
}
