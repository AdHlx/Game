#include "fhpch.h"
#include "Fountainhead/Renderer/VertexArray.h"

#include "Fountainhead/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fountainhead {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    FH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		FH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}