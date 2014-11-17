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
		showText("Bonjour , tu cherches une armure ?");
		addLink("Qui est tu ?", "", 100);
		addLink("Bye", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//case 1
	case 100:
		showText(
			"Je suis Boboko , le vendeur d'armures premier job pour les mercenaires, acolytes et acrobates !"
				);
		addLink("Retour", "", 0);
		return 1;
	}
	return 0;
}