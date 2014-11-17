#include "core/Core.h"
#include "core/MemoryLeak.h"
#include <iostream>

using namespace sdk;
using namespace std;


//#define STR_TYPE std::string
#define STR_TYPE sdk::stringc


s32 main()
{
	u32 t_time = CTime::system();

	{
		/*for (u32 i = 0; i < 50000; ++i)
		{
			STR_TYPE s("hallo, test");

			s = "hhhhhhhhhhhhhhhhhhhfffffffffffffffffff";

			s.clear();
			s.size();
			s.empty();
		}*/
	}

	sdk::stringc str("ggggggggggggggggggggggggg");
	str.append("djaskd");
	str.append(sdk::stringc("ööööööööööööööööööööööööööööö"));
	str.at(0);
	str.c_str();
	str.capacity();
	str.clear();
	str = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";
	str = str;
	str.compare(str);
	str.compare("jfdkdjf");
	str.count();
	str.data();
	str.empty();
	str.end();
	FASSERT(str.equals(str));
	str.equals("jkfjsdfkj");
	str.erase(2);
	str.erase(14, 10);
	str.erase_all('g');
	str.erase_first('ö');
	u32 o;
	str.find(o, 0, ' ');
	str.insert(2, ';');
	str.insert(4, "hallo");
	str.pop_back();
	str.pop_front();
	str.push_back(' ');
	str.push_front('.');
	str.replace(' ', '!');
	str.replace("   ", "jfkdsjfkdjf");
	str.reserve(12);
	str.resize(12);
	FASSERT(str.size() == 12);
	str.reverse();
	str.shuffle();
	str.size();
	str.substr(0, 10);
	str.substr(0);
	str.toArray();
	str = "13";
	FASSERT(str.toUInt() == 13);
	str.trim();
	str.trim_back();
	str.trim_front();

	CByteArray t_bytes;

	t_bytes << -1 << 1u << "test" << 0.4 << 0.1f;

	cout << t_bytes.getInt() << endl;
	cout << t_bytes.getUInt() << endl;
	cout << t_bytes.getString() << endl;
	cout << t_bytes.getDouble() << endl;
	cout << t_bytes.getFloat() << endl;

	cout << "Finished in " << (CTime::system() - t_time) << " ms" << endl;
	cin.get();

#ifdef _MSC_VER
#ifndef NDEBUG
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) );
#endif
#endif
}