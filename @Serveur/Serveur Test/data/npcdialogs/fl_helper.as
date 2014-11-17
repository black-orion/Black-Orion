#include "../scripts/spheron.as"

IPlayer player;

string str;


int OnDialogAction(const string &str, int action)
{
	clearDialog();

	player = getUser();

	switch (action)
	{

	case 0:
		showText("Bonjour ! Vous desirez ?");
		addLink("Buff !", "", 300);
		addLink("Debuff !", "", 400);
		addLink("Rien merci", "", -1);
		return 1;

	//End
	case -1:
		closeDialog();
		return 1;

	//Buff!
	case 300:
		buff(49, 10, 3600000); 
		buff(44, 10, 3600000); 
		buff(50, 10, 3600000);
		buff(51, 10, 3600000);		
		buff(52, 10, 3600000); 
		buff(53, 10, 3600000); 
		buff(113, 10, 3600000);
		buff(114, 10, 3600000);		
		buff(115, 10, 3600000); 
		buff(116, 10, 3600000); 
		addLink("Merci du Buff", "", -1);
		return 1;

	//Debuff
	case 400:
		return 1;
	}

	return 0;
}