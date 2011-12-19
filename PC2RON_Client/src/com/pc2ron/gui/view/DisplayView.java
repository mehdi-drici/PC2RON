/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.view;

import com.pc2ron.gui.model.DisplayModel;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JTextPane;

/**
 *
 * @author mehdi
 */
public class DisplayView extends JTextPane implements Observer {
    private static final long serialVersionUID = 112554656546987414L;
    
    private DisplayModel model;
    
    public DisplayView(DisplayModel model) {
        this.model = model;
        model.addObserver(this);
    }
    
    @Override
    public void update(Observable arg0, Object arg1) {
        this.setText(model.getText());
    }
    
}
