/**
 CScene2D
 By: Toh Da Jun
 Date: Mar 2020
 */
#pragma once

 // Include GLEW
#ifndef GLEW_STATIC
#include <GL/glew.h>
#define GLEW_STATIC
#endif

// Include Design Patterns
#include "DesignPatterns\SingletonTemplate.h"

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include Shader Manager
#include "RenderControl\ShaderManager.h"

// Include Keyboard controller
#include "Inputs\KeyboardController.h"

// GUI
#include "GUI/GUI.h"

class CScene2D : public CSingletonTemplate<CScene2D>
{
	friend CSingletonTemplate<CScene2D>;
public:

	// Init
	bool Init(void);

	// Update
	void Update(const double dElapsedTime);

	// PreRender
	void PreRender(void);

	// Render
	void Render(void);

	// PostRender
	void PostRender(void);

protected:
	//Moved constructor & destructor to prevent instantiation without using getInstance from Singleton STL
	// Constructor
	CScene2D(void);
	// Destructor
	virtual ~CScene2D(void);

	// Keyboard Controller singleton instance
	CKeyboardController* cKeyboardController;

	// A transformation matrix for controlling where to render the entities
	glm::mat4 transform;

	// GUI
	CGUI* cGUI;
};

