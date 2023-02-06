#pragma once
#include <queue>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "function/entity/entity_wrapper.h"

namespace Untitled
{
	class Entity;
	class EntityWrapper;
	class ObjectPool;

	using UID = unsigned;

	class RenderSystem
	{
	public:
		RenderSystem();
		void initEX();
		void tick(float delta_time);
		void drawEntity(Entity* entity);
		void registerToUpdateQueue(Entity* entity);

		void updateProjectionMatrix(int width, int height);
	private:
		std::priority_queue<EntityWrapper> m_entity_update_queue;
		std::shared_ptr<ObjectPool> m_object_pool;

		unsigned m_VAO, m_VBO;
		unsigned m_pp_framebuffer, m_texture_color_buffer,
			m_rbo, m_scr_VAO, m_scr_VBO;
		UID m_pp_shader;
		glm::mat4 m_projection;

		int m_test_counter = 0;
	};
}