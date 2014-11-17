#ifndef CORE_FILELIST_H
#define CORE_FILELIST_H


#include "CoreBase.h"
#include "String.h"
#include "Array.h"


BEGIN_NAMESPACE_CORE
{

	struct CFileEntry
	{
		sdk::stringc Name;

		bool IsFolder;

		bool IsHidden;

		u32 CreationTime;

		u32 LastChangeTime;

		u32 LastAccessTime;

		u64 Size;

		CFileEntry()
			: IsFolder(false)
			, IsHidden(false)
			, CreationTime(0)
			, LastChangeTime(0)
			, LastAccessTime(0)
			, Size(0)
		{
		}

		CFileEntry(const char *_name, bool _isfolder)
			: Name(_name)
			, IsFolder(_isfolder)
			, IsHidden(true)
			, CreationTime(0)
			, LastChangeTime(0)
			, LastAccessTime(0)
			, Size(0)
		{
		}
	};


	class CFileList
	{
	public:

		CFileList();

		~CFileList();

		//scans a directory for files and folders; _dir must have "\\*" at its end
		bool scan(const char *_dir, bool _listhiddenfiles = false);

		void clear();

		u32 getFileCount() const;

		CFileEntry &getFile(u32 _num);

		const CFileEntry &getFile(u32 _num) const;

		void remove(u32 _num);

		void remove(const char *_fileName);

		void add(const char *_fileName, bool _isfolder);

	private:

		CArray<CFileEntry> m_files;

	};

};


#endif //CORE_FILELIST_H
