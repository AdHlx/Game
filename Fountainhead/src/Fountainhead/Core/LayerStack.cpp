#include "fhpch.h"
#include "Fountainhead/Core/LayerStack.h"

namespace Fountainhead {
	//һ���Ѳ㽻����ջ���ͱ���ջ���У����Ե��Ѳ�ָ���Ƹ���ջʱ����ջ�Ѳ����뵽��ȷ��λ��
	//����ջ����ʱ���㶼���ͷ�

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);//�㱻�����б�ǰ�벿��
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);//���㱻�����б��벿��
	}
	//������ʱ���ᱻ�ͷţ�ֻ�����ٲ�ʱ�Żᣬ��ջ������Ȩ��Ӧ�ó���(Application)������ζ�ſ��Է���㣬ֻҪ�Ѳ㴫����ջ���Ҳ������㣬��ͻ��ڳ���ر�ʱ�ͷ�
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}