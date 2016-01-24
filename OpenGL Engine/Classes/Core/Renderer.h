#pragma once

#include "../Shader.h"
#include "../Camera.h"
#include "../GameObject.h"
#include "../RawModel.h"
#include "../TexturedModel.h"
#include <vector>

class Renderer {
private:
	Shader* shader;
	Camera* camera;

public:
	Renderer(Shader* shader, Camera* camera);
	void Draw(const std::vector<GameObject*>& objects);
};
