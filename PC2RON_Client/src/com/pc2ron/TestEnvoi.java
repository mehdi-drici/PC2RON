package com.pc2ron;

import java.net.*;
import java.io.*;
import com.pc2ron.interfaces.IProtocol;
import com.pc2ron.protocol.EOrder;
import com.pc2ron.protocol.Protocol;
import java.util.ArrayList;

public class TestEnvoi {
    public static void main(String[] argv) {        
        /*
        try {
            short r=10;
            short v=10;
            short b=10;
            String nom="ken";
            IProtocol pro = Protocol.getInstance();
            ArrayList contenu;
            
            // Init
            pro.connect("127.0.0.1", 5555);
            int id = pro.register(r, v, b, nom);
            System.out.println("ID : " + id);
            
            pro.sendOrder(EOrder.STRAIGHT);
            
            //start
            contenu = pro.readFrame();
            System.out.println("{Contenu} : " + contenu.toString());
            
            //pause
            contenu = pro.readFrame();
            System.out.println("{Contenu} : " + contenu.toString());
            
            //users
            contenu = pro.readFrame();
            System.out.println("{Contenu} : " + contenu.toString());
            
            //Thread.sleep(1000);
            pro.disconnect();
        } catch (UnknownHostException e) {
            System.out.println("Unkonw exception " + e.getMessage());

        } catch (IOException e) {
            System.out.println("IOException caught " + e.getMessage());
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } 
        */
    }
}