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
    addLink("Arme Ultime ?", "", 200);
    addLink("Percage ?", "", 300);
    addLink("Joyeau ?", "", 400);
    addLink("Upgrade ?", "", 500);
		addLink("Bye", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//case 1
	case 100:
		showText(
			"Je suis Bobochan , l'un des meilleurs forgerons de Madrigal."
				);
		addLink("Retour", "", 0);
		return 1;

	//case 2
	case 200:
		showText(
			"Les armes ultimes permettent de transformer tes armes classiques en armes surpuissantes dites ultimes."
				);
		addLink("Retour", "", 0);
		return 1;

  //case 3
	case 300:
		showText(
			"Le percage permet a ton arme d'accueillir un joyeau capable de modifier ses statistiques."
				);
		addLink("Retour", "", 0);
		return 1;

  //case 4
	case 400:
		showText(
			"Les joyeaux peuvent etre trouves soit en drop soit grace a un collecteur dans les champs de collection."
				);
		addLink("Retour", "", 0);
		return 1;

  //case 5
  case 500:
		showText(
			"Tu peux tout a fait upgrader ton arme ou armure grace a une pierre magique pour la rendre plus resistante ou puissante."
				);
		addLink("Retour", "", 0);
		return 1;

	}
	return 0;
}