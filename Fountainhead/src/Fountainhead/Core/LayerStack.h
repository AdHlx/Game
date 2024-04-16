#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Layer.h"

#include <vector>

namespace Fountainhead {
	//��������һ��Layer�����ķ�װ��
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//ʹ����������Ϊÿһ֡��Ҫ����������Ҳ��Ҫ�����������Ϊ����Ҫ���򴫵��¼������Ƕ���Update������������Ҫ�������
		//֮����û��ʹ��ջ����������Ϊ������Ҫ���м���룬��Ϊ�и���
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }//begin��end�ĵ�����ʵ�֣����ǿ�����App����ʹ��Range-For
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}