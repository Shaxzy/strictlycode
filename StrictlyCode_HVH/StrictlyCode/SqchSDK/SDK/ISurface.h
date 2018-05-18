#pragma once

#include "AllDef.h"
#include "Color.h"

namespace NSDK {
	typedef ULONG HFont;

	class ISurface {
	public:
		void DrawSetColor(Color col) {
			typedef void(__thiscall *OrigFn)(void*, Color);
			CallVFunction<OrigFn>(this, 14)(this, col);
		}

		void DrawFilledRect(int x0, int y0, int x1, int y1) {
			typedef void(__thiscall *OrigFn)(void*, int, int, int, int);
			CallVFunction<OrigFn>(this, 16)(this, x0, y0, x1, y1);
		}

		void DrawOutlinedRect(int x0, int y0, int x1, int y1) {
			typedef void(__thiscall *OrigFn)(void*, int, int, int, int);
			CallVFunction<OrigFn>(this, 18)(this, x0, y0, x1, y1);
		}

		void DrawLine(int x0, int y0, int x1, int y1) {
			typedef void(__thiscall *OrigFn)(void*, int, int, int, int);
			CallVFunction<OrigFn>(this, 19)(this, x0, y0, x1, y1);
		}

		void DrawSetTextFont(HFont font) {
			typedef void(__thiscall *OrigFn)(void*, HFont);
			CallVFunction<OrigFn>(this, 23)(this, font);
		}

		void DrawSetTextColor(Color col) {
			typedef void(__thiscall *OrigFn)(void*, Color);
			CallVFunction<OrigFn>(this, 24)(this, col);
		}

		void  DrawOutlinedCircle(int x, int y, int r, int seg)
		{
			typedef void(__thiscall* oDrawOutlinedCircle)(PVOID, int, int, int, int);
			return CallVFunction<oDrawOutlinedCircle>(this, 103)(this, x, y, r, seg);
		}

		void DrawSetTextPos(int x, int y) {
			typedef void(__thiscall *OrigFn)(void*, int, int);
			CallVFunction<OrigFn>(this, 26)(this, x, y);
		}

		void DrawPrintText(const wchar_t *text, int textLen, FontDrawType drawType = FontDrawType::FONT_DRAW_DEFAULT) {
			typedef void(__thiscall *OrigFn)(void*, const wchar_t *, int, FontDrawType);
			CallVFunction<OrigFn>(this, 28)(this, text, textLen, drawType);
		}

		HFont CreateFont() {
			typedef HFont(__thiscall *OrigFn)(void*);
			return CallVFunction<OrigFn>(this, 71)(this);
		}

		bool SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) {
			typedef bool(__thiscall *OrigFn)(void*, HFont, const char*, int, int, int, int, int, int, int);
			return CallVFunction<OrigFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
		}

		void GetTextSize(HFont font, const wchar_t *text, int &wide, int &tall) {
			typedef void(__thiscall *OrigFn)(void*, HFont, const wchar_t *, int&, int&);
			CallVFunction<OrigFn>(this, 79)(this, font, text, wide, tall);
		}
	};
}