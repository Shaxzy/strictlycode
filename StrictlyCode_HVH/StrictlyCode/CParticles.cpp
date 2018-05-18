#include "CParticles.h"
std::vector<dot*> dots = {};
ImDrawList* _drawList = nullptr;

void dot::update() {
	auto opacity = 75 * (255 / 255.0f);

	m_pos += m_vel * (opacity);
}

void dot::draw() {
	double opacity = (55.0f * (255 / 255.0f)) / 100;
	if (!_drawList)
		return;
	
	_drawList->AddRectFilled(ImVec2(m_pos.x - 2, m_pos.y - 2), ImVec2(2,2), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, opacity)));

	auto t = std::find(dots.begin(), dots.end(), this);
	if (t == dots.end()) {
		return;
	}

	for (auto i = t; i != dots.end(); i++) {
		if ((*i) == this) continue;

		auto dist = (m_pos - (*i)->m_pos).Length();

		if (dist < 128) {
			double alpha = (opacity * (dist / 128) ) / 100;

			_drawList->AddLine(ImVec2(m_pos.x - 1, m_pos.y - 2), ImVec2((*i)->m_pos.x - 2, (*i)->m_pos.y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, alpha)));
		}
	}
}

void dot_draw() {
	struct screen_size {
		int x, y;
	}; screen_size sc;

	NSDK::I::Engine()->GetScreenSize(sc.x, sc.y);

	int s = rand() % 24;

	if (s == 0) {
		dots.push_back(new dot(NSDK::Vector2D(rand() % (int)sc.x, -16), NSDK::Vector2D((rand() % 7) - 3, rand() % 3 + 1)));
	}
	else if (s == 1) {
		dots.push_back(new dot(NSDK::Vector2D(rand() % (int)sc.x, (int)sc.y + 16), NSDK::Vector2D((rand() % 7) - 3, -1 * (rand() % 3 + 1))));
	}
	else if (s == 2) {
		dots.push_back(new dot(NSDK::Vector2D(-16, rand() % (int)sc.y), NSDK::Vector2D(rand() % 3 + 1, (rand() % 7) - 3)));
	}
	else if (s == 3) {
		dots.push_back(new dot(NSDK::Vector2D((int)sc.x + 16, rand() % (int)sc.y), NSDK::Vector2D(-1 * (rand() % 3 + 1), (rand() % 7) - 3)));
	}

	for (auto i = dots.begin(); i < dots.end();) {
		if ((*i)->m_pos.y < -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
			delete (*i);
			i = dots.erase(i);
		}
		else {
			(*i)->update();
			i++;
		}
	}

	for (auto i = dots.begin(); i < dots.end(); i++) {
		(*i)->draw();
	}
}

void dot_destroy() {
	for (auto i = dots.begin(); i < dots.end(); i++) {
		delete (*i);
	}

	dots.clear();
}