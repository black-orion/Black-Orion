#ifndef NPCOBJECT_H
#define NPCOBJECT_H


#include "WorldMain.h"
#include "WorldObject.h"


class INpcData;
class IMoverData;
class INpcDialogScript;


class INpcObject : public IWorldObject
{
public:

	INpcObject(ID _id, IWorld *_world, const INpcData *_data);

	~INpcObject();

	E_TYPE getType() const;

	const IMoverData *getMover() const;

	const INpcData *getData() const;

	//setData

	//setMover

	bool init();

	void onWorldRemove();

	void onDestroy();

	void update();

	void dialogAction(const PlayerObjectPtr &_pObj, const char *_str, s32 _action1, s32 _action2, s32 _unknown);

private:

	const IMoverData * m_mover;

	const INpcData *m_data;

	u32 m_text;

	TimeMs m_nextText;

	INpcDialogScript *m_dialogScript;

};


#endif //NPCOBJECT_H
