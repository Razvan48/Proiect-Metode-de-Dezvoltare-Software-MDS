#pragma once

#include "../CollidableEntity.h"
#include "../TexturableEntity.h"

#include <map>

class Button : public virtual CollidableEntity, public virtual TexturableEntity
{
public:

	static enum class Status
	{
		DEFAULT = 0,
		HOVERED = 1,
		CLICKED = 2
	};

protected:

	std::string label;
	std::map<Button::Status, std::string> status_TextureNames;
	Status status = Button::Status::DEFAULT;

	void updateTexture();

public:

	Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<Button::Status, std::string>& status_TextureNames_, const std::string& label_ = "");
	Button();
	virtual ~Button();

	void onCollide(CollidableEntity& other, glm::vec2 overlap) override;
	void update() override;
	
	std::string getLabel() const { return label; }
	void setLabel(const std::string& label) { this->label = label; }

	void draw() override;

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	void setStatus(Button::Status st) { status = st; }
	Button::Status getStatus() const { return status; }

	void setDefault();
	void setHovered();
	void setClicked();

};