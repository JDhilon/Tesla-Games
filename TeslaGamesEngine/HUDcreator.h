#pragma once

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include "Global.h"
#include "HUD.h"
#include "Window.h"
#include "Texture.h"
#include "Shader.h"

class HUDcreator
{
public:
	HUDcreator() = default;

	void loadHUD();
	void loadTextures();
	void use();
	void setSize(float size) { size = size; };
	void load();
	void loadShader();

	void setLapNumber(int lap);
	void setAbilityNumber(int ability);
	void setAliveNumber(int alive);
	void setPositionNumber(int position);
	void setGameState(bool isPlayer);
	void setBulletNum(int bullet);
	void setHealth(float health) { currentHealth = health; };
	void setDisabled(bool isDisabled);
	void setSmoked(bool affectedBySmoke) { isSmoked = affectedBySmoke; };
	void setOiled(bool affectedByOil) { isOiled = affectedByOil; }
	void resetWinOrLose() { winOrLose = false; };
	void reset();
	
private:
	int id;
	float size = 1.0f;										//HUD size
	bool winOrLose = false;									//is someone finshed laps?
	float currentHealth = 100;
	bool isSmoked = false;
	bool isOiled = false;

	std::vector<HUD*> HUDList;
	std::vector<Texture> TextureList;

	Shader hudShader;

	unsigned int HUDindices[6] = {							// 0 -----3
			0, 1, 3,										// |	  |
			2, 1, 3											// 1 -----2
	};

	//digit textures
	Texture dig0Texture;
	Texture dig1Texture;
	Texture dig2Texture;
	Texture dig3Texture;
	Texture dig4Texture;
	Texture dig5Texture;
	Texture dig6Texture;
	Texture dig7Texture;
	Texture dig8Texture;
	Texture dig9Texture;

	//HUD textures
	Texture weaponUITexture;
	Texture outOfWeaponTexture;
	Texture emptyBarTexture;
	Texture healthBarTexture;
	Texture nitroBarTexture;
	Texture plusSymbolTexture;
	Texture nitroSymbolTexture;
	Texture flagTexture;
	Texture personTexture;
	Texture cupTexture;
	Texture winTexture;
	Texture loseTexture;
	Texture outOfBulletTexture;
	Texture bulletSymbolTexture;
	Texture smokedTexture;
	Texture oiledTexture;

	Texture abilityNum;
	Texture weaponTexture;
	Texture gameState;
	Texture bulletTexture;

	Texture lapNum1;
	Texture lapNum2;
	Texture aliveNum1;
	Texture aliveNum2;
	Texture posNum1;
	Texture posNum2;
	Texture slashTexture;
	Texture bulletNum1;
	Texture bulletNum2;

	//Empty texture
	Texture emptyTexture;

	// Vertex Shader of HUD_shader
	const char* vHshader = "Shaders/HUD_shader.vert";

	//Fragment shader of HUD_shader
	const char* fHshader = "Shaders/HUD_shader.frag";

	GLfloat weaponUIVertices[20] = {
		//	x									y										z		u	 v
			0.0f / 1600 * mainWindow.getWidth() * size, 720.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,	0.0f, 0.0f,								//bottom left
			0.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,								//top left
			370.0f / 1600 * mainWindow.getWidth() * size, 900 / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,								//top right
			370.0f / 1600 * mainWindow.getWidth() * size, 720.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,	1.0f, 0.0f								//bottom right
	};


	GLfloat numOfWeaponVertices[20] = {
		177.5f / 1600 * mainWindow.getWidth() * size, 770 / 900.0f * mainWindow.getHeight() * size, 1.0f,		0.0f, 0.0f,
		177.5f / 1600 * mainWindow.getWidth() * size, 800 / 900.0f * mainWindow.getHeight() * size, 1.0f,		0.0f, 1.0f,
		192.5f / 1600 * mainWindow.getWidth() * size, 800 / 900.0f * mainWindow.getHeight() * size, 1.0f,		1.0f, 1.0f,
		192.5f / 1600 * mainWindow.getWidth() * size, 770 / 900.0f * mainWindow.getHeight() * size, 1.0f,		1.0f, 0.0f
	};
	
	GLfloat emptyBar1Vertices[20] = {
		1200.0f / 1600 * mainWindow.getWidth() * size, 870.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1200.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1600.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1600.0f / 1600 * mainWindow.getWidth() * size, 870.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};
	
	GLfloat emptyBar2Vertices[20] = {
		0.0f / 1600 * mainWindow.getWidth() * size, 870.0f / 900.0f * mainWindow.getHeight() * size, 1.0f,		0.0f, 0.0f,
		0.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 1.0f,		0.0f, 1.0f,
		400.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 1.0f,		1.0f, 1.0f,
		400.0f / 1600 * mainWindow.getWidth() * size, 870.0f / 900.0f * mainWindow.getHeight() * size, 1.0f,		1.0f, 0.0f
	};

	GLfloat plusVertices[20] = {
		1160.0f / 1600 * mainWindow.getWidth() * size, 870.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1160.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1190.0f / 1600 * mainWindow.getWidth() * size, 900.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1190.0f / 1600 * mainWindow.getWidth() * size, 870.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat nitroSymbolVertices[20] = {
		1270.0f / 1600 * mainWindow.getWidth() * size, 855.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1270.0f / 1600 * mainWindow.getWidth() * size, 875.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1290.0f / 1600 * mainWindow.getWidth() * size, 875.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1290.0f / 1600 * mainWindow.getWidth() * size, 855.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat cupVertices[20] = {
		1200.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1200.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1230.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1230.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat rank1numVertices[20] = {
		1240.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1240.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1255.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1255.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat rank2numVertices[20] = {
		1260.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1260.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1275.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1275.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat totalRank1Vertices[20] = {
		1300.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1300.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1315.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1315.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat totalRank2Vertices[20] = {
		1320.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1320.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1335.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1335.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat rankSlashVertices[20] = {
		1280.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1280.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1295.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1295.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat flagVertices[20] = {
		1465.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1465.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1495.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1495.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat lap1numVertices[20] = {
		1500.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1500.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1515.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1515.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat lap2numVertices[20] = {
		1520.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1520.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1535.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1535.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat totalLap1Vertices [20] = {
		1560.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1560.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1575.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1575.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat totalLap2Vertices[20] = {
		1580.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1580.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1595.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1595.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat lapSlashVertices[20] = {
		1540.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1540.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1555.0f / 1600 * mainWindow.getWidth() * size, 865.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1555.0f / 1600 * mainWindow.getWidth() * size, 835.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat personVertices[20] = {
		1430.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1430.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1470.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1470.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat alive1numVertices[20] = {
		1475.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1475.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1495.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1495.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat alive2numVertices[20] = {
		1500.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1500.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1520.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1520.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat totalAlive1Vertices[20] = {
		1550.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1550.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1570.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1570.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat totalAlive2Vertices[20] = {
		1575.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1575.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1595.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1595.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat aliveSlashVertices[20] = {
		1525.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1525.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1545.0f / 1600 * mainWindow.getWidth() * size, 150.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1545.0f / 1600 * mainWindow.getWidth() * size, 110.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat gameStateVertices[20] = {
		350.f / 1600.f * mainWindow.getWidth() * size, 0.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f ,0.f,
		350.f / 1600.f * mainWindow.getWidth() * size, 900.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f, 1.f,
		1250.f / 1600.f * mainWindow.getWidth() * size, 900.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 1.f,
		1250.f / 1600.f * mainWindow.getWidth() * size, 0.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 0.f
	};

	GLfloat bulletVertices[20] = {
		10.f / 1600.f * mainWindow.getWidth() * size, 650.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f ,0.f,
		10.f / 1600.f * mainWindow.getWidth() * size, 710.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f, 1.f,
		47.6f / 1600.f * mainWindow.getWidth() * size, 710.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 1.f,
		47.6f / 1600.f * mainWindow.getWidth() * size, 650.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 0.f
	};
	
	GLfloat bulletNum1Vertices[20] = {
		140.f / 1600.f * mainWindow.getWidth() * size, 650.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f ,0.f,
		140.f / 1600.f * mainWindow.getWidth() * size, 710.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f, 1.f,
		170.f / 1600.f * mainWindow.getWidth() * size, 710.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 1.f,
		170.f / 1600.f * mainWindow.getWidth() * size, 650.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 0.f
	};

	GLfloat bulletNum2Vertices[20] = {
		180.f / 1600.f * mainWindow.getWidth() * size, 650.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f ,0.f,
		180.f / 1600.f * mainWindow.getWidth() * size, 710.f / 900.f * mainWindow.getHeight() * size, 0.f,			0.f, 1.f,
		210.f / 1600.f * mainWindow.getWidth() * size, 710.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 1.f,
		210.f / 1600.f * mainWindow.getWidth() * size, 650.f / 900.f * mainWindow.getHeight() * size, 0.f,			1.f, 0.f
	};

	GLfloat smokedVertices[20] = {
		1300.0f / 1600 * mainWindow.getWidth() * size, 720.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1300.0f / 1600 * mainWindow.getWidth() * size, 820.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1400.0f / 1600 * mainWindow.getWidth() * size, 820.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1400.0f / 1600 * mainWindow.getWidth() * size, 720.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};

	GLfloat oiledVertices[20] = {
		1450.0f / 1600 * mainWindow.getWidth() * size, 720.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 0.0f,
		1450.0f / 1600 * mainWindow.getWidth() * size, 820.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		0.0f, 1.0f,
		1550.0f / 1600 * mainWindow.getWidth() * size, 820.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 1.0f,
		1550.0f / 1600 * mainWindow.getWidth() * size, 720.0f / 900.0f * mainWindow.getHeight() * size, 0.0f,		1.0f, 0.0f
	};
};

