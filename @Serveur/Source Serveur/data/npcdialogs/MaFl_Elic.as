#include "../scripts/spheron.as"

const int FIRST_JOB_LEVEL = 15;

IPlayer player;

bool canGetFirstJob()
{
	return (
		player.getLevel() >= FIRST_JOB_LEVEL &&
		player.getJob() == JOB_VAGRANT);
}

string str;

int OnDialogAction(const string &str, int action)
{
	clearDialog();

	player = getUser();


	switch (action)
	{
	//Acceuil
	case 0:
		if (canGetFirstJob())
		{
			string text = "Bonjour ";
			text += player.getName();
			text += "!\nTu veux devenir un Acolyte ?";

			showText(text);

			addLink("Oui !", "", 100);
			addLink("Non !", "", -1);
		}
		else
		{
			string text = "Bonjour ";
			text += player.getName();
			text += "!\nJe suis le formateur des Acolytes";

			showText(text);
		}
		addLink("Bye", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//Acolytes
	case 100:
		showText("Tu veux vraiment devenir un Acolyte?");
		addButton("__YES__", "", 101);
		addButton("__NO__", "", 0);
		return 1;

	case 101:
		if (canGetFirstJob())
		{
			player.setJob(JOB_ASSIST);
			showText("Enfin te voila devenu un Acolyte!");
			addLink("Retour", "", 0);
		}
		return 1;

	}
	return 0;
}