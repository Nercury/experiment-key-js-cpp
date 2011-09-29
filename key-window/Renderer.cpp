#include "Renderer.h"

using namespace std;
using namespace key;

static std::map<std::string, std::shared_ptr<Renderer>> renderer_instances;

void Renderer::addRenderer(std::string identifier, std::shared_ptr<Renderer> instance) {
	renderer_instances.insert(std::pair<std::string, std::shared_ptr<Renderer>>(identifier, instance));
}

std::map<std::string, std::shared_ptr<Renderer>> Renderer::getRenderers() {
	return renderer_instances;
}