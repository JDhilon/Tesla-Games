// TeslaGamesEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
// The TeslaGamesEngine will be changed to a .lib, not .exe and then be included in the TeslaGames Project

#include "pch.h"
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

// Rendering includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Model.h"


//Health stuff
#include "Combat.h"
#include "HealthComponent.h"
#include "DamagingObject.h"
#include "Vehicle.h"
#include "Game.h"

//AudioStuff
#include "AudioEngine.h"
#include "AudioBoomBox.h"

//Controller stuff
#include "Controller.h"

//PhysX and Physics Engine
#include "PhysicsEngine.h"

//HUD stuff
#include "HUD.h"

// Stuff for imgui
#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"

// end of stuff for imgui



/* Rendering variables */
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
std::vector<HUD*> HUDList;
Camera camera;

Shader hudShader;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture TTexture;
Texture meterTexture;
Texture dig1Texture;
Texture healthTexture;

Material shinyMaterial;
Material dullMaterial;

PhysicsEngine physEng;

Model xwing;
Model boxTest;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

// Vertex Shader of HUD_shader
static const char* vHshader = "Shaders/HUD_shader.vert";

//Fragment shader of HUD_shader
static const char* fHshader = "Shaders/HUD_shader.frag";

/* End of rendering variables */

// function for interpolating normals of a mesh
void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

// create basic objects for testing
void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
	
	hudShader.createHUDFromFiles(vHshader, fHshader);

}

void CreateHUDs() {
	unsigned int HUDindecis[] = {						// 0 -----3
		0, 1, 3,										// |	  |
		2, 1, 3											// 1 -----2
	};

	GLfloat HUDvertices[] = {
	//	x	 y	  z			u	 v
		0.0, 450.0, 0.0,	0.0, 0.0,								//bottom left
		0.0, 600.0, 0.0,	0.0, 1.0,								//top left
		150.0, 600, 0.0,	1.0, 1.0,								//top right
		150.0, 450.0, 0.0,	1.0, 0.0								//bottom right
	};
	
	unsigned int HUD1indecis[] = {						// 0 -----3
		0, 1, 3,										// |	  |
		2, 1, 3											// 1 -----2
	};

	
	GLfloat firstDigtVertices[] = {
		30.0, 505.0, 1.0,	0.0, 0.0,
		30.0, 555.0, 1.0,	0.0, 1.0,
		55.0, 555.0, 1.0,	1.0, 1.0,
		55.0, 505.0, 1.0,	1.0, 0.0
	};

	GLfloat secondDigVertices[]{
		60.0, 505.0, 1.0,	0.0, 0.0,
		60.0, 555.0, 1.0,	0.0, 1.0,
		85.0, 555.0, 1.0,	1.0, 1.0,
		85.0, 505.0, 1.0,	1.0, 0.0
	};	
	
	GLfloat thirdDigVertices[]{
		90.0, 505.0, 1.0,	0.0, 0.0,
		90.0, 555.0, 1.0,	0.0, 1.0,
		115.0, 555.0, 1.0,	1.0, 1.0,
		115.0, 505.0, 1.0,	1.0, 0.0
	};

	GLfloat healthBarVertices[]{
		0.0, 430, 0.0,		0.0, 0.0,
		0.0, 450, 0.0,		0.0, 1.0,
		150.0, 450.0, 0.0,	1.0, 1.0,
		150.0, 430.0, 0.0,	1.0, 0.0
	};

	HUD* HUD1 = new HUD();
	HUD1->createHUD(HUDvertices, HUDindecis, 20, 6);
	HUDList.push_back(HUD1);

	HUD* HUD2 = new HUD();
	HUD2->createHUD(firstDigtVertices, HUD1indecis, 20, 6);
	HUDList.push_back(HUD2);

	HUD* HUD3 = new HUD();
	HUD3->createHUD(secondDigVertices, HUD1indecis, 20, 6);
	HUDList.push_back(HUD3);	
	
	HUD* HUD4 = new HUD();
	HUD4->createHUD(thirdDigVertices, HUD1indecis, 20, 6);
	HUDList.push_back(HUD4);
	
	HUD* HUD5 = new HUD();
	HUD5->createHUD(healthBarVertices, HUD1indecis, 20, 6);
	HUDList.push_back(HUD5);
}

// A function to obtain input, called each frame
//add vehicle movement to these FOR NOW
//TO DO: Someone comment all the controls for each button
void parseControllerInput(Controller* controller)
{
	// Update controller object with current input MUST BE FIRST
	controller->update();

	//IMPLEMENT THINGS In the IFs

	//Is button Pressed demo
	if (controller->isButtonPressed(XButtons.A)) {
		std::cout << controller->getIndex() << " " <<"A PRESSED" << std::endl;
	}
	if (controller->isButtonPressed(XButtons.X)) {
		std::cout << controller->getIndex() << " " << "X PRESSED" << std::endl;
	}
	
	//Is button down demo (more useful IMO)
	if (controller->isButtonDown(XButtons.Y)) {
		std::cout << controller->getIndex() << " " << "Y PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.B)) {
		std::cout << controller->getIndex() << " " << "B PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.L_Shoulder)) {
		std::cout << controller->getIndex() << " " << "LB PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.R_Shoulder)) {
		std::cout << controller->getIndex() << " " << "RB PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Up)) {
		std::cout << controller->getIndex() << " " << "D-Pad Up PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Down)) {
		std::cout << controller->getIndex() << " " << "D-Pad Down PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Right)) {
		std::cout << controller->getIndex() << " " << "D-Pad Right PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.DPad_Left)) {
		std::cout << controller->getIndex() << " " << "D-Pad Left PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.Start)) {
		std::cout << controller->getIndex() << " " << "Start PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.Back)) {
		std::cout << controller->getIndex() << " " << "Back PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.Back)) {
		std::cout << controller->getIndex() << " " << "Back PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.L_Thumbstick)) {
		std::cout << controller->getIndex() << " " << "L3 PRESSED and HELD" << std::endl;
	}
	if (controller->isButtonDown(XButtons.R_Thumbstick)) {
		std::cout << controller->getIndex() << " " << "R3 PRESSED and HELD" << std::endl;
	}

	if (!controller->LStick_InDeadzone()) {
		//physEng.turn(controller->leftStick_X());
		std::cout << controller->getIndex() << " " << "LS: " << controller->leftStick_X() << std::endl;
	}
	if (!controller->RStick_InDeadzone()) {
		//physEng.turn(controller->leftStick_X());
		std::cout << controller->getIndex() << " " << "RS: " << controller->rightStick_X() << std::endl;
	}
	if (controller->rightTrigger() > 0.0) {
		physEng.forwards(controller->rightTrigger());
		
		std::cout << controller->getIndex() << " " << "Right Trigger: " << controller->rightTrigger() << std::endl;
	}
	else {
		physEng.forwards(0.1f);
	}
	if (controller->leftTrigger() > 0.0) {
		physEng.reverse(controller->leftTrigger());
		std::cout << controller->getIndex() << " " << "Left Trigger: " << controller->leftTrigger() << std::endl;
	}
	physEng.turn(controller->leftStick_X());

	// Update the gamepad for next frame MUST BE LAST
	controller->refreshState();
}

int main()
{
	const char* glsl_version = "#version 130"; // USED FOR IMGUI SETTING
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	Renderer r = Renderer(mainWindow, camera);

	Game mainGame = Game(r);
	Object* car = new Vehicle(1);
	Object* car2 = new Vehicle(2);
	Object* bullet = new DamagingObject(20, 1);

	mainGame.AddObject(car);
	mainGame.AddObject(car2);
	mainGame.AddObject(bullet);

	mainGame.Play();

	// Rendering setup
	CreateObjects();
	CreateShaders();
	CreateHUDs();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureAlpha();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureAlpha();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureAlpha();
	plainTexture.LoadTexture();
	TTexture = Texture("Textures/t.png");
	TTexture.LoadTextureAlpha();
	meterTexture = Texture("Textures/meter.png");
	meterTexture.LoadTextureAlpha();
	dig1Texture = Texture("Textures/numbers/1.png");
	dig1Texture.LoadTextureAlpha();
	healthTexture = Texture("Textures/healthBar.png");
	healthTexture.LoadTextureAlpha();

	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
								0.5f, 0.5f,
								0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
								0.0f, 0.1f,
								0.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	//pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.0f, 0.1f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	//pointLightCount++;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
						0.0f, 2.0f,
						0.0f, 0.0f, 0.0f,
						0.0f, -1.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						20.0f);
	spotLightCount++;
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, -1.5f, 0.0f,
		-100.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	xwing.LoadModel("Models/x-wing.obj");
	boxTest.LoadModel("Models/box.obj");


	// TODO: Put FPS code into Game.Play()
	// Loop until window closed

	glfwSwapInterval(1);
	// imGui setting BEGINNING
	/*
#if __APPLE__
// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
*/
// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings

	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Imgui setting END

	//Audio system setup
	AudioEngine audioSystem = AudioEngine();
	AudioBoomBox audioObject = audioSystem.createBoomBox(audioConstants::SOUND_FILE_TTG_MAIN_MENU);
	AudioBoomBox audioObject2 = audioSystem.createBoomBox(audioConstants::SOUND_FILE_TTG_RACE);

	//The key is now that multiple sounds can be played at once. As long as sound card can support it
	//Comment out one sound if you dont wanna hear it
	//audioObject.playSound();
	//audioObject2.playSound();

	//Controller
	Controller player1 = Controller(1);
	Controller player2 = Controller(2);

	bool P1Connected = player1.isConnected();
	bool P2Connected = player2.isConnected();

	std::cout << "Player1 connected: " << P1Connected << std::endl;
	std::cout << "Player2 connected: " << P2Connected << std::endl;

	//physEng.upwards();
	//End of audio system setup/demo
	while (!mainWindow.getShouldClose())
	{
		physEng.stepPhysics();

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();
		if (P1Connected)
			parseControllerInput(&player1);
		if (P2Connected)
			parseControllerInput(&player2);

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Setup shader
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		// Draw pyramid one
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		// Draw pyramid two
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		// Draw base
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		// Draw X-Wing
		//physEng.increaseForwards();
		physx::PxVec3 xwingPos = physEng.GetPosition();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(xwingPos.x, xwingPos.y, xwingPos.z));	//translate to physx vehicle pos
		model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		xwing.RenderModel();

		// Draw Box
/*		model = glm::mat4(1.0f);
		physx::PxVec3 boxPos = physEng.GetBoxPos();
		model = glm::translate(model, glm::vec3(boxPos.x, boxPos.y, boxPos.z));	//translate to physx vehicle pos
		model = glm::scale(model, glm::vec3(3.f, 3.f, 3.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		boxTest.RenderModel();
		*/

		//Rendering HUD
		hudShader.UseShader();
		uniformModel = hudShader.GetModelLocation();
		uniformProjection = hudShader.GetProjectionLocation();

		glm::mat4 ortho = glm::ortho(0.0f, (float)mainWindow.getWidth(), (float)mainWindow.getHeight(), 0.0f);						//orthograohic projection

		glDisable(GL_DEPTH_TEST);																									//disable the depth-testing

		model = glm::mat4(1.0f);
		//glm::mat4 model = glm::mat4(1.0f);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(ortho));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//meter
		meterTexture.UseTexture();
		HUDList[0]->renderHUD();

		dig1Texture.UseTexture();
		HUDList[1]->renderHUD();

		dig1Texture.UseTexture();
		HUDList[2]->renderHUD();
		
		dig1Texture.UseTexture();
		HUDList[3]->renderHUD();
		
		//health bar
		healthTexture.UseTexture();
		HUDList[4]->renderHUD();

		glEnable(GL_DEPTH_TEST);

		//HUD ends here

		// End of rendering 

		// Start the Dear ImGui frame

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		{
			static float f = 0.0f;
			static int counter = 0;
/*
			ImGui::Begin("FPS COUNTER");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("Frame per Second counter");               // Display some text (you can use a format strings too)

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
*/
			ImGui::Begin("Debug");
			ImGui::Text("Driving mode and Position");
			ImGui::Text("Drivemode: %i Xpos: %f Ypos: %f Zpos: %f", physEng.getModeType(), xwingPos.x, xwingPos.y, xwingPos.z);

			ImGui::End();
		}

		// Rendering imgui
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(mainWindow.getWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// imgui ends here

		// TODO: Load shader in a material struct in the model (Basically all of the following code refactored to being in model


		mainWindow.swapBuffers();
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	


	return 0;
}