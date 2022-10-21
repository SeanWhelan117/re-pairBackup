#include "../include/CameraController.h"

/// @Author Michael R Ryan
/// @Date 01/02/2020

CameraController::CameraController(sf::RenderWindow & t_window) :
	m_windowRef{ t_window },
	m_view{ t_window.getDefaultView() },
	m_smoothness{ 40.0f, 20.0f }
{
}

///////////////////////////////////////////////////////////////////////////////
void CameraController::reset()
{
	m_view = m_windowRef.getView();
	m_view.setCenter(m_view.getSize() / 2.0f);
	m_windowRef.setView(m_view);
}

///////////////////////////////////////////////////////////////////////////////
void CameraController::moveWindow(sf::Vector2f t_targetPos)
{
	sf::Vector2f distanceVec = t_targetPos - m_view.getCenter();
	m_view.setCenter(m_view.getCenter().x + (distanceVec.x / m_smoothness.x), m_view.getCenter().y + (distanceVec.y / m_smoothness.y));

	// Horisontal
	if (m_view.getCenter().x + (m_view.getSize().x / 2.0f) > GAME_WIDTH + m_WINDOW_BORDER)
	{
		m_view.setCenter(GAME_WIDTH - (m_view.getSize().x / 2.0f) + m_WINDOW_BORDER, m_view.getCenter().y);
	}

	if (m_view.getCenter().x - (m_view.getSize().x / 2.0f) < -m_WINDOW_BORDER)
	{
		m_view.setCenter(m_view.getSize().x / 2.0f - m_WINDOW_BORDER, m_view.getCenter().y);
	}

	// Vertical
	if (m_view.getCenter().y + (m_view.getSize().y / 2.0f) > GAME_HEIGHT + m_WINDOW_BORDER)
	{
		m_view.setCenter(m_view.getCenter().x, GAME_HEIGHT - (m_view.getSize().y / 2.0f) + m_WINDOW_BORDER);
	}

	if (m_view.getCenter().y - (m_view.getSize().y / 2.0f) < -m_WINDOW_BORDER)
	{
		m_view.setCenter(m_view.getCenter().x, (m_view.getSize().y / 2.0f) - m_WINDOW_BORDER);
	}

	m_windowRef.setView(m_view);
}

///////////////////////////////////////////////////////////////////////////////
void CameraController::setSmoothness(sf::Vector2f t_smoothness)
{
	m_smoothness = t_smoothness;
}

///////////////////////////////////////////////////////////////////////////////