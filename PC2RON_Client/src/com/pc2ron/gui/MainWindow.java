/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui;

import com.pc2ron.gui.dialog.RegisterDialog;
import com.pc2ron.gui.dialog.ConnectDialog;
import com.pc2ron.interfaces.*;
import com.pc2ron.protocol.EFrameType;
import com.pc2ron.protocol.Protocol;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

/**
 *
 * @author mehdi
 */
public class MainWindow extends JFrame {
    // Instance du protocole
    private IProtocol protocol = Protocol.getInstance();
    
    // Grille de jeu
    private GridPanel gridPanel = new GridPanel();
    
    // Zone des messages du serveur (Pause, Start, Death, Win)
    private JTextArea msgTextArea = new JTextArea(4, 20);
    private JPanel msgPanel = new JPanel();
    private JLabel msgLabel = new JLabel("Message from Server: ");
    
    // Zone de connexion et d'inscription au serveur
    private JPanel controlPanel = new JPanel();
    public JButton connectButton = new JButton("Connect");
    public JButton registerButton = new JButton("Register");
    
    public MainWindow(){
        this.setTitle("PC2RON Game");
        this.setMinimumSize(new Dimension(700, 500));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //this.setLocationRelativeTo(null);
         
        this.getContentPane().add(createNorthPanel(), BorderLayout.NORTH);
        this.getContentPane().add(msgTextArea, BorderLayout.CENTER);
        this.getContentPane().add(createSouthPanel(), BorderLayout.SOUTH);
        
        // On cache le bouton d'inscription par defaut
        this.registerButton.setVisible(false);
        
        this.setFocusable(true);        
        this.setVisible(true);
        
        //go();
    }
    
    public JPanel createNorthPanel() {
         gridPanel.setPreferredSize(new Dimension(3*this.getWidth() / 4, 400));
         return gridPanel;
    }
    
    public JPanel createSouthPanel() {
        // Zone de controle
        connectButton.addActionListener(new ConnectListener());
        registerButton.addActionListener(new RegisterListener());
        
        controlPanel.setBackground(Color.lightGray);
        controlPanel.setLayout(new FlowLayout());
        controlPanel.add(connectButton, FlowLayout.LEFT);
        controlPanel.add(registerButton, FlowLayout.CENTER);
        
        return controlPanel;
    }
    
    public JPanel createCenterPanel() {
        // Zone de message
        //msgTextArea.setEditable(false);
        msgLabel = new JLabel("Message from Server: ");
        //msgPanel.setLayout(new BorderLayout());
        //msgPanel.add(msgLabel, BorderLayout.WEST);
        msgPanel.add(msgLabel);
        msgPanel.setPreferredSize(new Dimension(100, 20));
        
        return msgPanel;
    }
    
    private void go() {
        try {
            ArrayList result = protocol.readFrame();
                    System.out.println(result.toString());
                    msgTextArea.setText(result.toString());
                    msgTextArea.repaint();
                    EFrameType frameType;

                    // Compte a rebours
                    do {
                        result = protocol.readFrame();
                        System.out.println(result);
                        msgTextArea.setText(result.toString());
                        msgTextArea.repaint();
                        frameType = (EFrameType) result.get(0);
                        
                    } while (frameType.equals(EFrameType.Pause));
                    
            for(;;) {
                gridPanel.update();
                gridPanel.repaint();
                
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        } catch (Exception ex) {
            Logger.getLogger(MainWindow.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void main(String[] args){
        new MainWindow();
    }
    
    /**
     * Ecouteur du bouton de connexion
     */
    class ConnectListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent arg0) {
            ConnectDialog connectDialog = 
                   new ConnectDialog(null, "Server connection conf", true);
                
            ConnectInfo connectInfo = connectDialog.showDialog();
            
            // Connexion
            try {
                protocol.connect(connectInfo.getHost(), connectInfo.getPort());
                registerButton.setVisible(true);
                connectButton.setVisible(false);
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(null, ex.toString(), 
                             "Server connection", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    
    /**
     * Ecouteur du bouton d'inscription
     */
    class RegisterListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent arg0) {
            RegisterDialog registerDialog = 
                   new RegisterDialog(null, "Registration infos", true);

            IPlayer player = registerDialog.showDialog();
            
            short red = (short) player.getRGB().getRed();
            short green = (short) player.getRGB().getGreen();
            short blue = (short) player.getRGB().getBlue();
            short[] rgb = {red, green, blue};
            
            try {
                int id = protocol.register(rgb, player.getName());
                registerButton.setVisible(false);
                /*
                JOptionPane.showMessageDialog(null, "Votre identifiant est " + id, 
                                         "Registration", 
                                         JOptionPane.INFORMATION_MESSAGE);
                
                 */
                go();
                
            
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(null, ex.toString(), 
                             "Server registration", JOptionPane.ERROR_MESSAGE);
            }
            
        }
    }
}

