#pragma once
#include "function/entity/entity.h"
#include "function/entity/character.h"

namespace Untitled
{
    class QuadTree;
    class QuadTreeNode;

    class Scene
    {
    public:
        Scene();
        ~Scene();
        std::size_t tick(float delta_time);
        void tickNode(QuadTreeNode* node, float delta_time);
        void addEntity(Entity* entity);
        void setCharacter(Character* character);
    private:
        Character* m_current_character = nullptr;
        QuadTree* m_tree;
        std::size_t m_scene_id = 0;
    };
}
