#pragma once

enum class EntityStatus
{
	DEFAULT, //asta doar debug, NU FOLOSIM DEFAULT, FOLOSIM IDLE PENTRU STATUS DE INCEPUT
	IDLE,
	Walking,
	Running,
	TIRED,
	DYING,
	HOVERED,
	CLICKED
};