#pragma once

#include "fhpch.h"

#include "Fountainhead/Core/Core.h"

namespace Fountainhead {

	//�����е��¼���ǰ��������״̬
	//����ζ�ŵ��¼�����ʱ�����������ɳ���������������
	//����δ�������õĲ��Կ��������¼��л����¼�
	//�ڸ��½׶εġ��¼������ֶ����ǽ������ߺʹ���

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};//ö�ٿ��ܵ��¼�����

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	 = BIT(0),
		EventCategoryInput			 = BIT(1),
		EventCategoryKeyboard		 = BIT(2),
		EventCategoryMouse			 = BIT(3),
		EventCategoryMouseButton	 = BIT(4)
	};//���¼����ͷ���

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

//static EventType GetStaticType() { return EventType::KeyPressed; }
//����ϣ������ʱ�������һ���¼����ͣ�����������Ҫһ�������¼����͵ĺ��������ǲ�����ʵ�����鿴�¼�����
//virtual EventType GetEventType() const override { return GetStaticType(); }
//������Ҫ����麯�������ɣ����ͨ��Event���ഫ�ݣ����Ƕ�̬�ģ�����ֻ��һ��Event�����û�ָ�룬����ϣ���ܹ���������ʵ������
//�������ǿ��Դ�Event.h��class FOUNTAINHEAD_API Event -> GetEventType()�����᷵��ʵ�ʵ��¼����͵�ID
//virtual const char* GetName() const override { return "KeyPressed"; }
//������������������ͨ��һ��EVENT_CLASS_TYPE������ʵ��
//�·���EVENT_CLASS_CATEGORYҲ��һ���ĵ���

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		bool Handled = false;//�Ƿ��ѱ�����Ĳ���ֵ����Ϊ����ϣ���ܹ��ڶ�Ӧ�Ĳ㴦���Ӧ��ʵ������ϣ�����¼�����������Ĳ�

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }//�����¼��Ļ���

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}//��ѯ����¼��Ƿ����ڸ��������ͣ�Ȼ�����ǿ���ʹ���������ٹ��˵�ĳЩ�¼�
	};

	class EventDispatcher//�¼�����������һ���������Ƿǳ����ɵĸ����¼����͵����¼��ķ�ʽ
	{
	public:
		//��������յ�һ���¼������Һ����������ˣ����ǻ��յ�һ��Event���ã�Ҳ����˵���������κ����͵��¼�������Ҫ֪����ʲô
		//���ǿ���ʹ�ý��յ����¼�������һ��������ʵ����Ȼ��ʹ��һ����ͬ���¼����������������Dispatch����
		EventDispatcher(Event& event)//Event���ã����������κ��¼������Ժ����ģ��������бȽ�
			: m_Event(event)
		{
		}
		
		template<typename T, typename F>
		bool Dispatch(const F& func)//��⵱ǰҪ���ȵ��¼������ͣ�����Ƿ�ƥ�����ģ�����
		{
			if (m_Event.GetEventType() == T::GetStaticType())//��������һ����̬����������ʹ��T::����ȡ��̬����
			{//������Ե��ȵ��¼������������ƥ�䣬���ͻ�������¼������������
				m_Event.Handled = func(*(T*)&m_Event);//���Ϊ�棬��ô���ȵ����ʵĺ���
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)//���������������������ǵ���־���У��������ɵĶ��¼�����ToString()���������ɵļ�¼�¼�
	{
		return os << e.ToString();
	}
}