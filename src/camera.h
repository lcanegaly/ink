#pragma once 
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
           float yaw = 90.0f, float pitch = 0.0f) 
        : Front(glm::vec3(0.0f, 0.0f, 1.0f)), 
          Position(position), 
          WorldUp(up), 
          Yaw(yaw), 
          Pitch(pitch) {
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void Rotate(float deltaYaw, float deltaPitch) {
        Yaw += deltaYaw;
        Pitch += deltaPitch;
        updateCameraVectors();
    }

    void Translate(const glm::vec3 &direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        Position += direction * velocity;
    }

private:
    float MovementSpeed = 1.0f;
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};

