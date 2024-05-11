#pragma once

#include "../Human/Human.h"
#include "../Weapon/Weapon.h"

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <memory>

class Player : public virtual Human // singleton
{
private:

	Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses, double runningSpeed, double health, double stamina, double armor);
	virtual ~Player();

	Player(const Player& other) = delete;
	Player& operator= (const Player& other) = delete;
	Player(const Player&& other) = delete;
	Player& operator= (const Player&& other) = delete;

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void run();
	void interact();
	void moveUpReleased();
	void moveDownReleased();
	void moveRightReleased();
	void moveLeftReleased();
	void runReleased();
	void interactReleased();

	void look(double xpos, double ypos);

	void shoot();
	void reload();

	void pauseGame();

	void weaponSlot1();
	void weaponSlot2();
	void weaponSlot3();
	void weaponSlot4();
	void weaponSlot5();
	void weaponSlot6();

	double runningSpeed;

	double armor;
	double armorCap;

	double stamina;
	double staminaChangeSpeed;
	double staminaCap;

	int gold;
	const int goldCap;

	bool moveUpUsed;
	bool moveDownUsed;
	bool moveRightUsed;
	bool moveLeftUsed;
	bool runUsed;
	bool interactUsed;

	double walkingOffsetSize;
	double runningOffsetSize;
	double walkingOffsetSpeed;
	double runningOffsetSpeed;

	std::vector<std::shared_ptr<Weapon>> weapons;

	int currentWeaponIndex;

public:

	static Player& get();

	void onCollide(CollidableEntity& other, glm::vec2 overlap) override;

	void update() override;

	void setupPlayerInputComponent();

	inline double getStamina() const { return this->stamina; }
	inline double getStaminaCap() const { return this->staminaCap; }
	inline double getArmor() const { return this->armor; }
	inline double getArmorCap() const { return this->armorCap; }
	inline int getGold() const { return this->gold; }
	inline int getGoldCap() const { return this->goldCap; }

	inline void setGold(int gold) { this->gold = gold; }

	inline bool getInteractUsed() const { return this->interactUsed; }

	inline std::string getCurrentWeaponTexture() const { return this->weapons[this->currentWeaponIndex]->getTextureName2D(); }

	void draw() override;

	void save();
	void load();
};

