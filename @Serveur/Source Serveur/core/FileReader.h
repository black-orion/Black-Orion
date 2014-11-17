#ifndef CORE_FILEREADER_H
#define CORE_FILEREADER_H


#include "CoreBase.h"
#include "String.h"
#include "Util.h"


BEGIN_NAMESPACE_CORE
{

	class CFileReader
	{
	public:

		enum E_Option
		{
			opt_comments = 1
		};

		CFileReader();

		CFileReader(const char *_filename, bool _closeafterreading = true);

		~CFileReader();

		bool open(const char *_filename, bool _closeafterreading = true);

		bool isOpen();

		bool end();

		void quit();

		void close();

		bool reload();

		void setContent(const char *_content);

		const char *getContent();

		const char *getContentRest();

		void clearContent();

		void rewind();

		u32 getSize();

		const char *getFileName();

		bool getOption(u32 _option);

		void setOption(u32 _option, bool _on);

		char readChar(bool _skipwhitespaceandcomments = true);

		sdk::stringc readNext(u32 _count = 1);

		char *readNext(char *_dest, u32 _destsize, u32 _count = 1);

		void skipNext(u32 _count = 1);

		sdk::stringc readString(char _delim = '"');

		sdk::stringc readStringEx(const char *_delim = "\"");

		char *readString(char *_dest, u32 _destsize, char _delim = '"');

		char *readStringEx(char *_dest, u32 _destsize, const char *_delim = "\"");

		void skipString(char _delim = '"');

		void skipString(const char *_delim);

		s32 readInt();

		u32 readUInt();

		s64 readInt64();

		u64 readUInt64();

		f32 readFloat();

		f64 readDouble();

		//"1", "TRUE" and "true" (not case-sensitive) -> true
		bool readBool();

		sdk::stringc readLine();

		char *readLine(char *_dest, u32 _destsize);

		void skipLine();

		CFileReader &operator = (const CFileReader &_other);

	private:

		FILE *m_file;

		bool m_opensuccess;

		sdk::stringc m_filename;

		sdk::stringc m_content;

		const char *m_pos;

		const char *m_end;

		u32 m_readingpos;

		u32 m_options;

		s32 m_currentbytesread;

		enum {BUF_SIZE = 8192,
			BUF_2_SIZE = 2048};

		static char m_buffer[BUF_SIZE];

		static char m_buffer_2[BUF_2_SIZE];

		bool _load();

		void _updatePos();

		void _toNextToken();

		void _skipComments();

	};

};


#endif //CORE_FILEREADER_H
