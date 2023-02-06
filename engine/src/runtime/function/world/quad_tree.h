#pragma once
#include <vector>
#include <iostream>

#include "function/entity/entity.h"

namespace Untitled
{
    enum class QuadTreeNodeType
    {
        ROOT,
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    struct QuadTreeNode
    {
        QuadTreeNode() = default;
        QuadTreeNode(const double& _center_x, const double& _center_y, const double& _split_width);
        double center_x = 0.0, center_y = 0.0, split_width = 0.0;
        QuadTreeNode* top_left = nullptr;
        QuadTreeNode* top_right = nullptr;
        QuadTreeNode* bottom_left = nullptr;
        QuadTreeNode* bottom_right = nullptr;
        QuadTreeNode* parent = nullptr;
        QuadTreeNodeType type = QuadTreeNodeType::ROOT;
        std::vector<Entity*> m_data;
    };

    class QuadTree
    {
    public:
        QuadTree();
        ~QuadTree();
        void insert(Entity* entity);
        void deleteNode(QuadTreeNode* node);
        QuadTreeNode* locate(Entity* entity);
        QuadTreeNode* locate(float x, float y);
    private:
        QuadTreeNode m_root;
        const double m_scale = 1024.0;
        const int m_max_depth = 8;
    };
}
