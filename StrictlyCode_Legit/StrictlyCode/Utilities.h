#pragma once

#include "EntityStructs.h"
#include "OptionsManager.h"

#define M_PI		3.14159265358979323846f
#define M_PI_F		((float)(M_PI))
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))

class Utilities {
public:
	static bool W2S(const NSDK::Vector& v3D, NSDK::Vector& v2D);
	static NSDK::Vector GetEntityBone(CBaseEntity* pEntity, int iBone);
	static void VectorTransform(NSDK::Vector& in1, NSDK::matrix3x4a_t& in2, NSDK::Vector &out);
	static void SinCos(float radians, float *sine, float *cosine);
	static void AngleVectors(const NSDK::QAngle &angles, NSDK::Vector *forward);
	static void AngleVectors(const NSDK::QAngle &angles, NSDK::Vector *forward, NSDK::Vector *right, NSDK::Vector *up);
	static void VectorAngles1(const NSDK::Vector& forward, NSDK::QAngle &angles);
	static void VectorAngles(const NSDK::Vector& forward, NSDK::QAngle &angles);
	static NSDK::QAngle CalcAngle(NSDK::Vector src, NSDK::Vector dst);
	static bool Clamp(NSDK::QAngle &angles);
	static void NormalizeAngle(NSDK::QAngle& angle);
	static void Normalize(float& angle);
	static void ClampAngles(NSDK::QAngle &angles);
	static float ClampY(float y);
	static NSDK::Vector extrapolateTick(NSDK::Vector p0, CBaseEntity* ent);
	static void SetClanTag(const char* tag, const char* name);
	static void marquee(std::string& marquee);
	static NSDK::Color FromHSB(float hue, float saturation, float brightness);
	static float RandomFloat(float min, float max);
	static void RandomSeed(int iSeed);
	static void AverageDifference(const NSDK::Vector& a, const NSDK::Vector& b, float& result);
	static float GetFov(const NSDK::QAngle& viewAngle, const NSDK::QAngle& aimAngle);
	template< class T, class Y >
	static T ClampValue(T const &val, Y const &minVal, Y const &maxVal);
	static float distance_point_to_line(NSDK::Vector Point, NSDK::Vector LineOrigin, NSDK::Vector Dir);
	static NSDK::Vector Utilities::angle_vector(NSDK::Vector meme);
	static NSDK::Vector AnglesToPixels(NSDK::Vector SourceAngles, NSDK::Vector FinalAngles, float sensitivityy, float mpitch, float myaw);
	static NSDK::Vector PixelsDeltaToAnglesDelta(NSDK::Vector PixelsDelta, float sensitivityy, float mpitch, float myaw);
	static float GetInterp();
	static float GetNetworkLatency();
	static NSDK::Vector ToVector(NSDK::QAngle qAng);
	static NSDK::QAngle ToQAngle(NSDK::Vector vAng);
};