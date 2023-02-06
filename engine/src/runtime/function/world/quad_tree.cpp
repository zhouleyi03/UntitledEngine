#include "quad_tree.h"

namespace Untitled
{
    QuadTreeNode::QuadTreeNode(const double& _center_x,
        const double& _center_y, const double& _split_width)
        :center_x(_center_x), center_y(_center_y), split_width(_split_width)
    {
    }

    QuadTree::QuadTree()
    {
        m_root.center_x = m_scale / 2.0;
        m_root.center_y = m_scale / 2.0;
        m_root.split_width = m_scale;
    }

    QuadTree::~QuadTree()
    {
        deleteNode(m_root.top_left);
        deleteNode(m_root.top_right);
        deleteNode(m_root.bottom_left);
        deleteNode(m_root.bottom_right);
    }

    void QuadTree::insert(Entity* entity)
    {
        locate(entity)->m_data.push_back(entity);
    }

    void QuadTree::deleteNode(QuadTreeNode* node)
    {
        if (!node) return;
        deleteNode(node->bottom_left);
        deleteNode(node->bottom_right);
        deleteNode(node->top_left);
        deleteNode(node->top_right);
        delete node;
    }

    QuadTreeNode* QuadTree::locate(Entity* entity)
    {
        auto node = &m_root;
        int depth = 0;
        double new_split_width, new_center_offset;
        while (depth++ < m_max_depth)
        {
            new_split_width = node->split_width / 2.0;
            new_center_offset = new_split_width / 2.0;
            if (entity->m_pos.x > node->center_x)
            {
                if (entity->m_pos.y > node->center_y)
                {
                    if (!node->top_right)
                    {
                        node->top_right =
                            new QuadTreeNode(
                                node->center_x + new_center_offset,
                                node->center_y + new_center_offset,
                                new_split_width);
                        node->top_right->parent = node;
                        node->top_right->type = QuadTreeNodeType::TOP_RIGHT;
                    }
                    node = node->top_right;
                }
                else
                {
                    if (!node->bottom_right)
                    {
                        node->bottom_right =
                            new QuadTreeNode(
                                node->center_x + new_center_offset,
                                node->center_y - new_center_offset,
                                new_split_width);
                        node->bottom_right->parent = node;
                        node->bottom_right->type = QuadTreeNodeType::BOTTOM_RIGHT;
                    }
                    node = node->bottom_right;
                }
            }
            else // entity->m_pos.x <= node->center_x
            {
                if (entity->m_pos.y > node->center_y)
                {
                    if (!node->top_left)
                    {
                        node->top_left =
                            new QuadTreeNode(
                                node->center_x - new_center_offset,
                                node->center_y + new_center_offset,
                                new_split_width);
                        node->top_left->parent = node;
                        node->top_left->type = QuadTreeNodeType::TOP_LEFT;
                    }
                    node = node->top_left;
                }
                else
                {
                    if (!node->bottom_left)
                    {
                        node->bottom_left =
                            new QuadTreeNode(
                                node->center_x - new_center_offset,
                                node->center_y - new_center_offset,
                                new_split_width);
                        node->bottom_left->parent = node;
                        node->bottom_left->type = QuadTreeNodeType::BOTTOM_LEFT;
                    }
                    node = node->bottom_left;
                }
            }
        }
        return node;
    }

    QuadTreeNode* QuadTree::locate(float x, float y)
    {
        Entity tmp(0, 0, x, y, 0, 0, 0); // dummy entity
        return locate(&tmp);
    }
}
