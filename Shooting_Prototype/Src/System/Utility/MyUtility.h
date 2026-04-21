#pragma once

//=== どんな型でも int 型に変換する関数 =======================
template<typename T>
constexpr inline int ToInt(T value) noexcept
{
	return static_cast<int>(value);
}

//=== どんな型でも float 型に変換する関数 =====================
template<typename T>
constexpr inline float ToFloat(T value) noexcept
{
	return static_cast<float>(value);
}

//=== 内部で使う乱数エンジン =================================
inline std::mt19937& GetRNG() noexcept
{
	static thread_local std::mt19937 mt{ std::random_device{}() };
	return mt;
}

//=== 指定した範囲内の整数をランダムに返す関数 ==================
inline int RandomRange(int min, int max) noexcept
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(GetRNG());
}

//=== 指定した範囲内の実数をランダムに返す関数 ==================
inline float RandomRangeF(float min, float max) noexcept
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(GetRNG());
}

//=== 0.0f ~ 1.0f の値をランダムに返す関数 ===================
inline float Random01() noexcept
{
	return RandomRangeF(0.0f, 1.0f);
}

//=== 指定した確率で true false を返す関数 ===================
inline bool RandomChance(float probability) noexcept
{
	return Random01() < probability;
}

//=== ランダムな符号を返す関数 ===============================
inline int RandomSign() noexcept
{
	return RandomChance(0.5f) ? 1 : -1;
}

//=== ランダムな色を返す関数 =================================
inline Math::Color RandomColor() noexcept
{
	return { Random01(),
			 Random01(),
			 Random01(),
			 1.0f };
}
