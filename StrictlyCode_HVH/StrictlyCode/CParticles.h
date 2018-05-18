#pragma once
#include "SqchSDK\SDK\Vector.h"
#include "EntityStructs.h"
#include <vector>
#include "rayGUI\imgui.h"
extern ImDrawList* _drawList;
/* pasted from k4m */
//broken
class dot {
public:
	dot(NSDK::Vector2D p, NSDK::Vector2D v) {
		m_vel = v;
		m_pos = p;
	}

	void update();
	void draw();

	NSDK::Vector2D m_pos, m_vel;
};

extern void dot_draw();
extern void dot_destroy();