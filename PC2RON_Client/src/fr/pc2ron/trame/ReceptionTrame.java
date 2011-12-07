package fr.pc2ron.trame;

import java.io.DataInputStream;
import java.io.IOException;

import fr.pc2ron.interfaces.IChaine;
import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.IDonneeFactory;
import fr.pc2ron.interfaces.IEntierNonSigne1;
import fr.pc2ron.interfaces.IEntierNonSigne2;
import fr.pc2ron.interfaces.IEntierNonSigne4;
import fr.pc2ron.interfaces.IEntierSigne1;
import fr.pc2ron.interfaces.IEntierSigne2;
import fr.pc2ron.interfaces.IEntierSigne4;
import fr.pc2ron.interfaces.IFlottant;
import fr.pc2ron.interfaces.IReceptionTrame;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.interfaces.ITrameFactory;
import fr.pc2ron.trame.donnee.DonneeFactory;
import fr.pc2ron.trame.donnee.ETypeDonnee;
import org.omg.PortableInterceptor.SYSTEM_EXCEPTION;

//@todo Gestion des erreurs
public class ReceptionTrame implements IReceptionTrame {

	@Override
	public IChaine recevoirChaine(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
        
		IChaine chaine = null;
        IEntierNonSigne2 nbOctets;
        byte[] buffer ;

		try {
            int temp = in.readUnsignedShort();
            nbOctets = donneeFactory.getEntierNonSigne2(temp);
            //nbOctets = this.recevoirEntierNonSigne2(in);
            //debug
            System.out.println("taille chaine = " + temp);
            //debug
            buffer = new byte[nbOctets.getEntier()];
            in.read(buffer, 0, nbOctets.getEntier());
            chaine = donneeFactory.getChaine(new String(buffer, IChaine.CHARSET));
            
            //debug
            System.out.println("chaine = " + chaine.getChaine());
            //debug
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return chaine;
	}
    
    //@todo types de donnee a mettre en unsigned
	@Override
	public IDonnee recevoirDonnee(DataInputStream in) {
		byte type;
		IDonnee donnee = null;
		
		try {
			type = in.readByte();
            
            //debug
            System.out.println("Type donnee = " + type);
            //debug
            
			ETypeDonnee t = ETypeDonnee.getTypeDonnee(type);
			//debug
            System.out.println("t.getStringType() = " + t.getStringType());
            //debug
                    
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
                    //debug
                    System.out.println("Entier non signe 2 - OK : " + donnee.getClass());
                    //debug
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
            
            //debug
            System.out.println("donnee = " + donnee.toString());
            //debug
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return donnee;
	}

	@Override
	public IEntierNonSigne1 recevoirEntierNonSigne1(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IEntierNonSigne1 entier = null;
		try {
			entier = donneeFactory.getEntierNonSigne1((short) in.readUnsignedByte());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IEntierNonSigne2 recevoirEntierNonSigne2(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IEntierNonSigne2 entier = null;
		try {
			entier = donneeFactory.getEntierNonSigne2(in.readUnsignedShort());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IEntierNonSigne4 recevoirEntierNonSigne4(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IEntierNonSigne4 entier = null;
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
	public IEntierSigne1 recevoirEntierSigne1(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IEntierSigne1 entier = null;
		try {
			entier = donneeFactory.getEntierSigne1(in.readByte());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IEntierSigne2 recevoirEntierSigne2(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IEntierSigne2 entier = null;
		try {
			entier = donneeFactory.getEntierSigne2(in.readShort());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IEntierSigne4 recevoirEntierSigne4(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IEntierSigne4 entier = null;
		try {
			entier = donneeFactory.getEntierSigne4(in.readInt());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return entier;
	}

	@Override
	public IFlottant recevoirFlottant(DataInputStream in) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		IFlottant flottant = null;
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
	public ITrame recevoirTrame(DataInputStream in) {
		ITrameFactory trameFactory = TrameFactory.getInstance();
		ITrame trameRecue = trameFactory.getTrame();
		
		try {
			short typeFanion = (short) (in.readByte() & 0xff);
			
			trameRecue.setTypeFanion(typeFanion);

			if (typeFanion == ETypeFanion.TrameNormale.getType()) {
                byte id = in.readByte();
            
				trameRecue.setId(id);
				
				byte nbDonnees = in.readByte();
            
				//IDonneeFactory donneeFactory = DonneeFactory.getInstance();
				IDonnee donneeRecue;
				
				// Reception des donnees
				for(int i=0; i < nbDonnees; i++) {  
					donneeRecue = recevoirDonnee(in);             
					trameRecue.ajouterDonnee(donneeRecue);   
				}
				
			} else if (typeFanion == ETypeFanion.TrameSpeciale.getType()) {
				return trameRecue;
			
			} else {
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
