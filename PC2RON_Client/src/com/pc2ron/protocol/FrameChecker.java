/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.protocol;

import com.pc2ron.frame.EPennant;
import com.pc2ron.frame.data.*;
import com.pc2ron.interfaces.*;

/**
 * Verificateur d'une trame au niveau 
 * de la couche application (protocole)
 * Ce checker s'assure de la validite du format des trames
 * 
 * L'instance de ce Checker etant unique
 * on utilise le pattern Singleton 
 * @author Mehdi Drici
 */
public class FrameChecker implements IFrameChecker {
    // Unique instance de la fabrique
    private static IFrameChecker instance;
    
    private FrameChecker() {
    }

    /**
    * Recuperer l'instance du singleton
    * @return L'unique instance du constructeur 
    */
    public static IFrameChecker getInstance() {
        if (null == instance) { // Premier appel
            instance = new FrameChecker();
        }

        return instance;
    }
    
    /**
     * Aiguillage sur la methode de verification a utiliser
     * en fonction du type de trame
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *         au protocole PC2RON
     */
    @Override
    public void check(IFrame frame) throws FormatException {
        EPennant pennant = EPennant.getPennant(frame.getPennant());
        
        switch(pennant) {
            case NormalFrame:
                EFrameType type = EFrameType.getFrameType(frame.getId());
                switch(type) {
                    case Ack:
                        checkAck(frame);
                        break;
                        
                    case Registered:
                        checkRegistered(frame);
                        break;
                        
                    case Start:
                        checkStart(frame);
                        break;
                        
                    case Pause:
                        checkPause(frame);
                        break;
                        
                    case Death:
                        checkDeath(frame);
                        break;
                        
                    case Win:
                        checkWin(frame);
                        break;
                        
                    case End:
                        checkEnd(frame);
                        break;
                        
                    case Turn:
                        checkTurn(frame);
                        break;
                        
                    case User:
                        checkUser(frame);
                        break;
                        
                    default:
                        // Type de trame inconnu
                        throw new FormatException();
                }
                break;
            
            case SpecialFrame:
                break;
             
            // Fanion inconnu
            // Ce code ne doit jamais etre atteint
            // Une erreur de fanion est reportee par la couche transport
            default:
                throw new FormatException();
        }
    }
    
    /**
     * Verifier une trame Ack
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkAck(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.Ack;
        IData field;
        
        if(frame.getDataSize() != 2) {
            throw new FormatException(frameType.toString(), 
                                                 "Nombre de donnees incorrect");
        }
        
        // Verification de premier champ
        field = frame.getData().get(0);
        
        if(!(field instanceof DataString)) {
            throw new FormatException(frameType.toString(), 
                                  "Le champ d'acquittement recu est incorrect");
        }
        
        // Verification du nom d'application 
        field = frame.getData().get(1);
        
        if(! (field instanceof DataString)) {
            IDataString ack = (IDataString) field;
            
            if(! ack.getContent().equals("OK")) {
                throw new FormatException(frameType.toString(), 
                        "Le champ de nom application recu n'est pas correct !");
            }
        }
    }
    
    /**
     * Verifier une trame Registered
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkRegistered(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.Registered;
        IData field;
        
        // Verification du nombre de donnees
        if(frame.getDataSize() != 2) {
            throw new FormatException(frameType.toString(), 
                                                 "Nombre de donnees incorrect");
        }
        
        // Verification du champ d'acquittement ("OK" ou "NO")
        field = frame.getData().get(0);
        if(! (field instanceof DataString)) {
            throw new FormatException(frameType.toString(), 
                                  "Le champ d'acquittement recu est incorrect");
        }
        
        // Verification du champ de l'identifiant (ou de message d'erreur)
        field = frame.getData().get(1);
        
        if( !(field instanceof DataString) && !(field instanceof DataUint16)) {
            throw new FormatException(frameType.toString(), 
                     "Le champ d'id ou de message d'erreur recu est incorrect");
        }
    }
    
    /**
     * Verifier une trame Start
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkStart(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.Start;
        IData field;
        
        // Verification du nombre de donnees
        if(frame.getDataSize() != 1) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
        
        // Verification du message
        field = frame.getData().get(0);
        if(! (field instanceof DataString)) {
            throw new FormatException(frameType.toString(), 
                                  "Le message start recu est incorrect");
        }
    }
    
    /**
     * Verifier une trame Pause
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkPause(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.Pause;
        IData field;
        
        // Verification du nombre de donnees
        if(frame.getDataSize() != 1) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
        
        // Verification du message
        field = frame.getData().get(0);
        if(! (field instanceof DataString)) {
            throw new FormatException(frameType.toString(), 
                                  "Le message pause recu est incorrect");
        }
    }
    
    /**
     * Verifier une trame Death
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkDeath(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.Death;
        IData field;
        
        // Verification du nombre de donnees
        if(frame.getDataSize() != 1 || frame.getDataSize() != 2) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
        
        // Verification de l'id du premier perdant
        field = frame.getData().get(0);
        if(! (field instanceof DataUint16)) {
            throw new FormatException(frameType.toString(), 
                                  "L'id du premier perdant est incorrect");
        }
        
        // Verification de l'id du deuxieme perdant (defini optionnellement)
        if(frame.getDataSize() == 2) {
            field = frame.getData().get(1);
            
            if(! (field instanceof DataUint16)) {
                throw new FormatException(frameType.toString(), 
                                      "L'id du deuxieme perdant est incorrect");
            }
        }
    }
    
    /**
     * Verifier une trame Win
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkWin(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.Win;
        IData field;
        
        // Verification du nombre de donnees
        if(frame.getDataSize() != 1) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
        
        // Verification de l'id du gagnant
        field = frame.getData().get(0);
        if(! (field instanceof DataUint16)) {
            throw new FormatException(frameType.toString(), 
                                  "L'id du gagnant est incorrect");
        }
    }
    
    /**
     * Verifier une trame Turn
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkTurn(IFrame frame) throws FormatException {        
        EFrameType frameType = EFrameType.Turn;
        IData field;
        
        // Verification du nombre de donnees
        // Le calcul est effectue en conformite avec la structure 
        // d'une trame Turn
        // La trame Turn doit au minimum contenir les informations
        // d'un joueur
        if(frame.getDataSize() <= 1 || (frame.getDataSize()-1) % 
                                         IProtocol.PLAYER_DATA_SIZE != 0) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
        
        // Verification du temps ecoule depuis le debut de la partie
        field = frame.getData().get(0);
        if(! (field instanceof DataUint32)) {
            throw new FormatException(frameType.toString(), 
                                      "Le temps ecoule est incorrect");
        }
        
        int playersSize = (frame.getDataSize()-1) / IProtocol.PLAYER_DATA_SIZE;
        
        for(int i=0; i < playersSize; i++) {
            
            // Verification des informations de chaque joueur
            for(int j=1; j <= IProtocol.PLAYER_DATA_SIZE; j++) {
                field = frame.getData().get((IProtocol.PLAYER_DATA_SIZE * i) + j);
                
                if(! (field instanceof DataUint16)) {
                    throw new FormatException(frameType.toString(), 
                                 "Les informations du joueur sont incorrectes");
                }
            }
        }
    }
    
    /**
     * Verifier une trame User
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkUser(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.User;
        IData field;
        
        // Verification du nombre de donnees
        if(frame.getDataSize() != 9) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
        
        // Verification de l'identifiant du joueur
        field = frame.getData().get(0);
        if(! (field instanceof DataUint16)) {
            throw new FormatException(frameType.toString(), 
                                      "L'identifiant est incorrect");
        }
        
        // Verification du nom
        field = frame.getData().get(1);
        if(! (field instanceof DataString)) {
            throw new FormatException(frameType.toString(), 
                                      "Le nom recu du joueur est incorrect");
        }
        
        // Verification de la couleur
        for(int i=0; i < 3; i++) {
            // Le champ de la couleur commence au champ 2
            field = frame.getData().get(2 + i);
            if(! (field instanceof DataUint8)) {
                throw new FormatException(frameType.toString(), 
                           "La couleur recue du joueur est incorrecte");
            }
        }
        
        // Verification des coordonnees
        for(int i=0; i < 2; i++) {
            // Le champ des coordonnees commence au champ 5
            field = frame.getData().get(5 + i);
            if(! (field instanceof DataUint16)) {
                throw new FormatException(frameType.toString(), 
                           "Les coordonnees recues du joueur sont incorrectes");
            }
        }
        
        // Verification de la direction
        field = frame.getData().get(7);
        if(! (field instanceof DataUint8)) {
            throw new FormatException(frameType.toString(), 
                                 "La direction recue du joueur est incorrecte");
        }
        
        // Verification de la vitesse
        field = frame.getData().get(8);
        if(! (field instanceof DataUint8)) {
            throw new FormatException(frameType.toString(), 
                                  "La vitesse recue du joueur est incorrecre");
        }
    }
    
    /**
     * Verifier une trame End
     * Une trame End ne contenant aucune donnee
     * il s'agit donc simplement de verifier que la trame n'en contient
     * effectivement pas
     * @param frame Trame a verifier
     * @throws FormatException Exception renvoyee en cas de non conformite
     *                         au protocole PC2RON
     */
    @Override
    public void checkEnd(IFrame frame) throws FormatException {
        EFrameType frameType = EFrameType.End;
        
        // Verification du nombre de donnees
        // Le calcul est effectue en conformite avec la structure 
        // d'une trame Turn
        if(frame.getDataSize() != 0) {
            throw new FormatException(frameType.toString(), 
                                      "Nombre de donnees incorrect");
        }
    }
}
