#pragma once
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtx/transform.hpp"
#include <iostream> 

class Transform {
public:
    glm::vec3 position;
    glm::vec3 rotation_axis;
    float angle;
    glm::vec3 scale;
    Transform* parent;
    Transform(Transform* parent = nullptr, glm::vec3 position = glm::vec3(0.0f), 
              glm::vec3 rotation_axis = glm::vec3(0.0f, 0.0f, 1.0f), float angle = 0.0,  
              glm::vec3 scale = glm::vec3(1.0f))
        : parent(parent), position(position), rotation_axis(rotation_axis), scale(scale) {}
    // Compute global transformation matrix
    glm::mat4 GlobalMatrix() const {
        glm::mat4 posMatrix = glm::translate(position);
        glm::mat4 scaleMatrix = glm::scale(scale);
        glm::mat4 rotMatrix = glm::rotate(angle, rotation_axis);
        glm::mat4 localMatrix = posMatrix * rotMatrix * scaleMatrix;
        if (parent) {
            return parent->GlobalMatrix() * localMatrix;
        }
        return localMatrix;
    }
};

