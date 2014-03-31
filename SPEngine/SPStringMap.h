//////////////////////////////////////////////////////////////////////////
/// @file		SPStringMap.h the header file of template SPStringMap class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-10
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPString.h"
#include <map>
#include "SPLogHelper.h"
#include "SPIterator.h"

using namespace std;
namespace SPEngine
{
	/// @brief A SPString comparing struct.
	struct IsLessWString
	{
		bool operator () (const wstring& left, const wstring& right) const
		{
			//return wcscmp(left.c_str(), right.c_str()) < 0;
			return wcscmp(left.c_str(), right.c_str()) < 0;
		}
	};

	/// @brief A SPString comparing struct.
	struct IsLessString
	{
		bool operator () (const string& left, const string& right) const
		{
			//return wcscmp(left.c_str(), right.c_str()) < 0;
			return strcmp(left.c_str(), right.c_str()) < 0;
		}
	};


	///////////////////////////////////////////////////////////////////////
	/// @brief SPStringMap to produce a map indexed by SPString.
	///
	///////////////////////////////////////////////////////////////////////
	template <typename T>
	class SPWStringMap
	{
		map<wstring, T, IsLessWString> stringMap;	///< Inner map.
		typedef typename map<wstring, T, IsLessWString>::iterator Iter; ///< Map iterator.

	public:
		/// @name Operation
		/// @{
		void Clear()
		{
			stringMap.clear();
		}

		pair<wstring, T>& Get(int num)
		{
			assert(abs(num) < GetCount());
			
			if (num >= 0)
			{
				int pos = 0;
				Iter iter = stringMap.begin();

				while(pos < num)
				{
					iter++;
				}
			}
			else
			{
				int pos = 0;
				Iter iter = stringMap.rbegin();

				while(pos > num)
				{
					iter++;
				}
			}
		}

		T& Get(wstring index)
		{
			if (IsSet(index))
			{
				return stringMap[index];
			}
			
			SPLogHelper::WriteLog("[Game] WARNING: Trying to get an nonexistent object from map!");

			Add(index);

			return stringMap[index];
		}

		T& operator [] (wstring index)
		{
			return Get(index);
		}

		void Add(wstring index)
		{
			stringMap[index] = T();
		}

		void Set(wstring index, T object)
		{
			stringMap[index] = object;
		}

		void Remove(wstring index)
		{
			map<wstring, T, IsLessWString>::iterator iter = stringMap.find(index);

			if (iter != stringMap.end())
			{
				stringMap.erase(iter);
			}
			else
			{
				SPLogHelper::WriteDebug("[Game] WARNING: Removing an nonexistent index from map!");
			}
		}

		int GetCount()
		{
			return stringMap.size();
		}

		bool IsSet(wstring index)
		{
			if (stringMap.find(index) == stringMap.end())
			{
				return false;
			}

			return true;
		}

		const map<wstring, T, IsLessWString>* GetMap() const
		{
			 return &stringMap;
		}
		/// @}

	public:
		SPWStringMap(void) { }
		virtual ~SPWStringMap(void) { }
	};

	///////////////////////////////////////////////////////////////////////
	/// @brief SPStringMapIterator to go through a SPString map.
	///
	/// usage:
	///		SPStringMapIterator<Type> iter(stringMapPtr);
	///		for (iter.First(); !iter.IsDone(); iter.Next())
	///		{
	///			...
	///		}
	///////////////////////////////////////////////////////////////////////
	template<typename T>
	class SPWStringMapIterator : public SPIterator<T>
	{
	public:
		SPWStringMapIterator(const SPWStringMap<T>* setMap)
		{
			theMap = setMap;
			First();
		}

		virtual void First()
		{
			current = theMap->GetMap()->begin();
		}

		virtual void Next()
		{
			current++;
		}

		virtual bool IsDone() const
		{
			return current == theMap->GetMap()->end();
		}

		virtual T CurrentItem() const
		{
			assert(!IsDone());

			return current->second;
		}

		wstring CurrentIndex() const
		{
			return current->first;
		}

	private:
		const SPWStringMap<T>* theMap;
		typename map<wstring, T, IsLessWString>::const_iterator current;
	};

	template <typename T>
	class SPStringMap
	{
		map<string, T, IsLessString> stringMap;	///< Inner map.
		typedef typename map<string, T, IsLessString>::iterator Iter; ///< Map iterator.

	public:
		/// @name Operation
		/// @{
		void Clear()
		{
			stringMap.clear();
		}

		pair<string, T>& Get(int num)
		{
			assert(abs(num) < GetCount());

			if (num >= 0)
			{
				int pos = 0;
				Iter iter = stringMap.begin();

				while(pos < num)
				{
					iter++;
				}
			}
			else
			{
				int pos = 0;
				Iter iter = stringMap.rbegin();

				while(pos > num)
				{
					iter++;
				}
			}			
		}

		T& Get(string index)
		{
			if (IsSet(index))
			{
				return stringMap[index];
			}

			SPLogHelper::WriteLog("[Game] WARNING: Trying to get an nonexistent object from map!");

			Add(index);

			return stringMap[index];			
		}

		T& operator [] (string index)
		{
			return Get(index);
		}

		void Add(string index)
		{
			stringMap[index] = T();
		}

		void Set(string index, T object)
		{
			stringMap[index] = object;
		}

		void Remove(string index)
		{
			map<string, T, IsLessString>::iterator iter = stringMap.find(index);

			if (iter != stringMap.end())
			{
				stringMap.erase(iter);
			}
			else
			{
				SPLogHelper::WriteLog("[Game] WARNING: Removing an nonexistent index from map!");
			}
		}

		int GetCount()
		{
			return stringMap.size();
		}

		bool IsSet(string index)
		{
			if (stringMap.find(index) == stringMap.end())
			{
				return false;
			}

			return true;
		}

		const map<string, T, IsLessString>* GetMap() const
		{
			return &stringMap;
		}
		/// @}

	public:
		SPStringMap(void) {Clear();}
		virtual ~SPStringMap(void) {}		
	};

	///////////////////////////////////////////////////////////////////////
	/// @brief SPStringMapIterator to go through a SPString map.
	///
	/// usage:
	///		SPStringMapIterator<Type> iter(stringMapPtr);
	///		for (iter.First(); !iter.IsDone(); iter.Next())
	///		{
	///			...
	///		}
	///////////////////////////////////////////////////////////////////////
	template<typename T>
	class SPStringMapIterator : public SPIterator<T>
	{
	public:
		SPStringMapIterator(const SPStringMap<T>* setMap)
		{
			theMap = setMap;
			First();
		}

		virtual void First()
		{
			current = theMap->GetMap()->begin();
		}

		virtual void Next()
		{
			current++;
		}

		virtual bool IsDone() const
		{
			return current == theMap->GetMap()->end();
		}

		virtual T CurrentItem() const
		{
			assert(!IsDone());

			return current->second;
		}

		string CurrentIndex() const
		{
			return current->first;
		}

	private:
		const SPStringMap<T>* theMap;
		typename map<string, T, IsLessString>::const_iterator current;
	};
}


