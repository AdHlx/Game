#pragma once

#include "Fountainhead/Core/Core.h"
#include "Fountainhead/Core/Layer.h"

#include <vector>

namespace Fountainhead {
	//基本上是一个Layer向量的封装器
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//使用向量是因为每一帧都要遍历，而且也需要反向迭代，因为我们要反向传递事件，但是对于Update，我们总是需要正向遍历
		//之所以没有使用栈容器，是因为我们需要向中间插入，因为有覆层
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }//begin和end的迭代器实现，我们可以在App类中使用Range-For
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