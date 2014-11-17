#include "../scripts/spheron.as"

const int FIRST_JOB_LEVEL = 15;

const int SECOND_JOB_LEVEL = 60;

IPlayer player;

bool canGetFirstJob()
{
	return (
		player.getLevel() >= FIRST_JOB_LEVEL &&
		player.getJob() == JOB_VAGRANT);
}

bool canGetSecondJob()
{
	return (
		player.getLevel() >= SECOND_JOB_LEVEL &&
		(
			player.getJob() == JOB_MERCENARY ||
			player.getJob() == JOB_ACROBAT ||
			player.getJob() == JOB_ASSIST ||
			player.getJob() == JOB_MAGICIAN
		));
}

int OnDialogAction(const string &str, int action)
{
	clearDialog();

	player = getUser();

	switch (action)
	{
	//Home
	case 0:
		if (canGetFirstJob())
		{
			string text = "Bonjour ";
			text += player.getName();
			text += "!\nSi tu veux Changer de JOB clique sur celui que tu desire:";

			showText(text);

			addLink("Mercenaire", "", 100);
			addLink("Acrobat", "", 200);
			addLink("Assist", "", 300);
			addLink("Magicien", "", 400);
		}
		else if (canGetSecondJob())
		{
			string text = "Bonjour ";
			text += player.getName();
			text += "!\nSi tu veux Changer de JOB clique sur celui que tu desire:";
			
			showText(text);
			
			switch (player.getJob())
			{
			case JOB_MERCENARY:
				addLink("Knight", "", 1100);
				addLink("Blade", "", 1200);
				break;

			case JOB_ACROBAT:
				addLink("Jester", "", 2100);
				addLink("Ranger", "", 2200);
				break;

			case JOB_ASSIST:
				addLink("Ringmaster", "", 3100);
				addLink("Billposter", "", 3200);
				break;

			case JOB_MAGICIAN:
				addLink("Psykeeper", "", 4100);
				addLink("Elementor", "", 4200);
				break;
			}
		}
		else
		{
			showText("Hello!");
		}
		addLink("Bye", "", -1);
		return 1;

	//close
	case -1:
		closeDialog();
		return 1;

	//Mercenary
	case 100:
		showText("Do you really want to become a MERCENARY?");
		addButton("__YES__", "", 101);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 101:
		if (canGetFirstJob())
		{
			player.setJob(JOB_MERCENARY);
			showText("You are now a MERCENARY!");
			addLink("Back", "", 0);
		}
		return 1;

	//Knight
	case 1100:
		showText("Do you really want to become a KNIGHT?");
		addButton("__YES__", "", 1101);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 1101:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_MERCENARY)
		{
			player.setJob(JOB_KNIGHT);
			showText("You are now a KNIGHT!");
			addLink("Back", "", 0);
		}
		return 1;

	//Blade
	case 1200:
		showText("Do you really want to become a BLADE?");
		addButton("__YES__", "", 1201);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 1201:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_MERCENARY)
		{
			player.setJob(JOB_BLADE);
			showText("You are now a BLADE!");
			addLink("Back", "", 0);
		}
		return 1;

	//Acrobat
	case 200:
		showText("Do you really want to become an ACROBAT?");
		addButton("__YES__", "", 201);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 201:
		if (canGetFirstJob())
		{
			player.setJob(JOB_ACROBAT);
			showText("You are now an ACROBAT!");
			addLink("Back", "", 0);
		}
		return 1;

	//Jester
	case 2100:
		showText("Do you really want to become a JESTER?");
		addButton("__YES__", "", 2101);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 2101:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_ACROBAT)
		{
			player.setJob(JOB_JESTER);
			showText("You are now a JESTER!");
			addLink("Back", "", 0);
		}
		return 1;

	//Ranger
	case 2200:
		showText("Do you really want to become a RANGER?");
		addButton("__YES__", "", 2201);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 2201:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_ACROBAT)
		{
			player.setJob(JOB_RANGER);
			showText("You are now a RANGER!");
			addLink("Back", "", 0);
		}
		return 1;

	//Assist
	case 300:
		showText("Do you really want to become an ASSIST?");
		addButton("__YES__", "", 301);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 301:
		if (canGetFirstJob())
		{
			player.setJob(JOB_ASSIST);
			showText("You are now an ASSIST!");
			addLink("Back", "", 0);
		}
		return 1;

	//Ringmaster
	case 3100:
		showText("Do you really want to become a RINGMASTER?");
		addButton("__YES__", "", 3101);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 3101:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_ASSIST)
		{
			player.setJob(JOB_RINGMASTER);
			showText("You are now a RINGMASTER!");
			addLink("Back", "", 0);
		}
		return 1;

	//Billposter
	case 3200:
		showText("Do you really want to become a BILLPOSTER?");
		addButton("__YES__", "", 3201);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 3201:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_ASSIST)
		{
			player.setJob(JOB_BILLPOSTER);
			showText("You are now a BILLPOSTER!");
			addLink("Back", "", 0);
		}
		return 1;

	//Magician
	case 400:
		showText("Do you really want to become a MAGICIAN?");
		addButton("__YES__", "", 401);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 401:
		if (canGetFirstJob())
		{
			player.setJob(JOB_MAGICIAN);
			showText("You are now a MAGICIAN!");
			addLink("Back", "", 0);
		}
		return 1;

	//Psykeeper
	case 4100:
		showText("Do you really want to become a PSYKEEPER?");
		addButton("__YES__", "", 4101);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 4101:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_MAGICIAN)
		{
			player.setJob(JOB_PSYKEEPER);
			showText("You are now a PSYKEEPER!");
			addLink("Back", "", 0);
		}
		return 1;

	//Elementor
	case 4200:
		showText("Do you really want to become an ELEMENTOR?");
		addButton("__YES__", "", 4201);
		addButton("__NO__", "", 0);
		addLink("Back", "", 0);
		return 1;

	case 4201:
		if (player.getLevel() >= SECOND_JOB_LEVEL &&
			player.getJob() == JOB_MAGICIAN)
		{
			player.setJob(JOB_ELEMENTOR);
			showText("You are now an ELEMENTOR!");
			addLink("Back", "", 0);
		}
		return 1;
	}

	return 0;
}