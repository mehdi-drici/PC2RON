package fr.pc2ron.trame;

import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IChaine;
import fr.pc2ron.interfaces.IEntierNonSigne1;
import fr.pc2ron.interfaces.IEntierNonSigne2;
import fr.pc2ron.interfaces.IEntierNonSigne4;
import fr.pc2ron.interfaces.IEntierSigne1;
import fr.pc2ron.interfaces.IEntierSigne2;
import fr.pc2ron.interfaces.IEntierSigne4;
import fr.pc2ron.interfaces.IFlottant;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.interfaces.IVisitable;
import fr.pc2ron.interfaces.IVisiteur;
import fr.pc2ron.trame.donnee.ETypeDonnee;

public class VisiteurEnvoiTrame implements IVisiteur<DataOutputStream, IVisitable>{
   
    @Override
    public IVisitable visit(ITrame trame, DataOutputStream out) {
            try {
                out.writeByte(trame.getTypeFanion());

                ETypeFanion typeFanion = ETypeFanion.getTypeFanion(
                                                     trame.getTypeFanion());
                switch(typeFanion) {
                    case TrameNormale:
                        out.writeByte(trame.getId());
                        out.writeByte(trame.getNbDonnees());

                        for (int i=0; i < trame.getNbDonnees(); i++) {
                            trame.getDonnees().get(i).accept(this, out);
                        }
                        break;

                    case TrameSpeciale:
                        break;

                    default:
                        //@todo envoyer une exception
                        System.out.println("Fanion de la trame envoyee incorrect");
                }
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }

            // TODO Auto-generated method stub
            return null;
    }

    @Override
    public IVisitable visit(IEntierSigne1 donnee, DataOutputStream out) {
            try {
                    out.writeByte(ETypeDonnee.ENTIER_SIGNE1.getType());
                    out.writeByte(donnee.getEntier());

            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IEntierSigne2 donnee, DataOutputStream out) {
            try {
                    out.writeByte(ETypeDonnee.ENTIER_SIGNE2.getType());
                    out.writeShort(donnee.getEntier());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IEntierSigne4 donnee, DataOutputStream out) {
            try {
                    out.writeByte(ETypeDonnee.ENTIER_SIGNE4.getType());
                    out.writeInt(donnee.getEntier());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IEntierNonSigne1 donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.ENTIER_NON_SIGNE1.getType());
                    //out.writeShort(donnee.getEntier());

                    // Conversion en entier non signe
                    short entierNonSigne = donnee.getEntier();

                    out.writeByte((byte)entierNonSigne);
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IEntierNonSigne2 donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.ENTIER_NON_SIGNE2.getType());
                    //out.writeInt(donnee.getEntier());

                    int entierNonSigne = donnee.getEntier();

                    //@todo tester
                    //out.writeShort((short) entierNonSigne);

                    ArrayList<Byte> listeOctets = new ArrayList<Byte>();

                    // Valeur
                    listeOctets.add((byte) (entierNonSigne >>> 8));
                    listeOctets.add((byte) (entierNonSigne));

                    for(int i=0; i < listeOctets.size(); i++){	
                            out.writeByte(listeOctets.get(i));
            }

            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IEntierNonSigne4 donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.ENTIER_NON_SIGNE4.getType());
                    //out.writeLong(donnee.getEntier());

                    long entierNonSigne = donnee.getEntier();
                    ArrayList<Byte> listeOctets = new ArrayList<Byte>();

                    //@todo tester
                    //out.writeInt((int) entierNonSigne);

                    // Valeur		
                    listeOctets.add((byte)(entierNonSigne >>> 24));
                    listeOctets.add((byte)(entierNonSigne >>> 16));
                    listeOctets.add((byte)(entierNonSigne >>>  8));
                    listeOctets.add((byte)(entierNonSigne));

                    for(int i=0; i < listeOctets.size(); i++){	
                            out.writeByte(listeOctets.get(i));
            }

            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IChaine donnee, DataOutputStream out) {
            try {
                    short taille = (short) donnee.getChaine().getBytes("UTF-8").length;

                    out.write(ETypeDonnee.CHAINE.getType());
                    //out.writeShort(donnee.getChaine().getBytes("UTF-8").length);
                    out.writeShort(taille);
                    out.write(donnee.getChaine().getBytes());
                    //out.writeUTF(donnee.getChaine());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IFlottant donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.FLOTTANT.getType());
                    out.writeDouble(donnee.getFlottant());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }
}
