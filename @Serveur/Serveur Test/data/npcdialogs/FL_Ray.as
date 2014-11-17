#include "../scripts/spheron.as"

IPlayer player;

string str;

int OnDialogAction(const string &str, int action)
{
	clearDialog();


	switch (action)
	{

	case 0:
		showText("Bonjour , Jeune Gerrier tu veux aller en Arene?");
		addLink("Qui est tu ?", "", 100);
		addLink("Aller a l'arene", "", 500);
		addLink("Bye", "", -1);
		return 1;


	case -1:
		closeDialog();
		return 1;
		
	case 500:
		showText("Non disponible ...");
		addLink("Retour", "", 0);
		return 1;
	

	case 100:
		showText("Je suis Ray , le gardien de l'arene");
		addLink("Retour", "", 0);
		return 1;
	}
	return 0;
}