#pragma once
#include <list>
#include <algorithm>
#include "SPPointer.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief template class SPComposite to represent a Composite pattern.
	//////////////////////////////////////////////////////////////////////
	template <typename Component>
	class SPComposite : public Component
	{		
	protected:
		typedef SPPointer<Component> ComponentPtr;
		typedef list<ComponentPtr> Children;
		typedef	typename Children::iterator ChildIterator;

		Children children; ///< Children component list;

	public:
		virtual bool AddChild(ComponentPtr newChild)
		{
			ChildIterator iter = find(children.begin(), children.end(), newChild);

			if( iter == children.end())
			{
				children.push_back(newChild);
				return true;
			}

			return false;;
		}

		virtual bool RemoveChild(ComponentPtr child)
		{
			ChildIterator iter = find(children.begin(), children.end(), child);

			if( iter != children.end())
			{
				children.erase(iter);
				return true;
			}

			return false;
		}

		virtual bool Clear()
		{
			children.clear();
			return true;
		}
	};
}


