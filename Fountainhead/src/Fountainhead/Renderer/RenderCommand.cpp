#include "fhpch.h"
#include "Fountainhead/Renderer/RenderCommand.h"

namespace Fountainhead {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();//指定使用哪一个API

}