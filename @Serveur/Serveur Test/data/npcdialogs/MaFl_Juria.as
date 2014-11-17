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
		showText("Bonjour , Que veux tu ?");
		addLink("Qui est tu ?", "", 100);
    addLink("office publique ?", "", 200);
    addLink("Perin ?", "", 300);
    addLink("Guilde ?", "", 400);
    addLink("Boite aux lettres ?", "", 500);
		addLink("Bye", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//case 1
	case 100:
		showText(
			"Je suis Juria ,je m'occupe de l'office publique de Flarine mais je suis aussi une banque ."
				);
		addLink("Retour", "", 0);
		return 1;

	//case 2
	case 200:
		showText(
			"L'office publique est un endroit ou acheter ses perins et voir les statistiques des guildes."
				);
		addLink("Retour", "", 0);
		return 1;

  //case 3
	case 300:
		showText(
			"Les perins representent cent mille penyas."
				);
		addLink("Retour", "", 0);
		return 1;

  //case 4
	case 400:
		showText(
			"Ici nous ne voyons que des statistiques des guildes non approfondies. Allez au centre guilde de Flarine pour plus d'infos."
				);
		addLink("Retour", "", 0);
		return 1;

  //case 5
  case 500:
		showText(
			"La boite aux lettres a cote de moi te permet d'envoyer des lettres ou des objets aux autres joueurs."
				);
		addLink("Retour", "", 0);
		return 1;

	}
	return 0;
}