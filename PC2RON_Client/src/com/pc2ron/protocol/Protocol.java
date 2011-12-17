package com.pc2ron.protocol;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import com.pc2ron.interfaces.*;
import com.pc2ron.frame.*;

import com.pc2ron.frame.data.*;
import com.pc2ron.game.EDirection;
import com.pc2ron.game.ESpeed;
import com.pc2ron.game.Player;
import java.awt.Color;
import java.awt.Point;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Protocole PC2RON du point de vue du client
 * Celui-ci gere l'echange entre le client et le serveur
 * @author Mehdi Drici
 */
public class Protocol implements IProtocol {
    private Socket sock;
    // Flux d'envoi et de reception
    private DataOutputStream out;
    private DataInputStream in;

    // Sender et Receiver de trame
    private IFrameReceiver receiver;
    private IVisitor sender;

    // Constructeur de trame
    private IFrameBuilder builder;

    // Verificateur de trame
    private IFrameChecker checker;

    // Unique instance du protocole
    private static IProtocol instance;

    private Protocol() {
        receiver = FrameReceiver.getInstance();
        sender = FrameSenderVisitor.getInstance();
        builder = FrameBuilder.getInstance();
        checker = FrameChecker.getInstance();
    }

    public static IProtocol getInstance() {
            if (null == instance) { // Premier appel
                    instance = new Protocol();
        }
        return instance;
    }
        
    /**
     * Se connecter au serveur
     * Un envoi d'une trame Initiate est effectue
     * @param host Adresse du serveur
     * @param port Port d'ecoute du serveur
     * @throws Exception Une exception est envoyee en cas de trame incorrect,
     *                   format incorrect ou d'acquittement negatif 
     */
    @Override
    public void connect(String host, int port) throws Exception {
        // Initialisation de la socket
        sock = new Socket(host, port);
        in = new DataInputStream(sock.getInputStream());
        out = new DataOutputStream(sock.getOutputStream());

        // Envoi de la trame Init
        sender.visit(builder.createInit(), out);

        // Reception de l'acquittement
        IFrame ack = receiver.readFrame(in);

        // Verifification de l'acquittement
        checker.check(ack);

        IDataString msg = (IDataString) ack.getData().get(0);

        if(msg.getContent().equals("NO")) {
            throw new ProtocolException(
            "La version du protocole n'est pas supportee par le serveur !");
        }
    }
    
    /**
     * Deconnexion du serveur
     * Il s'agit d'un envoi de la trame de fin de transmission
     * et de la fermeture de la socket
     */
    @Override
    public void disconnect() {
        try {
            IFrameFactory trameFactory = FrameFactory.getInstance();
            sender.visit(trameFactory.createEndFrame(), out);

            out.flush();
            out.close();
            sock.close();
         } catch (IOException ex) {
             Logger.getLogger(Protocol.class.getName()).log(Level.SEVERE, null, ex);
         } catch (IncorrectFrameException ex) {
             Logger.getLogger(Protocol.class.getName()).log(Level.SEVERE, null, ex);
         }
    }
    

    /**
     * Inscription du joueur
     * Un envoi de la trame Connect est effectue
     * @param rgb Couleur de la moto du joueur
     * @param name Nom du joueur
     * @return L'identifiant du joueur retourne par le serveur en case de succes
     * @throws Exception Une exception est envoyee en cas de trame incorrect,
     *                   format incorrect ou d'acquittement negatif
     */
    @Override
    public int register(short[] rgb, String name) throws Exception {
        // Envoi de la trame Init
        sender.visit(builder.createConnect(rgb, name), out);

        // Reception de l'acquittement
        IFrame registered = receiver.readFrame(in);

        // Verifification de l'acquittement
        checker.check(registered);

        IDataString msg = (IDataString) registered.getData().get(0);
        
        // On envoi le message d'erreur recu
        if(msg.getContent().equals("NO")) {
            IDataString errorMsg = (IDataString) registered.getData().get(1);
            throw new ProtocolException(errorMsg.getContent());
        
        // On retourne l'identifiant du joueur nouvellement inscrit
        } else {
            IDataUint16 id = (IDataUint16) registered.getData().get(1);
            return id.getValue();
        }
    }

    /**
     * Reception et extraction des donnees d'une trame quelconque
     * 
     * @return Resultat de la lecture de trame correspondant a 
     *         la paire de 2 elements:
     *         - le type de trame
     *         - les donnees extraites de la trame (leur format depend de 
     *           la trame recue)
     * 
     * NOTA: cette methode permet l'aiguillage vers la methode de reception
     *       adaptee
     *       
     * @throws Exception Une exception est envoyee en cas de trame incorrect,
     *                   format incorrect ou d'acquittement negatif
     */
    @Override
    public ArrayList readFrame() throws Exception {
        IFrame receivedFrame = receiver.readFrame(in);
        
        EFrameType frameType = EFrameType.getFrameType(receivedFrame.getId());
        
        // Resultat correspondant aux donnees extraites de la trame recue
        ArrayList result = new ArrayList();
        
        // Verification de la trame
        checker.check(receivedFrame);
        
        // Initialisation du resultat avec le type de trame
        result.add(frameType);
        
        switch(frameType) {
            case User:
                ArrayList<IPlayer> players = new ArrayList<IPlayer>();
                do {
                    players.add(readUser(receivedFrame));
                    receivedFrame = receiver.readFrame(in);
                    frameType = EFrameType.getFrameType(receivedFrame.getId());
                } while (frameType != EFrameType.End);
                result.add(players);
                break;

            case Start:
                result.add(readStart(receivedFrame));
                break;

            case Pause:
                result.add(readPause(receivedFrame));
                break;

            case Turn:
                result.add(readTurn(receivedFrame));
                break;

            case Death:
                result.add(readDeath(receivedFrame));
                break;

            case Win:
                result.add(readWin(receivedFrame));
                break;

            default:;
        }

        return result;
    }
    
    /**
     * Extraction des donnees d'une trame Start
     * a savoir le message recu
     * @param startFrame Trame a extraire
     * @return Message recu
     */
    @Override
    public String readStart(IFrame startFrame) {
        IDataString msg = (DataString) startFrame.getData().get(0);

        return msg.getContent();
    }
    
    /**
     * Extraction des donnees d'une trame Pause
     * a savoir le message recu
     * @param pauseFrame Trame a extraire
     * @return Message recu
     */
    @Override
    public String readPause(IFrame pauseFrame) {
        IDataString msg = (DataString) pauseFrame.getData().get(0);

        return msg.getContent();
    }
    
    /**
     * Extraction des donnees d'une trame Death
     * a savoir l'identifiant du/des perdant(s)
     * @param deathFrame Trame a extraire
     * @return Le ou les identifiants des deux perdants
     */
    @Override
    public int[] readDeath(IFrame deathFrame) {
        int loosersSize = deathFrame.getDataSize();
        int[] loosers = new int[loosersSize];
        IDataUint16 idLooser;
        
        for(int i = 0; i < loosersSize; i++) {
            idLooser = (IDataUint16) deathFrame.getData().get(i);
            loosers[i] = idLooser.getValue();
        }
        
        return loosers;
    }
    
    /**
     * Extraction des donnees d'une trame Death
     * a savoir les donnees d'un joueur
     * @param userFrame Trame a extraire
     * @return Donnes du joueur recues
     */
    @Override
    public IPlayer readUser(IFrame userFrame) {
        IPlayer playerReceived = new Player();

        List data = userFrame.getData();

        // Identifiant du joueur recu
        IDataUint16 id = (IDataUint16) data.get(0);
        playerReceived.setId(id.getValue());

        // Nom du joueur recu
        IDataString name = (IDataString) data.get(1);
        playerReceived.setName(name.getContent());
        
        // Couleur de la moto du joueur recu
        IDataUint8 red = (IDataUint8) data.get(2);
        IDataUint8 green = (IDataUint8) data.get(3);
        IDataUint8 blue = (IDataUint8) data.get(4);
        Color color = new Color(red.getValue(), green.getValue(), blue.getValue());
        playerReceived.setRGB(color);
        
        // Coordonnees initiales du joueur recu
        IDataUint16 x0 = (DataUint16) data.get(5);
        IDataUint16 y0 = (DataUint16) data.get(6);
        playerReceived.getPositions().add(new Point(x0.getValue(), y0.getValue()));
        
        // Vitesse du joueur recu
        IDataUint8 speed = (IDataUint8) data.get(7);
        playerReceived.setSpeed(ESpeed.getESpeed(speed.getValue()));
        
        return playerReceived;
    }
    
    
    /**
     * Extraction des donnees d'une trame Win
     * a savoir l'identifiant du gagnant
     * @param deathFrame Trame a extraire
     * @return L'identifiant du gagnant
     */
    @Override
    public int readWin(IFrame trameWin) {
        IDataUint16 winnerId = (IDataUint16) trameWin.getData().get(0);

        return winnerId.getValue();
    }
    
    /**
     * Extraction des donnees d'une trame Turn
     * a savoir les positions et directions des joueurs
     * @param turnFrame Trame a extraire
     * @return Positions et directions de tous les participants recus
     * @throws Exception 
     */
    @Override
    public ArrayList readTurn(IFrame turnFrame) {
	ArrayList result = new ArrayList();
        
        int DataSize = turnFrame.getDataSize();
        int playersSize = (DataSize-1) / PLAYER_DATA_SIZE;
        IPlayer[] players = new Player[playersSize];
        
        Point position = new Point();
        IDataUInt32 elapsedTime =  (IDataUInt32) turnFrame.getData().get(0);
        IDataUint16 id;
        IDataUint16 x, y;
        IDataUint16 dir;
        
        /*
         * Ajout des informations des joueurs recus dans la trame Turn
         */
        for(int i = 0; i < playersSize; i++) {
            // Identifiant du joueur
            id = (IDataUint16) turnFrame.getData().get((i*PLAYER_DATA_SIZE) + 1);
            
            // Position du joueur
            x = (IDataUint16) turnFrame.getData().get((i*PLAYER_DATA_SIZE) + 2);
            y = (IDataUint16) turnFrame.getData().get((i*PLAYER_DATA_SIZE) + 3);
            position.setLocation(x.getValue(), y.getValue());
            
            // Direction du joueur
            dir = (IDataUint16) turnFrame.getData().get((i*PLAYER_DATA_SIZE) + 4);
            
            players[i].setId(id.getValue());
            players[i].getPositions().add(position);
            players[i].setDir(EDirection.getEDirection(dir.getValue()));
            
        }
        
	// Construction du resultat de la lecture
        result.add(elapsedTime.getValue());
        result.add(players);
        
        return result;
    }
    
    /**
     * Envoi d'un ordre representant un changement de direction ou un abandon
     * @param ordre 
     */
    @Override
    public void sendOrder(EOrder order) throws IncorrectFrameException {
        sender.visit(builder.createOrder(order), out);
    }
    
    /**
     * Signaler que le joueur est pret
     * @todo implement
     */
    public void startGame() {
        
    }
}
