package com.pc2ron.interfaces;

public interface IVisitable {
	 <Data, Result> Result accept (IVisitor<Data, Result> visiteur, Data donnees);
}
