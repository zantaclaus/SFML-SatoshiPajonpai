#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = int(texture->getSize().x / float(imageCount.x));
	uvRect.height = int(texture->getSize().y / float(imageCount.y));
}

Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;


	uvRect.left = currentImage.x * abs(uvRect.width);
	uvRect.width = abs(uvRect.width);
}