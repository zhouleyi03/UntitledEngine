#include "scene.h"

#include "quad_tree.h"

namespace Untitled
{
    Scene::Scene()
    {
        m_tree = new QuadTree();
    }

    Scene::~Scene()
    {
        delete m_tree;
    }

    std::size_t Scene::tick(float delta_time)
    {
        m_current_character->tick(delta_time);

        QuadTreeNode* node = m_tree->locate(m_current_character);

        QuadTreeNode* t1, * t2, * t3;
        switch (node->type)
        {
        case QuadTreeNodeType::TOP_LEFT:
            t1 = m_tree->locate(node->center_x, node->center_y + node->split_width)->parent;
            t2 = m_tree->locate(node->center_x - node->split_width, node->center_y)->parent;
            t3 = m_tree->locate(node->center_x - node->split_width, node->center_y + node->split_width);
            tickNode(t1->bottom_left, delta_time);
            tickNode(t1->bottom_right, delta_time);
            tickNode(t2->top_right, delta_time);
            tickNode(t2->bottom_right, delta_time);
            tickNode(t3, delta_time);
            break;
        case QuadTreeNodeType::TOP_RIGHT:
            t1 = m_tree->locate(node->center_x, node->center_y + node->split_width)->parent;
            t2 = m_tree->locate(node->center_x + node->split_width, node->center_y)->parent;
            t3 = m_tree->locate(node->center_x + node->split_width, node->center_y + node->split_width);
            tickNode(t1->bottom_left, delta_time);
            tickNode(t1->bottom_right, delta_time);
            tickNode(t2->top_left, delta_time);
            tickNode(t2->bottom_left, delta_time);
            tickNode(t3, delta_time);
            break;
        case QuadTreeNodeType::BOTTOM_LEFT:
            t1 = m_tree->locate(node->center_x - node->split_width, node->center_y)->parent;
            t2 = m_tree->locate(node->center_x, node->center_y - node->split_width)->parent;
            t3 = m_tree->locate(node->center_x - node->split_width, node->center_y - node->split_width);
            tickNode(t1->top_right, delta_time);
            tickNode(t1->bottom_right, delta_time);
            tickNode(t2->top_left, delta_time);
            tickNode(t2->top_right, delta_time);
            tickNode(t3, delta_time);
            break;
        case QuadTreeNodeType::BOTTOM_RIGHT:
            t1 = m_tree->locate(node->center_x + node->split_width, node->center_y)->parent;
            t2 = m_tree->locate(node->center_x, node->center_y - node->split_width)->parent;
            t3 = m_tree->locate(node->center_x + node->split_width, node->center_y - node->split_width);
            tickNode(t1->top_left, delta_time);
            tickNode(t1->bottom_left, delta_time);
            tickNode(t2->top_left, delta_time);
            tickNode(t2->top_right, delta_time);
            tickNode(t3, delta_time);
            break;
        }

        node = node->parent;
        tickNode(node->bottom_left, delta_time);
        tickNode(node->bottom_right, delta_time);
        tickNode(node->top_left, delta_time);
        tickNode(node->top_right, delta_time);

        return m_scene_id;
    }

    void Scene::tickNode(QuadTreeNode* node, float delta_time)
    {
        if (!node) return;
        for (auto& ent : node->m_data)
            ent->tick(delta_time);
    }

    void Scene::addEntity(Entity* entity)
    {
        m_tree->insert(entity);
    }

    void Scene::setCharacter(Character* character)
    {
        m_current_character = character;
    }
}
