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
		showText("Bonjour jeune homme, le voyage t'interesse ?");
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
			"Je suis Isruel ,je vends des tickets vers des iles bonus telles que AZRIA . En veux tu ?"
				);
		addLink("Retour", "", 0);
		return 1;
	}
	return 0;
}