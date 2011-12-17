/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.dialog;

/**
 *
 * @author mehdi
 */
import com.pc2ron.gui.ConnectInfo;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;



public class ConnectDialog extends JDialog {
    public static final String HOST = "127.0.0.1";
    public static final String PORT = "5555";
    
    private ConnectInfo connectInfo = new ConnectInfo();

    // Labels pour l'adresse et le port du serveur
    private JLabel hostLabel;
    private JLabel portLabel;

    // Champs pour l'adresse et le port du serveur
    private JTextField hostField;
    private JTextField portField;

    /**
     * Constructeur
     * @param parent
     * @param title
     * @param modal
     */
    public ConnectDialog(JFrame parent, String title, boolean modal){
        super(parent, title, modal);
        this.setSize(350, 150);
        this.setLocationRelativeTo(null);
        this.setResizable(false);
        this.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
        this.initComponent();
    }


    public ConnectInfo showDialog(){
        this.setVisible(true);		
        return this.connectInfo;		
    }

    /**
     * Initialise le contenu de la boîte
     */
    private void initComponent(){
        /*
         * Zone de connexion 
         */
        JPanel connectPanel = new JPanel();
        connectPanel.setBackground(Color.white);
        connectPanel.setPreferredSize(new Dimension(220, 60));
        connectPanel.setBorder(BorderFactory.createTitledBorder("Connexion"));
        connectPanel.setLayout(new GridLayout(2, 2));
        
        // Hote
        hostLabel = new JLabel("Host: ");
        hostField = new JTextField(HOST);
        hostField.setPreferredSize(new Dimension(10, 3));
        
        connectPanel.add(hostLabel);
        connectPanel.add(hostField);

        // Port
        portLabel = new JLabel("Port: ");
        portField = new JTextField(PORT);
        portField.setPreferredSize(new Dimension(10, 3));

        connectPanel.add(portLabel);
        connectPanel.add(portField);

        JPanel controlPanel = new JPanel();

        /**
         * Zone de controle (Ok ou Annuler)
         */
        JButton okButton = new JButton("OK");

        okButton.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0) {
                if(hostField.getText().isEmpty()) {
                    JOptionPane.showMessageDialog(null, "Empty host", 
                         "Server connection Config", JOptionPane.ERROR_MESSAGE);
                }
                
                else if(portField.getText().isEmpty()) {
                    JOptionPane.showMessageDialog(null, "Empty port", 
                         "Server connection Config", JOptionPane.ERROR_MESSAGE);
                }
                
                else {
                    try {
                        connectInfo = new ConnectInfo(hostField.getText(),
                                        Integer.parseInt(portField.getText()));
                        setVisible(false);
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(null, "Port is not a number", 
                             "Server connection Config", JOptionPane.ERROR_MESSAGE);
                    }
                }
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

        this.getContentPane().add(connectPanel, BorderLayout.CENTER);
        this.getContentPane().add(controlPanel, BorderLayout.SOUTH);
    }
}
