/**
 Map2D
 By: Toh Da Jun
 Date: Mar 2020
 */
#pragma once

// Include SingletonTemplate
#include "DesignPatterns\SingletonTemplate.h"

// Include GLEW
#ifndef GLEW_STATIC
#include <GL/glew.h>
#define GLEW_STATIC
#endif

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include the RapidCSV
#include "System/rapidcsv.h"
// Include map storage
#include <map>
// Include Mesh
#include "Primitives\Mesh.h"

// Include Settings
#include "GameControl\Settings.h"

// Include Entity2D
#include "Primitives/Entity2D.h"



// A structure storing information about Map Sizes
struct MapSize {
	unsigned int uiRowSize;
	unsigned int uiColSize;
};

// A structure storing information about a map grid
// It includes data to be used for A* Path Finding
struct Grid {
	unsigned int value;

	// Row and Column index of its parent
	// Note that 0 <= i < uiRowSize & 0 <= j < uiColSize
	unsigned int uiParentRow, uiParentCol;
	// Movement Costs: f = g + h
	double f, g, h;
};

class CMap2D : public CSingletonTemplate<CMap2D>, public CEntity2D
{
	friend CSingletonTemplate<CMap2D>;
public:
	// Init
	bool Init(	const unsigned int uiNumLevels = 1,
				const unsigned int uiNumRows = 24,
				const unsigned int uiNumCols = 32);

	// Update
	void Update(const double dElapsedTime);

	// PreRender
	void PreRender(void);

	// Render
	void Render(void);

	// PostRender
	void PostRender(void);

	// Set the specifications of the map
	void SetNumTiles(const CSettings::AXIS sAxis, const unsigned int uiValue);
	void SetNumSteps(const CSettings::AXIS sAxis, const unsigned int uiValue);

	// Set the value at certain indices in the arrMapInfo
	void SetMapInfo(const unsigned int uiRow, const unsigned int uiCol, const int iValue, const bool bInvert = true);

	// Get the value at certain indices in the arrMapInfo
	int GetMapInfo(const unsigned int uiRow, const unsigned int uiCol, const bool bInvert = true) const;

	// Load a map
	bool LoadMap(string filename, const unsigned int uiLevel = 0);

	// Save a tilemap
	bool SaveMap(string filename, const unsigned int uiLevel = 0);

	// Find the indices of a certain value in arrMapInfo
	bool FindValue(const int iValue, unsigned int& uirRow, unsigned int& uirCol, const bool bInvert = true);

protected:

	//CQuad Mesh for loading tiles
	CMesh* quadMesh;

	// The variable containing the rapidcsv::Document
	// We will load the CSV file's content into this Document
	rapidcsv::Document doc;

	// A 3-D array which stores the values of the tile map
	Grid*** arrMapInfo;

	// The current level
	unsigned int uiCurLevel;
	// The number of levels
	unsigned int uiNumLevels;

	// A 1-D array which stores the map sizes for each level
	MapSize* arrMapSizes;

	// Map containing texture IDs
	map<int, int> MapOfTextureIDs;

	// Constructor
	CMap2D(void);

	// Destructor
	virtual ~CMap2D(void);

	// Load a texture
	bool LoadTexture(const char* filename, const int iTextureCode);

	// Render a tile
	void RenderTile(const unsigned int uiRow, const unsigned int uiCol);
};

