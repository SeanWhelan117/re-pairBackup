#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

/// @Author Michael R Ryan
/// @Date 01/02/2020

#include <SFML/Graphics.hpp>
#include "Config.h"

class CameraController
{
public:
	CameraController(sf::RenderWindow & t_window);

	void reset();

	void moveWindow(sf::Vector2f t_targetPos);

	void setSmoothness(sf::Vector2f t_smoothness);

private:
	sf::RenderWindow & m_windowRef;
	sf::View m_view;
	sf::Vector2f m_smoothness;

	const float m_WINDOW_BORDER{ 150.0f };
};

#endif // CAMERA_CONTROLLER_H