package fr.pc2ron.interfaces;

public interface IVisitable {
	 <Data, Result> Result accept (IVisiteur<Data, Result> visiteur, Data donnees);
}
