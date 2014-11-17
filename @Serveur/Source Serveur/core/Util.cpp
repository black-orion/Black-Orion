#include "Util.h"
#include "Debug.h"


BEGIN_NAMESPACE_CORE
{

	u32 g_seed = 0;

	void seed(u32 _number)
	{
		g_seed = _number;
	}

	u32 random()
	{
		return (((g_seed = g_seed * 214013L + 2531011L) >> 16) & 0xffff);
	}

	u32 random(u32 _max)
	{
		return random() % (_max + 1);
	}

	u32 random(u32 _min, u32 _max)
	{
		FDASSERT(_min <= _max);

		return _min + (random() % (_max - _min + 1));
	}

	u32 random32()
	{
		return random() | (random() << 16);
	}

	u32 random32(u32 _max)
	{
		return random32() % (_max + 1);
	}

	u32 random32(u32 _min, u32 _max)
	{
		FDASSERT(_min <= _max);

		return _min + (random32() % (_max - _min + 1));
	}

	f32 randomf()
	{
		return (random32(1000000) / f32(1000000.0f));
	}

	f64 randomd()
	{
		return (random32(1000000) / f64(1000000.0f)) + (random32(1000000) / f64(1000000000000.0f));
	}

};