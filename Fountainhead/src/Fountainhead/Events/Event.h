#pragma once

#include "fhpch.h"

#include "Fountainhead/Core/Core.h"

namespace Fountainhead {

	//引擎中的事件当前处于阻塞状态
	//这意味着当事件发生时，它立即被派出，必须立即处理。
	//对于未来，更好的策略可能是在事件中缓冲事件
	//在更新阶段的“事件”部分对它们进行总线和处理。

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};//枚举可能的事件类型

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	 = BIT(0),
		EventCategoryInput			 = BIT(1),
		EventCategoryKeyboard		 = BIT(2),
		EventCategoryMouse			 = BIT(3),
		EventCategoryMouseButton	 = BIT(4)
	};//将事件类型分类

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

//static EventType GetStaticType() { return EventType::KeyPressed; }
//我们希望运行时检查是哪一种事件类型，所以我们需要一个返回事件类型的函数，我们不必有实例来查看事件类型
//virtual EventType GetEventType() const override { return GetStaticType(); }
//我们需要这个虚函数的理由，如果通过Event基类传递，它是多态的，我们只有一个Event的引用或指针，我们希望能够看到它的实际类型
//所以我们可以从Event.h的class FOUNTAINHEAD_API Event -> GetEventType()，它会返回实际的事件类型的ID
//virtual const char* GetName() const override { return "KeyPressed"; }
//以上三个函数都可以通过一个EVENT_CLASS_TYPE宏来简单实现
//下方的EVENT_CLASS_CATEGORY也是一样的道理

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		bool Handled = false;//是否已被处理的布尔值，因为我们希望能够在对应的层处理对应的实践，不希望将事件传播到更深的层

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }//所有事件的基类

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}//查询这个事件是否属于给定的类型，然后我们可以使用它来快速过滤掉某些事件
	};

	class EventDispatcher//事件调度器，是一种能让我们非常轻松的根据事件类型调度事件的方式
	{
	public:
		//如果我们收到一个事件，并且函数被调用了，我们会收到一个Event引用，也就是说它可以是任何类型的事件，不需要知道是什么
		//我们可以使用接收到的事件，创建一个调度器实例，然后使用一个不同的事件函数，调用下面的Dispatch函数
		EventDispatcher(Event& event)//Event引用，它可以是任何事件，可以和这个模板参数进行比较
			: m_Event(event)
		{
		}
		
		template<typename T, typename F>
		bool Dispatch(const F& func)//检测当前要调度的事件的类型，检测是否匹配这个模板参数
		{
			if (m_Event.GetEventType() == T::GetStaticType())//由于这是一个静态函数，我们使用T::来获取静态类型
			{//如果尝试调度的事件，与这个函数匹配，它就会用这个事件调用这个函数
				m_Event.Handled = func(*(T*)&m_Event);//如果为真，那么调度到合适的函数
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)//输出流运算符，存在于我们的日志库中，可以轻松的对事件调用ToString()，可以轻松的记录事件
	{
		return os << e.ToString();
	}
}