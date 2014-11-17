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
		showText("Bonjour , veux-tu que je te guide ?");
		addLink("Oui!", "", 100);
		addLink("Bye", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//case 1
	case 100:
		showText(
			"Si tu as l'ame d'un guerrier , que tu aimes vaincre , choisis d'etre mercenaire mon jeune ami!"
				);
		addLink("Retour", "", 0);
		return 1;
	}
	return 0;
}