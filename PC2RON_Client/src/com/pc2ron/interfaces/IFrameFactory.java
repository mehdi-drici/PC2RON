package com.pc2ron.interfaces;

import java.util.ArrayList;

/**
 * Interface representant la fabrique de trame (au niveau de la couche transport)
 * @author mehdi
 */
public interface IFrameFactory {
    public IFrame createFrame();
    public IFrame createFrame(short id);
    public IFrame createFrame(short id, IData data);
    public IFrame createFrame(short id, ArrayList<IData> dataList);
    public IFrame createEndFrame();
}
