package com.pc2ron.frame;

import java.io.DataInputStream;
import java.io.IOException;

import com.pc2ron.interfaces.IString;
import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IUint8;
import com.pc2ron.interfaces.IUint16;
import com.pc2ron.interfaces.IUInt32;
import com.pc2ron.interfaces.IInt8;
import com.pc2ron.interfaces.IInt16;
import com.pc2ron.interfaces.IInt32;
import com.pc2ron.interfaces.IDouble;
import com.pc2ron.interfaces.IFrameReceiver;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.frame.data.DonneeFactory;
import com.pc2ron.frame.data.ETypeDonnee;

//@todo Gestion des erreurs
public class FrameReceiver implements IFrameReceiver {

	@Override
	public IString recevoirChaine(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
        
		IString chaine = null;
                IUint16 nbOctets;
                byte[] buffer ;

		try {
                    int temp = in.readUnsignedShort();
                    nbOctets = donneeFactory.getEntierNonSigne2(temp);
                    
                    //nbOctets = this.recevoirEntierNonSigne2(in);

                    buffer = new byte[nbOctets.getEntier()];
                    in.read(buffer, 0, nbOctets.getEntier());
                    
                    chaine = donneeFactory.getChaine(new String(buffer, IString.CHARSET));
                    
		} catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
		}
		return chaine;
	}
    
    //@todo types de donnee a mettre en unsigned
	@Override
	public IData recevoirDonnee(DataInputStream in) {
		byte type;
		IData donnee = null;
		
		try {
			type = in.readByte();
			ETypeDonnee t = ETypeDonnee.getTypeDonnee(type);

			switch (t) {
				case ENTIER_SIGNE1:
					donnee = recevoirEntierSigne1(in);
					break;
					
				case ENTIER_SIGNE2:
					donnee = recevoirEntierSigne2(in);
					break;
					
				case ENTIER_SIGNE4:
					donnee = recevoirEntierSigne4(in);
					break;
					
				case ENTIER_NON_SIGNE1:
					donnee = recevoirEntierNonSigne1(in);
					break;
					
				case ENTIER_NON_SIGNE2:
					donnee = recevoirEntierNonSigne2(in);
					break;
					
				case ENTIER_NON_SIGNE4:
					donnee = recevoirEntierNonSigne4(in);
					break;
					
				case CHAINE:
					donnee = recevoirChaine(in);
					break;
					
				case FLOTTANT:
					donnee = recevoirFlottant(in);
					break;
					
				default:
					System.out.println("Mauvais type de donnee !");
			}

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return donnee;
	}

	@Override
	public IUint8 recevoirEntierNonSigne1(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IUint8 entier = null;
		try {
			entier = donneeFactory.getEntierNonSigne1((short) in.readUnsignedByte());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IUint16 recevoirEntierNonSigne2(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IUint16 entier = null;
		try {
			entier = donneeFactory.getEntierNonSigne2(in.readUnsignedShort());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IUInt32 recevoirEntierNonSigne4(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IUInt32 entier = null;
		try {
			long entierSigne = in.readInt();
			long entierNonSigne = entierSigne & 0xffffffffL;
			entier = donneeFactory.getEntierNonSigne4(entierNonSigne);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IInt8 recevoirEntierSigne1(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IInt8 entier = null;
		try {
			entier = donneeFactory.getEntierSigne1(in.readByte());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IInt16 recevoirEntierSigne2(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IInt16 entier = null;
		try {
			entier = donneeFactory.getEntierSigne2(in.readShort());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IInt32 recevoirEntierSigne4(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IInt32 entier = null;
		try {
			entier = donneeFactory.getEntierSigne4(in.readInt());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IDouble recevoirFlottant(DataInputStream in) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IDouble flottant = null;
		try {
			flottant = donneeFactory.getFlottant(in.readDouble());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return flottant;
	}

	@Override
	//@todo gestion des erreurs
	public IFrame recevoirTrame(DataInputStream in) {
		IFrameFactory trameFactory = FrameFactory.getInstance();
		IFrame trameRecue = trameFactory.getTrame();
		
		try {
                        byte typeFanion = in.readByte();
                        
			trameRecue.setTypeFanion(typeFanion);
                        short t = 255;
                        
                        EPennant eTypeFanion = EPennant.getTypeFanion(typeFanion);
                        
                        switch(eTypeFanion) {
                            case TrameNormale:
                                byte id = in.readByte();
                                trameRecue.setId(id);

                                byte nbDonnees = in.readByte();
                                
                                
                                //IDonneeFactory donneeFactory = DonneeFactory.getInstance();
                                IData donneeRecue;

                                // Reception des donnees
                                for(int i=0; i < nbDonnees; i++) {  
                                    donneeRecue = recevoirDonnee(in);             
                                    trameRecue.ajouterDonnee(donneeRecue);   
                                }
                                break;
                             
                            case TrameSpeciale:
                                return trameRecue;
                                
                            default:
                                System.out.println("Erreur de fanion !");
				return null;         
                        }
            
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
                
		return trameRecue;
	}

}
