#include "../include/Person.h"

///////////////////////////////////////////////////////////////////////////////
Person::Person(sf::Texture const& t_spriteSheetTexture, int t_animIntervalMS) :
    m_animIntervalMS{ t_animIntervalMS }
{
    m_boundingBox.setFillColor(sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) });
    m_boundingBox.setPosition((GAME_WIDTH / 2.0f) - (getSize().x / 2.0f), (GAME_HEIGHT / 2.0f) - (getSize().y / 2.0f));
    m_boundingBox.setSize({ 30.0f, 60.0f });

    setupSprites(t_spriteSheetTexture);
}

///////////////////////////////////////////////////////////////////////////////
Person::Person(sf::Texture const& t_spriteSheetTexture, int t_animIntervalMS, float const t_x, float const t_y) :
    m_animIntervalMS{ t_animIntervalMS }
{
    m_boundingBox.setFillColor(sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) });
    m_boundingBox.setPosition(t_x, t_y);
    m_boundingBox.setSize({ 30.0f, 60.0f });

    setupSprites(t_spriteSheetTexture);
}

///////////////////////////////////////////////////////////////////////////////
void Person::setupSprites(sf::Texture const& t_spriteSheetTexture)
{
    m_fullSprite.setTexture(t_spriteSheetTexture);
    m_hairSprite.setTexture(t_spriteSheetTexture);
    m_shirtSprite.setTexture(t_spriteSheetTexture);
    m_trousersSprite.setTexture(t_spriteSheetTexture);

    m_fullSprite.setTextureRect({ 0, 0, 8, 16 });
    m_hairSprite.setTextureRect({ 0, 16, 8, 16 });
    m_shirtSprite.setTextureRect({ 0, 32, 8, 16 });
    m_trousersSprite.setTextureRect({ 0, 48, 8, 16 });

    m_fullSprite.setOrigin(4.0f,0.0f);
    m_hairSprite.setOrigin(4.0f, 0.0f);
    m_shirtSprite.setOrigin(4.0f, 0.0f);
    m_trousersSprite.setOrigin(4.0f, 0.0f);

    m_fullSprite.setScale(m_SCALE, m_SCALE);
    m_hairSprite.setScale(m_SCALE, m_SCALE);
    m_shirtSprite.setScale(m_SCALE, m_SCALE);
    m_trousersSprite.setScale(m_SCALE, m_SCALE);

    //m_fullSprite.setColor(sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) });
    m_hairSprite.setColor(sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) });
    m_shirtSprite.setColor(sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) });
    m_trousersSprite.setColor(sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) });
}

///////////////////////////////////////////////////////////////////////////////
void Person::move(float t_x, float t_y)
{
    m_boundingBox.move(t_x, t_y);

    animateMovement({ t_x, t_y });
}

///////////////////////////////////////////////////////////////////////////////
void Person::move(sf::Vector2f t_vector)
{
    m_boundingBox.move(t_vector);

    animateMovement(t_vector);
}

///////////////////////////////////////////////////////////////////////////////
void Person::animateMovement(sf::Vector2f t_movementVector)
{
    m_fullSprite.setPosition(m_boundingBox.getPosition().x + 4.0f, m_boundingBox.getPosition().y);
    m_hairSprite.setPosition(m_boundingBox.getPosition().x + 4.0f, m_boundingBox.getPosition().y);
    m_shirtSprite.setPosition(m_boundingBox.getPosition().x + 4.0f, m_boundingBox.getPosition().y);
    m_trousersSprite.setPosition(m_boundingBox.getPosition().x + 4.0f, m_boundingBox.getPosition().y);

    if (fabsf(t_movementVector.x) > fabsf(t_movementVector.y))
    {
        m_frameIndex = 4;

        if (t_movementVector.x > 0)
        {
            setScale(m_SCALE, m_SCALE);
        }
        else
        {
            setScale(-m_SCALE, m_SCALE);
        }
    }
    else
    {
        setScale(m_SCALE, m_SCALE);

        if (t_movementVector.y > 0)
        {
            m_frameIndex = 2;
        }
        else
        {
            m_frameIndex = 6;
        }
    }

    int currentFrame = m_frameIndex;

    if (static_cast<int>(m_animationTimer.getElapsedTime().asMilliseconds()) % m_animIntervalMS > m_animIntervalMS / 2)
    {
        currentFrame++;
    }

    m_fullSprite.setTextureRect({ 8 * currentFrame, 0, 8, 16 });
    m_hairSprite.setTextureRect({ 8 * currentFrame, 16, 8, 16 });
    m_shirtSprite.setTextureRect({ 8 * currentFrame, 32, 8, 16 });
    m_trousersSprite.setTextureRect({ 8 * currentFrame, 48, 8, 16 });
}

///////////////////////////////////////////////////////////////////////////////
void Person::setScale(float t_scaleX, float t_scaleY)
{
    m_fullSprite.setScale(t_scaleX, t_scaleY);
    m_hairSprite.setScale(t_scaleX, t_scaleY);
    m_shirtSprite.setScale(t_scaleX, t_scaleY);
    m_trousersSprite.setScale(t_scaleX, t_scaleY);
}

///////////////////////////////////////////////////////////////////////////////
const sf::Vector2f Person::getPosition() const
{
	return m_boundingBox.getPosition();
}

///////////////////////////////////////////////////////////////////////////////
void Person::setPosition(float t_x, float t_y)
{
    m_boundingBox.setPosition(t_x, t_y);

    m_fullSprite.setPosition(m_boundingBox.getPosition());
    m_hairSprite.setPosition(m_boundingBox.getPosition());
    m_shirtSprite.setPosition(m_boundingBox.getPosition());
    m_trousersSprite.setPosition(m_boundingBox.getPosition());
}

///////////////////////////////////////////////////////////////////////////////
const sf::Vector2f Person::getSize() const
{
    return { m_boundingBox.getGlobalBounds().width, m_boundingBox.getGlobalBounds().height };
}

///////////////////////////////////////////////////////////////////////////////
void Person::setFillColor(sf::Color t_hairColor, sf::Color t_shirtColor, sf::Color t_trousersColor)
{
    m_hairSprite.setColor(t_hairColor);
    m_shirtSprite.setColor(t_shirtColor);
    m_trousersSprite.setColor(t_trousersColor);
}

///////////////////////////////////////////////////////////////////////////////
sf::Color Person::getFillColor()
{
    return m_boundingBox.getFillColor();
}

///////////////////////////////////////////////////////////////////////////////
sf::Color Person::getHairColor()
{
    return m_hairSprite.getColor();
}

///////////////////////////////////////////////////////////////////////////////
sf::Color Person::getShirtColor()
{
    return m_shirtSprite.getColor();
}

///////////////////////////////////////////////////////////////////////////////
sf::Color Person::getTrousersColor()
{
    return m_trousersSprite.getColor();
}

///////////////////////////////////////////////////////////////////////////////
const int Person::getFrameIndex() const
{
    return m_frameIndex;
}

///////////////////////////////////////////////////////////////////////////////
void Person::setFrameIndex(int const t_index)
{
    m_frameIndex = t_index;

    m_fullSprite.setTextureRect({ 8 * m_frameIndex, 0, 8, 16 });
    m_hairSprite.setTextureRect({ 8 * m_frameIndex, 16, 8, 16 });
    m_shirtSprite.setTextureRect({ 8 * m_frameIndex, 32, 8, 16 });
    m_trousersSprite.setTextureRect({ 8 * m_frameIndex, 48, 8, 16 });
}

///////////////////////////////////////////////////////////////////////////////
void Person::setAnimationInterval(int t_milliseconds)
{
    m_animIntervalMS = t_milliseconds;
}

///////////////////////////////////////////////////////////////////////////////
void Person::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    //target.draw(m_boundingBox, states);

    target.draw(m_fullSprite, states);
    target.draw(m_hairSprite, states);
    target.draw(m_shirtSprite, states);
    target.draw(m_trousersSprite, states);
}
