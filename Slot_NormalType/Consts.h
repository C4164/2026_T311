#pragma once

namespace Const
{
	//小役の種類
	constexpr enum MinorPrize
	{
		bell,				//ベル
		replay,				//リプレイ
		chance,				//チャンス目
		melon_weakness,		//弱スイカ
		melon_strength_1,	//強スイカ1
		melon_strength_2,	//強スイカ2
		cherry_weakness,	//弱チェリー
		cherry_strength_1,	//強チェリー1
		cherry_strength_2,	//強チェリー2
	};

	//設定の段階(数)
	constexpr int SETTING = 6;

	//設定別の小役確率[分子：16bit(65536)分の何か]
	struct Probability
	{
		const int BELL[SETTING] = { 0,0,0,0,0,0 };				//ベル
		const int REPLAY[SETTING] = { 0,0,0,0,0,0 };			//リプレイ
		const int CHANCE[SETTING] = { 0,0,0,0,0,0 };			//チャンス目
		const int MELON_WEAKNESS[SETTING] = { 0,0,0,0,0,0 };	//弱スイカ
		const int MELON_STRENGTH_1[SETTING] = { 0,0,0,0,0,0 };	//強スイカ1
		const int MELON_STRENGTH_2[SETTING] = { 0,0,0,0,0,0 };	//強スイカ2
		const int CHERRY_WEAKNESS[SETTING] = { 0,0,0,0,0,0 };	//弱チェリー
		const int CHERRY_STRENGTH_1[SETTING] = { 0,0,0,0,0,0 };	//強チェリー1
		const int CHERRY_STRENGTH_2[SETTING] = { 0,0,0,0,0,0 };	//強チェリー2
	};
}