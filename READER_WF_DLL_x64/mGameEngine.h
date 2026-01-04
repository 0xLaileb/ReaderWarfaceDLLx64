#pragma once
#include <windows.h>
#include <Math.h>
#define DBL_MIN          2.2250738585072014e-308
#define ILINE __forceinline
#define BIT(x)   (1 << (x))

typedef unsigned int EntityId;
typedef unsigned int uint32;
typedef signed int int32;
typedef float f32;

enum type_zero { ZERO };
enum type_min { VMIN };
enum type_max { VMAX };
enum type_identity { IDENTITY };

const float VEC_EPSILON = 0.05f;

ILINE float _sqrt(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)& y;                     // floating point bit level hacking [sic]
	i = 0x5f3759df - (i >> 1);             // Newton's approximation
	y = *(float*)& i;
	y = y * (threehalfs - (x2 * y * y)); // 1st iteration
	y = y * (threehalfs - (x2 * y * y)); // 2nd iteration
	y = y * (threehalfs - (x2 * y * y)); // 3rd iteration

	return 1 / y;
}

ILINE float isqrt_safe_tpl(float op) { return 1.0f / (float)_sqrt(op + (float)DBL_MIN); }
ILINE int32 int_round(f32 f) { return f < 0.f ? int32(f - 0.5f) : int32(f + 0.5f); }

template <typename F> struct Vec3_tpl {
	F x, y, z;
	ILINE Vec3_tpl(type_zero) : x(0), y(0), z(0) {}
	ILINE Vec3_tpl(type_min);
	ILINE Vec3_tpl(type_max);
	explicit ILINE Vec3_tpl(F f) : x(f), y(f), z(f) { }
	ILINE Vec3_tpl() {
		Vec3_tpl(0, 0, 0);
	}
	ILINE Vec3_tpl(F xt, F yt, F zt) {
		x = xt;
		y = yt;
		z = zt;
	}
	ILINE F length() const { return (F)_sqrt(x * x + y * y + z * z); }
	template<typename T> ILINE F sum(T a) {
		F s = 0;
		for (int i = 0; i < a.size; ++i) s += a[i];
		return s;
	}
	template<typename T> ILINE F dot(T a, T b) { return sum(a * b); }

	ILINE F  distance(Vec3_tpl VecB) { return (F)_sqrt(((x - VecB.x) * (x - VecB.x)) + ((y - VecB.y) * (y - VecB.y)) + ((z - VecB.z) * (z - VecB.z))); }

	ILINE F& operator[](int index) { return ((F*)this)[index]; }
	ILINE F  operator[](int index) const { return ((F*)this)[index]; }

	void operator += (F f) { x += f; y += f; z += f; }
	void operator -= (F f) { x -= f; y -= f; z -= f; }
	ILINE Vec3_tpl<F> operator*(F k) const {
		const Vec3_tpl<F> v = *this;
		return Vec3_tpl<F>(v.x * k, v.y * k, v.z * k);
	}
	ILINE Vec3_tpl& operator /  (F f) { return Vec3_tpl(x / f, y / f, z / f); }
	ILINE Vec3_tpl& operator = (const Vec3_tpl& source) { x = source.x; y = source.y; z = source.z; return *this; }
	ILINE Vec3_tpl& operator = (const F value) { x = value; y = value; z = value;   return *this; }
	ILINE Vec3_tpl& operator *= (F f) { x *= f; y *= f; z *= f; return *this; }
	ILINE Vec3_tpl& operator /= (F f) { x /= f; y /= f; z /= f; return *this; }

	ILINE friend Vec3_tpl operator + (const Vec3_tpl& vec1, const Vec3_tpl& vec2) { return Vec3_tpl(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z); }
	ILINE friend Vec3_tpl operator + (const Vec3_tpl& vec1, const F* vec2) { return vec1 + Vec3_tpl(vec2); }
	ILINE friend Vec3_tpl operator + (const F* vec1, const Vec3_tpl& vec2) { return Vec3_tpl(vec1) + vec2; }

	ILINE friend Vec3_tpl operator - (const Vec3_tpl& vec1, const Vec3_tpl& vec2) { return Vec3_tpl(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z); }
	ILINE friend Vec3_tpl operator - (const Vec3_tpl& vec1, const F* vec2) { return vec1 - Vec3_tpl(vec2); }
	ILINE friend Vec3_tpl operator - (const F* vec1, const Vec3_tpl& vec2) { return Vec3_tpl(vec1) - vec2; }

	ILINE Vec3_tpl<F>& Set(const F xval, const F yval, const F zval) {
		x = xval; y = yval; z = zval;
		return *this;
	}

	ILINE Vec3_tpl& normalize() {
		F len2 = x * x + y * y + z * z;
		if (len2 > (F)1e-20f) {
			F rlen = _sqrt(len2);
			x *= rlen;
			y *= rlen;
			z *= rlen;
		}
		else Set(0, 0, 1);

		return *this;
	}
	ILINE Vec3_tpl<F> GetNormalized() const {
		FLOAT fInvLen = (FLOAT)isqrt_safe_tpl(x * x + y * y + z * z);
		Vec3_tpl<F> out = *this;
		out.x *= fInvLen;
		out.y *= fInvLen;
		out.z *= fInvLen;
		return out;
	}
};
template <typename F> struct Vec4_tpl {
	F x, y, z, w;
	ILINE Vec4_tpl(type_zero) : x(0), y(0), z(0), w(0) {}
	ILINE Vec4_tpl(type_min);
	ILINE Vec4_tpl(type_max);
	explicit ILINE Vec4_tpl(F f) : x(f), y(f), z(f), w(f) { }
	ILINE Vec4_tpl() {
		Vec4_tpl(0, 0, 0, 0);
	}
	ILINE Vec4_tpl(F xt, F yt, F zt, F wt) {
		x = xt;
		y = yt;
		z = zt;
		w = wt;
	}
};
template <typename F> struct Quat_tpl {
	Vec3_tpl<F> v;
	F w;
	ILINE  Quat_tpl() {}
	ILINE  Quat_tpl(F angle, const Vec3_tpl<F>& axis) : w(angle), v(axis) {};
	ILINE  Quat_tpl(type_identity) : w(1), v(0, 0, 0) {}

	ILINE  bool operator!=(const Quat_tpl<F>& q) const { return !(*this == q); }
	ILINE  Quat_tpl<F>	operator - () const { return Quat_tpl<F>(-w, -v); };

	ILINE  bool IsEquivalent(const Quat_tpl<F>& q, F e = VEC_EPSILON) const {
		Quat_tpl<F> p = -q;
		bool t0 = (fabs_tpl(v.x - q.v.x) <= e) && (fabs_tpl(v.y - q.v.y) <= e) && (fabs_tpl(v.z - q.v.z) <= e) && (fabs_tpl(w - q.w) <= e);
		bool t1 = (fabs_tpl(v.x - p.v.x) <= e) && (fabs_tpl(v.y - p.v.y) <= e) && (fabs_tpl(v.z - p.v.z) <= e) && (fabs_tpl(w - p.w) <= e);
		t0 |= t1;
		return t0;
	}
	ILINE   void  SetRotationVDir(const Vec3_tpl<F>& vdir) {
		w = (0.70710676908493042f);
		v.x = (vdir.z * 0.70710676908493042f);
		v.y = (0.0f);
		v.z = (0.0f);

		F l = (F)_sqrt(vdir.x * vdir.x + vdir.y * vdir.y);

		if (l > (0.00001)) {
			Vec3_tpl<F> hv;
			hv.x = vdir.x / l;
			hv.y = vdir.y / l + 1.0f;
			hv.z = l + 1.0f;

			F r = (F)_sqrt(hv.x * hv.x + hv.y * hv.y);
			F s = (F)_sqrt(hv.z * hv.z + vdir.z * vdir.z);
			F hacos0 = 0.0;
			F hasin0 = -1.0;

			if (r > (0.00001)) {
				hacos0 = hv.y / r;
				hasin0 = -hv.x / r;
			}
			F hacos1 = hv.z / s;
			F hasin1 = vdir.z / s;
			w = (hacos0 * hacos1);
			v.x = (hacos0 * hasin1);
			v.y = (hasin0 * hasin1);
			v.z = (hasin0 * hacos1);
		}
	}
	static Quat_tpl<F> CreateRotationVDir(const Vec3_tpl<F>& vdir) {
		Quat_tpl<F> q;
		q.SetRotationVDir(vdir);
		return q;
	}
	ILINE void SetIndentity() { w = 1; v.x = 0; v.y = 0; v.z = 0; }
};

template <typename F> struct QuatT_tpl {
	Quat_tpl<F>   q;
	Vec3_tpl<F> t;
	ILINE  QuatT_tpl() {};
	ILINE  QuatT_tpl(const Vec3_tpl<F>& _t, const Quat_tpl<F>& _q) { q = _q; t = _t; }
	ILINE  QuatT_tpl(type_identity) { q.w = 1; q.v.x = 0; q.v.y = 0; q.v.z = 0; t.x = 0; t.y = 0; t.z = 0; }
};
template <typename F> struct Matrix33_tpl {
	F m00, m01, m02;
	F m10, m11, m12;
	F m20, m21, m22;
	ILINE  Matrix33_tpl() {};
	explicit ILINE Matrix33_tpl<F>(const Quat_tpl<F>& q) {
		Vec3_tpl<F> v2 = q.v + q.v;
		F xx = 1 - v2.x * q.v.x;
		F yy = v2.y * q.v.y;
		F xw = v2.x * q.w;
		F xy = v2.y * q.v.x;
		F yz = v2.z * q.v.y;
		F yw = v2.y * q.w;
		F xz = v2.z * q.v.x;
		F zz = v2.z * q.v.z;
		F zw = v2.z * q.w;
		m00 = 1 - yy - zz;
		m01 = xy - zw;
		m02 = xz + yw;
		m10 = xy + zw;
		m11 = xx - zz;
		m12 = yz - xw;
		m20 = xz - yw;
		m21 = yz + xw;
		m22 = xx - yy;
	}
	template<typename F1> ILINE  Matrix33_tpl(const Matrix33_tpl<F1>& m) {
		m00 = F(m.m00);	m01 = F(m.m01);	m02 = F(m.m02);
		m10 = F(m.m10);	m11 = F(m.m11);	m12 = F(m.m12);
		m20 = F(m.m20);	m21 = F(m.m21);	m22 = F(m.m22);
	}
	ILINE  Matrix33_tpl& operator = (const Matrix33_tpl<F>& m) {
		m00 = m.m00;	m01 = m.m01;	m02 = m.m02;
		m10 = m.m10;	m11 = m.m11;	m12 = m.m12;
		m20 = m.m20;	m21 = m.m21;	m22 = m.m22;
		return *this;
	}
};
template <typename F> struct Matrix34_tpl {
	F m00, m01, m02, m03;
	F m10, m11, m12, m13;
	F m20, m21, m22, m23;

	ILINE Matrix34_tpl() {};
	template<class F1> explicit Matrix34_tpl(const QuatT_tpl<F1>& q) {
		Vec3_tpl<F1> v2 = q.q.v + q.q.v;
		F1 xx = 1 - v2.x * q.q.v.x;		F1 yy = v2.y * q.q.v.y;		F1 xw = v2.x * q.q.w;
		F1 xy = v2.y * q.q.v.x;			F1 yz = v2.z * q.q.v.y;		F1 yw = v2.y * q.q.w;
		F1 xz = v2.z * q.q.v.x;			F1 zz = v2.z * q.q.v.z;		F1 zw = v2.z * q.q.w;
		m00 = F(1 - yy - zz);			m01 = F(xy - zw);			m02 = F(xz + yw);			m03 = F(q.t.x);
		m10 = F(xy + zw);				m11 = F(xx - zz);			m12 = F(yz - xw);			m13 = F(q.t.y);
		m20 = F(xz - yw);				m21 = F(yz + xw);			m22 = F(xx - yy);			m23 = F(q.t.z);
	}
	ILINE Vec3_tpl <F>GetTranslation() const { return Vec3_tpl <F>(m03, m13, m23); }

	ILINE Matrix34_tpl <F>SetTranslation(Vec3_tpl<F>vPos) {
		m03 = F(vPos.x);
		m13 = F(vPos.y);
		m23 = F(vPos.z);
		return *this;
	}
};
template<typename F> struct Matrix44_tpl {
	F m00, m01, m02, m03;
	F m10, m11, m12, m13;
	F m20, m21, m22, m23;
	F m30, m31, m32, m33;

	ILINE Matrix44_tpl() {};
	ILINE void SetZero() {
		m00 = 0;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 0;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 0;
	}
	ILINE void SetIdentity()
	{
		m00 = 1;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 1;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 1;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 1;
	}
	ILINE Matrix44_tpl(type_zero) { SetZero(); }
	ILINE F& operator[](int index) { return ((F*)this)[index]; }
	ILINE F  operator[](int index) const { return ((F*)this)[index]; }
};

template<class F1, class F2>ILINE Vec3_tpl<F1> operator*(const Matrix33_tpl<F2>& m, const Vec3_tpl<F1>& p) {
	Vec3_tpl<F1> tp;
	tp.x = F1(m.m00 * p.x + m.m01 * p.y + m.m02 * p.z);
	tp.y = F1(m.m10 * p.x + m.m11 * p.y + m.m12 * p.z);
	tp.z = F1(m.m20 * p.x + m.m21 * p.y + m.m22 * p.z);
	return tp;
}
template<class F, class F2> Vec3_tpl<F> operator*(const QuatT_tpl<F>& q, const Vec3_tpl<F2>& v) {
	Vec3_tpl<F> out, r2;
	r2.x = (q.q.v.y * v.z - q.q.v.z * v.y) + q.q.w * v.x;
	r2.y = (q.q.v.z * v.x - q.q.v.x * v.z) + q.q.w * v.y;
	r2.z = (q.q.v.x * v.y - q.q.v.y * v.x) + q.q.w * v.z;
	out.x = (r2.z * q.q.v.y - r2.y * q.q.v.z);
	out.x += out.x + v.x + q.t.x;
	out.y = (r2.x * q.q.v.z - r2.z * q.q.v.x);
	out.y += out.y + v.y + q.t.y;
	out.z = (r2.y * q.q.v.x - r2.x * q.q.v.y);
	out.z += out.z + v.z + q.t.z;
	return out;
}
template<class F> Vec3_tpl<F> operator*(const Matrix34_tpl<F>& m, const Vec3_tpl<F>& p) {
	Vec3_tpl<F> tp;
	tp.x = m.m00 * p.x + m.m01 * p.y + m.m02 * p.z + m.m03;
	tp.y = m.m10 * p.x + m.m11 * p.y + m.m12 * p.z + m.m13;
	tp.z = m.m20 * p.x + m.m21 * p.y + m.m22 * p.z + m.m23;
	return tp;
}
template <class F> Matrix34_tpl<F> operator * (const Matrix34_tpl<F>& l, const Matrix34_tpl<F>& r) {
	Matrix34_tpl<F> m;
	m.m00 = l.m00 * r.m00 + l.m01 * r.m10 + l.m02 * r.m20;
	m.m10 = l.m10 * r.m00 + l.m11 * r.m10 + l.m12 * r.m20;
	m.m20 = l.m20 * r.m00 + l.m21 * r.m10 + l.m22 * r.m20;
	m.m01 = l.m00 * r.m01 + l.m01 * r.m11 + l.m02 * r.m21;
	m.m11 = l.m10 * r.m01 + l.m11 * r.m11 + l.m12 * r.m21;
	m.m21 = l.m20 * r.m01 + l.m21 * r.m11 + l.m22 * r.m21;
	m.m02 = l.m00 * r.m02 + l.m01 * r.m12 + l.m02 * r.m22;
	m.m12 = l.m10 * r.m02 + l.m11 * r.m12 + l.m12 * r.m22;
	m.m22 = l.m20 * r.m02 + l.m21 * r.m12 + l.m22 * r.m22;
	m.m03 = l.m00 * r.m03 + l.m01 * r.m13 + l.m02 * r.m23 + l.m03;
	m.m13 = l.m10 * r.m03 + l.m11 * r.m13 + l.m12 * r.m23 + l.m13;
	m.m23 = l.m20 * r.m03 + l.m21 * r.m13 + l.m22 * r.m23 + l.m23;
	return m;
}

template<class F> Vec3_tpl<F> operator*(const Vec3_tpl<F>& m, const Vec3_tpl<F>& p) {
	return Vec3_tpl<F>(m.x * p.x, m.y * p.y, m.z * p.z);
}
typedef Vec3_tpl<float>			Vec3;
typedef Vec4_tpl<float>			Vec4;
typedef Quat_tpl<float>			Quat;
typedef QuatT_tpl<float>		QuatT;
typedef Quat_tpl<float>			quaternionf;
typedef Matrix33_tpl<float>		Matrix33;
typedef Matrix34_tpl<float>		Matrix34;
typedef Matrix44_tpl<FLOAT>		Matrix44;

struct AABB {
	Vec3 min;
	Vec3 max;
	ILINE Vec3 GetCenter() const { return (min + max) * 0.5f; }
	ILINE bool IsReset() const { return min.x > max.x; }
	ILINE void Reset() { min = Vec3(1e15f);  max = Vec3(-1e15f); }
};

/*
enum KeyCodes :INT {

	BACKSPACE = 8,
	TAB = 9,
	ENTER = 13,
	SHIFT = 16,
	CTRL = 17,
	ALT = 18,
	PAUSE_BREAK = 19,
	CAPS_LOCK = 20,
	ESCAPE = 27,
	PAGE_UP = 33,
	PAGE_DOWN = 34,
	END = 35,
	HOME = 36,
	LEFT_ARROW = 37,
	UP_ARROW = 38,
	RIGHT_ARROW = 39,
	DOWN_ARROW = 40,
	INSERT = 45,
	DELETE_ = 46,
	_0 = 48,
	_1 = 49,
	_2 = 50,
	_3 = 51,
	_4 = 52,
	_5 = 53,
	_6 = 54,
	_7 = 55,
	_8 = 56,
	_9 = 57,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	LEFT_WINDOW = 91,
	RIGHT_WINDOW = 92,
	SELECT_KEY = 93,
	NUMPAD_0 = 96,
	NUMPAD_1 = 97,
	NUMPAD_2 = 98,
	NUMPAD_3 = 99,
	NUMPAD_4 = 100,
	NUMPAD_5 = 101,
	NUMPAD_6 = 102,
	NUMPAD_7 = 103,
	NUMPAD_8 = 104,
	NUMPAD_9 = 105,
	MULTIPLY = 106,
	ADD = 107,
	SUBTRACT = 109,
	DECIMAL_POINT = 110,
	DIVIDE = 111,
	F1 = 112,
	F2 = 113,
	F3 = 114,
	F4 = 115,
	F5 = 116,
	F6 = 117,
	F7 = 118,
	F8 = 119,
	F9 = 120,
	F10 = 121,
	F11 = 122,
	F12 = 123,
	NUM_LOCK = 144,
	SCROLL_LOCK = 145,
	SEMI_COLON = 186,
	EQUAL_SIGN = 187,
	COMMA = 188,
	DASH = 189,
	PERIOD = 190,
	FORWARD_SLASH = 191,
	GRAVE_ACCENT = 192,
	OPEN_BRACKET = 219,
	BACK_SLASH = 220,
	CLOSE_BRAKET = 221,
	SINGLE_QUOTE = 222
};
*/

/*
enum EEntityProxy {
	ENTITY_PROXY_RENDER,
	ENTITY_PROXY_PHYSICS,
	ENTITY_PROXY_SCRIPT,
	ENTITY_PROXY_AUDIO,
	ENTITY_PROXY_AI,
	ENTITY_PROXY_AREA,
	ENTITY_PROXY_BOIDS,
	ENTITY_PROXY_BOID_OBJECT,
	ENTITY_PROXY_CAMERA,
	ENTITY_PROXY_FLOWGRAPH,
	ENTITY_PROXY_SUBSTITUTION,
	ENTITY_PROXY_TRIGGER,
	ENTITY_PROXY_ROPE,
	ENTITY_PROXY_ENTITYNODE,
	ENTITY_PROXY_ATTRIBUTES,
	ENTITY_PROXY_CLIPVOLUME,
	ENTITY_PROXY_DYNAMICRESPONSE,
	ENTITY_PROXY_USER,
	ENTITY_PROXY_LAST
};


enum EEntityXFormFlags {
	ENTITY_XFORM_POS = BIT(1),
	ENTITY_XFORM_ROT = BIT(2),
	ENTITY_XFORM_SCL = BIT(3),
	ENTITY_XFORM_NO_PROPOGATE = BIT(4),
	ENTITY_XFORM_FROM_PARENT = BIT(5),   //!< When parent changes his transformation.
	ENTITY_XFORM_PHYSICS_STEP = BIT(13),
	ENTITY_XFORM_EDITOR = BIT(14),
	ENTITY_XFORM_TRACKVIEW = BIT(15),
	ENTITY_XFORM_TIMEDEMO = BIT(16),
	ENTITY_XFORM_NOT_REREGISTER = BIT(17),  //!< Optimization flag, when set object will not be re-registered in 3D engine.
	ENTITY_XFORM_NO_EVENT = BIT(18),  //!< Suppresses ENTITY_EVENT_XFORM event.
	ENTITY_XFORM_NO_SEND_TO_ENTITY_SYSTEM = BIT(19),
	ENTITY_XFORM_USER = 0x1000000,
};

enum EEntityGetSetSlotFlags {
	ENTITY_SLOT_ACTUAL = 1 << 31
};
*/

enum ESilhouettesParams {
	eAllMap = 524312,
	eLimitDistance = 524296
};