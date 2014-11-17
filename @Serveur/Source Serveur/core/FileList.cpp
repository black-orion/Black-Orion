#include "FileList.h"
#include "Debug.h"

#ifdef OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


BEGIN_NAMESPACE_CORE
{

	CFileList::CFileList()
	{
	}

	CFileList::~CFileList()
	{
	}

	bool CFileList::scan(const char *_dir, bool _listhiddenfiles)
	{
		FDASSERT(_dir);

#ifdef OS_WINDOWS
		char t_dir[512];
		xstrcpy(t_dir, 260, _dir);

		u32 t_dirlen = strlen(t_dir);

		if (t_dirlen < 3)
			return false;

		if (t_dir[t_dirlen - 1] != '*' ||
			t_dir[t_dirlen - 2] != '\\')
		{
			t_dir[t_dirlen] = '\\';
			t_dir[t_dirlen + 1] = '*';
			t_dir[t_dirlen + 2] = 0;
		}

		HANDLE t_handle;
		WIN32_FIND_DATA t_wfd;

		//skip "."
		t_handle = FindFirstFileA(t_dir, &t_wfd);

		if (t_handle)
		{
			CFileEntry t_newentry;

			//skip ".."
			FindNextFile(t_handle, &t_wfd);

			while (FindNextFile(t_handle, &t_wfd))
			{
				t_newentry.Name = t_wfd.cFileName;

				t_newentry.IsFolder = ((t_wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

				t_newentry.IsHidden = ((t_wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0);

				if (!_listhiddenfiles &&
					t_newentry.IsHidden)
				{
					continue;
				}

				t_newentry.CreationTime = (u64(t_wfd.ftCreationTime.dwHighDateTime) << 32) +
					t_wfd.ftCreationTime.dwLowDateTime;

				t_newentry.LastChangeTime = (u64(t_wfd.ftLastWriteTime.dwHighDateTime) << 32) +
					t_wfd.ftLastWriteTime.dwLowDateTime;

				t_newentry.LastAccessTime = (u64(t_wfd.ftLastAccessTime.dwHighDateTime) << 32) +
					t_wfd.ftLastAccessTime.dwLowDateTime;

				t_newentry.Size = (u64(t_wfd.nFileSizeHigh) << 32) + t_wfd.nFileSizeLow;

				m_files.push_back(t_newentry);
			}

			FindClose(t_handle);
			return true;
		}
#endif

		return false;
	}

	void CFileList::clear()
	{
		m_files.clear();
	}

	u32 CFileList::getFileCount() const
	{
		return m_files.size();
	}

	CFileEntry &CFileList::getFile(u32 _num)
	{
		FDASSERT(_num < m_files.size());

		return m_files[_num];
	}

	const CFileEntry &CFileList::getFile(u32 _num) const
	{
		FDASSERT(_num < m_files.size());

		return m_files[_num];
	}

	void CFileList::remove(u32 _num)
	{
		if (_num < m_files.size())
		{
			m_files.erase(_num);
		}
	}

	void CFileList::remove(const char *_fileName)
	{
		FDASSERT(_fileName);

		for (u32 i = 0; i < m_files.size(); i++)
		{
			if (strcmp(m_files[i].Name.c_str(), _fileName) == 0)
			{
				m_files.erase(i);
				return;
			}
		}
	}

	void CFileList::add(const char *_fileName, bool _isfolder)
	{
		m_files.push_back(CFileEntry(_fileName, _isfolder));
	}

};
