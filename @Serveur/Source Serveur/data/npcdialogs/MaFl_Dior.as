#include "../scripts/spheron.as"

IPlayer player;

string str;

int OnDialogAction(const string &str, int action)
{
	clearDialog();

	player = getUser();

	switch (action)
	{
	//Home
	case 0:
		showText("Bonjour , un Conseil ?");
		addLink("Qui est tu ?", "", 100);
    addLink("Comment voler ?", "", 200);
		addLink("Bye", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//case 1
	case 100:
		showText(
			"Je suis Dior, la vendeuse de planches"
				);
		addLink("Retour", "", 0);
		return 1;

	//case 2
	case 200:
		showText(
			"C'est facile! Il faut que tu sois plus du level 20 pour avoir automatiquement le niveau 1 de vol! Ensuite il te faut acheter un Balai,une Planche,une Hoverbike ou des Ailes."
				);
		addLink("Retour", "", 0);
		return 1;

	}
	return 0;
}