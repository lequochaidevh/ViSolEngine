#pragma once 
#include "core/logger/logger.h"
#include "pch.h"
#include "eventAction.h"

/*
	/3/
	Create EventDispatcher for 2 respone :
		i.Register or add eventCallback to List respective somthing of event
		ii.Excute all of eventCallback when event active 
*/
namespace ViSolEngine {
	/* Create EventActionList (vector) */
	using EventActionList = std::vector<IEventAction*>;
	using EventID = UUID;
	class VISOL_API EventDispatcher {
		friend class Application; // Spec only Application class which can create it
	public:
		~EventDispatcher();

		template<typename T>
		void addEventListener(const eventCallback<T>& callback) {
			VISOL_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Add invalid EventContext");
			EventID eventID = getTypeUUID<T>();
			CORE_LOG_DEBUG("Create event type: {0} - with ID: {1} ", typeid(T).name(), eventID);
			IEventAction* eventAction = new EventAction<T>(callback);
			mEventActionMap[eventID].emplace_back(eventAction);
		}

		template<typename T>
		void dispatchListener(const T& evenContext) {
			VISOL_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Dispatch invalid EventContext");
			EventID eventID = getTypeUUID<T>();
			VISOL_ASSERT(mEventActionMap.find(eventID) != mEventActionMap.end() && "Unknow event type");
			for (auto eventAction : mEventActionMap.at(eventID)) {
				if (eventAction->execute(&evenContext)) {
					break;
				}
			}
		}

	private:
		EventDispatcher();
		std::unordered_map<EventID, EventActionList> mEventActionMap;
	};
}