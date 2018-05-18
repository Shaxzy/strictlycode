#include "Utilities.h"
#define pi		3.14159265358979323846f
#include <math.h>
#include <algorithm>

FORCEINLINE float DotProduct(const float *v1, const float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

bool Utilities::W2S(const NSDK::Vector& v3D, NSDK::Vector& v2D) 
{
	return (NSDK::I::DebugOverlay()->ScreenPosition(v3D, v2D) != 1);
}

NSDK::Vector Utilities::GetEntityBone(CBaseEntity* pEntity, int iBone) {
	NSDK::matrix3x4_t boneMatrix[128];

	if (!pEntity->SetupBones(boneMatrix, 128, 256, NSDK::I::Engine()->GetLastTimeStamp()))
		return NSDK::Vector();

	NSDK::matrix3x4_t hitbox = boneMatrix[iBone];

	return NSDK::Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
}

NSDK::Vector VelocityExtrapolate(CBaseEntity* player, NSDK::Vector aimPos)
{
	return aimPos + (*player->GetVelocity() * NSDK::I::GlobalVars()->interval_per_tick);
}

float Utilities::GetFov(const NSDK::QAngle& viewAngle, const NSDK::QAngle& aimAngle)
{
	NSDK::QAngle delta = aimAngle - viewAngle;
	Utilities::NormalizeAngle(delta);

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

//static auto linegoesthrusmoke = NSDK::O::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0", "xxxxxxxx????xxx");
NSDK::Color Utilities::FromHSB(float hue, float saturation, float brightness)
{
	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
		return NSDK::Color(
			(unsigned char)(brightness * 255),
			(unsigned char)(t * 255),
			(unsigned char)(p * 255)
		);
	}
	else if (h < 2)
	{
		return NSDK::Color(
			(unsigned char)(q * 255),
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255)
		);
	}
	else if (h < 3)
	{
		return NSDK::Color(
			(unsigned char)(p * 255),
			(unsigned char)(brightness * 255),
			(unsigned char)(t * 255)
		);
	}
	else if (h < 4)
	{
		return NSDK::Color(
			(unsigned char)(p * 255),
			(unsigned char)(q * 255),
			(unsigned char)(brightness * 255)
		);
	}
	else if (h < 5)
	{
		return NSDK::Color(
			(unsigned char)(t * 255),
			(unsigned char)(p * 255),
			(unsigned char)(brightness * 255)
		);
	}
	else
	{
		return NSDK::Color(
			(unsigned char)(brightness * 255),
			(unsigned char)(p * 255),
			(unsigned char)(q * 255)
		);
	}
}

void Utilities::VectorTransform(NSDK::Vector& in1, NSDK::matrix3x4_t& in2, NSDK::Vector &out)
{
	out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
	out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
	out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

void Utilities::VectorTransform(NSDK::Vector& in1, const NSDK::matrix3x4_t& in2, NSDK::Vector &out)
{
	out.x = in1.Dot(NSDK::Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
	out.y = in1.Dot(NSDK::Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
	out.z = in1.Dot(NSDK::Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}

void Utilities::SinCos(float radians, float *sine, float *cosine) 
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

NSDK::Vector Utilities::AnglesToPixels(NSDK::Vector SourceAngles, NSDK::Vector FinalAngles, float sensitivityy, float mpitch, float myaw)
{
	NSDK::Vector delta = SourceAngles - FinalAngles;
	NormalizeAngle(delta);
	float xMove = (-delta.x) / (myaw * sensitivityy);
	float yMove = (delta.y) / (mpitch * sensitivityy);

	return NSDK::Vector(yMove, xMove, 0.0f);
}

NSDK::Vector Utilities::PixelsDeltaToAnglesDelta(NSDK::Vector PixelsDelta, float sensitivityy, float mpitch, float myaw)
{
	float xMove = (-PixelsDelta.x) * (myaw * sensitivityy);
	float yMove = (PixelsDelta.y) * (mpitch * sensitivityy);

	return NSDK::Vector(yMove, xMove, 0.0f);
}

NSDK::Vector Utilities::angle_vector(NSDK::Vector meme)
{
	auto sy = sin(meme.y / 180.f * static_cast<float>(pi));
	auto cy = cos(meme.y / 180.f * static_cast<float>(pi));

	auto sp = sin(meme.x / 180.f * static_cast<float>(pi));
	auto cp = cos(meme.x / 180.f* static_cast<float>(pi));

	return NSDK::Vector(cp*cy, cp*sy, -sp);
}

void Utilities::AngleVectors(const NSDK::QAngle &angles, NSDK::Vector *forward) {
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[NSDK::MathThings::YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[NSDK::MathThings::PITCH]), &sp, &cp);

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void Utilities::marquee(std::string& marquee)
{
	std::string temp_string = marquee;
	marquee.erase(0, 1);
	marquee += temp_string[0];
}



void Utilities::AngleVectors(const NSDK::QAngle &angles, NSDK::Vector *forward, NSDK::Vector *right, NSDK::Vector *up){
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[NSDK::MathThings::YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[NSDK::MathThings::PITCH]), &sp, &cp);
	SinCos(DEG2RAD(angles[NSDK::MathThings::ROLL]), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

void Utilities::VectorAngles1(const NSDK::Vector& forward, NSDK::QAngle &angles){
	float	tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

void Utilities::VectorAngles(const NSDK::Vector& forward, NSDK::QAngle &angles) {
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90) angles[1] -= 180;
		else if (angles[1] < 90) angles[1] += 180;
		else if (angles[1] == 90) angles[1] = 0;
	}

	angles[2] = 0.0f;
}


NSDK::QAngle Utilities::CalcAngle(NSDK::Vector src, NSDK::Vector dst) 
{
	NSDK::QAngle angles;
	NSDK::Vector delta = src - dst;
	VectorAngles(delta, angles);
	NormalizeAngle(delta);
	return angles;
}

void Utilities::AverageDifference(const NSDK::Vector& a, const NSDK::Vector& b, float& result)
{
	NSDK::Vector calcvec;
	calcvec.x = abs(a.x - b.x);
	calcvec.y = abs(a.y - b.y);
	calcvec.z = abs(a.y - b.y);

	result = (calcvec.x + calcvec.y + calcvec.z) / 3.f;
}

void Utilities::Clamp(NSDK::QAngle &angs) 
{
	if (angs.x > 89) angs.x = 89;

	if (angs.x < -89) angs.x = -89;

	// bad number.
	if (!std::isfinite(angs.y))
	{
		angs.y = 0.f;
		return;
	}

	// no need to normalize this angle.
	if (angs.y >= -180.f && angs.y <= 180.f)
		return;

	// get amount of rotations needed.
	float rot = std::round(std::abs(angs.y / 360.f));

	// normalize.
	angs.y = (angs.y < 0.f) ? angs.y + (360.f * rot) : angs.y - (360.f * rot);
}

float Utilities::ClampY(float Y) 
{
	while (Y > 180)
	{
		Y -= 180;
	}
	while (Y < -180) 
	{
		Y += 180;
	}
	return Y;
}

void Utilities::NormalizeAngle(NSDK::QAngle& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

void Utilities::ClampAngles(NSDK::QAngle& angle)
{
	if (angle.y > 180.0f)
		angle.y = 180.0f;

	else if (angle.y < -180.0f)
		angle.y = -180.0f;

	if (angle.x > 89.0f)
		angle.x = 89.0f;

	else if (angle.x < -89.0f)
		angle.x = -89.0f;

	angle.z = 0;
}

void Utilities::Normalize(float& angle) 
{
	while (angle > 180.f) 
	{
		angle -= 180.f;
	}
	while (angle < -180.f) 
	{
		angle += 180.f;
	}
}


NSDK::Vector Utilities::extrapolateTick(NSDK::Vector p0, CBaseEntity* ent) 
{
	return p0 + (*ent->GetVelocity() * NSDK::I::GlobalVars()->interval_per_tick);
}

void Utilities::SetClanTag(const char* tag, const char* name) {
	using SetClanTagFn = void(__fastcall*) (const char *tag, const char *name);
	static SetClanTagFn SetClanTagEx = (SetClanTagFn)(NSDK::O::FindSignature( ("engine.dll"),  ("53 56 57 8B DA 8B F9 FF 15")));
	SetClanTagEx(tag, name);
}

float Utilities::RandomFloat(float min, float max)
{
	typedef float(*RandomFloat_t)(float, float);
	static RandomFloat_t m_RandomFloat = (RandomFloat_t)GetProcAddress(GetModuleHandle( ("vstdlib.dll")),  ("RandomFloat"));
	return m_RandomFloat(min, max);
}

void Utilities::RandomSeed(int iSeed)
{
	typedef void(*RandomSeed_t)(int);
	static RandomSeed_t m_RandomSeed = (RandomSeed_t)GetProcAddress(GetModuleHandle( ("vstdlib.dll")),  ("RandomSeed"));
	return m_RandomSeed(iSeed);
}

template< class T, class Y >

T Utilities::ClampValue(T const &val, Y const &minVal, Y const &maxVal)
{
	if (val < minVal)
		return minVal;
	else if (val > maxVal)
		return maxVal;
	else
		return val;
}

float Utilities::distance_point_to_line(NSDK::Vector Point, NSDK::Vector LineOrigin, NSDK::Vector Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}

float Utilities::GetInterp()
{
	float updaterate = NSDK::I::CVar()->FindVar( ("cl_updaterate"))->GetFloat();
	NSDK::ConVar* minupdate = NSDK::I::CVar()->FindVar( ("sv_minupdaterate"));
	NSDK::ConVar* maxupdate = NSDK::I::CVar()->FindVar( ("sv_maxupdaterate"));

	if (minupdate && maxupdate)
		updaterate = maxupdate->GetFloat();

	float ratio = NSDK::I::CVar()->FindVar( ("cl_interp_ratio"))->GetFloat();

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = NSDK::I::CVar()->FindVar( ("cl_interp"))->GetFloat();
	NSDK::ConVar* cmin = NSDK::I::CVar()->FindVar( ("sv_client_min_interp_ratio"));
	NSDK::ConVar* cmax = NSDK::I::CVar()->FindVar( ("sv_client_max_interp_ratio"));

	if (cmin && cmax && cmin->GetFloat() != 1)
		ratio = ClampValue(ratio, cmin->GetFloat(), cmax->GetFloat());

	return max(lerp, ratio / updaterate);
}

float Utilities::GetNetworkLatency()
{
	// Get true latency
	NSDK::INetChannelInfo *nci = NSDK::I::Engine()->GetNetChannelInfo();
	if (nci)
	{
		float OutgoingLatency = nci->GetAvgLatency(0);
		return OutgoingLatency;
	}
	else
	return 0.0f;
}

NSDK::Vector Utilities::ToVector(NSDK::QAngle qAng)
{
	return NSDK::Vector(qAng.x, qAng.y, qAng.z);
}

NSDK::QAngle Utilities::ToQAngle(NSDK::Vector vAng)
{
	return NSDK::QAngle(vAng.x, vAng.y, vAng.z);
}

float Utilities::clip(float n, float lower, float upper) 
{
	return max(lower, min(n, upper));
}

bool Utilities::HitChance(CBaseEntity* local, CBaseCombatWeapon* weapon, int chance) 
{
		float inaccuracy = weapon->GetAccuracy();

		if (inaccuracy == 0)
			inaccuracy = 0.0000001;

		inaccuracy = 1 / inaccuracy;

		return inaccuracy > chance;
}

void Utilities::AngleMatrix(const NSDK::Vector angles, NSDK::matrix3x4_t& matrix)
{
	float sr, sp, sy, cr, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	sr = sin(DEG2RAD(angles[2]));
	cr = cos(DEG2RAD(angles[2]));

	//matrix = (YAW * PITCH) * ROLL
	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = (sp * crcy + srsy);
	matrix[1][2] = (sp * crsy - srcy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

void Utilities::MatrixSetColumn(const NSDK::Vector &in, int column, NSDK::matrix3x4_t& out)
{
	out[0][column] = in.x;
	out[1][column] = in.y;
	out[2][column] = in.z;
}

void Utilities::AngleMatrix(const NSDK::QAngle &angles, const NSDK::Vector &position, NSDK::matrix3x4_t& matrix_out)
{
	AngleMatrix(angles, matrix_out);
	MatrixSetColumn(position, 3, matrix_out);
}

void Utilities::MatrixCopy(const NSDK::matrix3x4_t& source, NSDK::matrix3x4_t& target)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			target[i][j] = source[i][j];
		}
	}
}

void Utilities::MatrixMultiply(NSDK::matrix3x4_t& in1, const NSDK::matrix3x4_t& in2)
{
	NSDK::matrix3x4_t out;
	if (&in1 == &out)
	{
		NSDK::matrix3x4_t in1b;
		MatrixCopy(in1, in1b);
		MatrixMultiply(in1b, in2);
		return;
	}
	if (&in2 == &out)
	{
		NSDK::matrix3x4_t in2b;
		MatrixCopy(in2, in2b);
		MatrixMultiply(in1, in2b);
		return;
	}
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
		in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
		in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
		in1[0][2] * in2[2][2];
	out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
		in1[0][2] * in2[2][3] + in1[0][3];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
		in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
		in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
		in1[1][2] * in2[2][2];
	out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
		in1[1][2] * in2[2][3] + in1[1][3];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
		in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
		in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
		in1[2][2] * in2[2][2];
	out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
		in1[2][2] * in2[2][3] + in1[2][3];

	in1 = out;
}

void Utilities::VectorRotate(const float *in1, const NSDK::matrix3x4_t& in2, float *out)
{
	out[0] = DotProduct(in1, in2[0]);
	out[1] = DotProduct(in1, in2[1]);
	out[2] = DotProduct(in1, in2[2]);
}

void Utilities::VectorRotate(const NSDK::Vector& in1, const NSDK::matrix3x4_t &in2, NSDK::Vector &out)
{
	VectorRotate(&in1.x, in2, &out.x);
}

void Utilities::VectorRotate(const NSDK::Vector &in1, const NSDK::QAngle &in2, NSDK::Vector &out)
{
	NSDK::matrix3x4_t matRotate;
	AngleMatrix(in2, matRotate);
	VectorRotate(in1, matRotate, out);
}