/**
 * @file Game.h
 * @brief ゲームクラスの宣言
 * @author Gold Smith
 * @date 2023
 *
 * Released under the MIT license
 * https: //opensource.org/licenses/mit-license.php
 */
#pragma once
#define NOMINMAX
#define _CRTDBG_MAP_ALLOC
#include<Windows.h>
#include<string>
#include<iostream>
#include<sstream>
#include <limits>
using namespace std;
constexpr int N = 3;
constexpr int INF = 1000000;

class Game
{
public:
	Game();
	~Game();
	bool operator==(const Game& other) const = delete;
	/// <summary>
	/// 実際のゲームスタート。
	/// </summary>
	/// <param name="human_first">人が先攻か。</param>
	/// <param name="two_player">2プレーヤー対戦か。</param>
	void play_game(bool human_first, bool two_player);
private:
	/// <summary>
	/// これでboard_tという型定義。
	/// </summary>
	typedef char board_t[N][N];
	board_t board;
	void display_board();
	void init_game();
	bool is_draw();
	bool is_win(char player);
	/// <summary>
	/// 評価関数
	/// </summary>
	/// <param name="ch">対象の手番</param>
	/// <param name="depth">読み深さ</param>
	/// <param name="pb_is_seddled">決着が着いたか
	/// 着いてないかの結果を受け取るポインタ。</param>
	/// <returns></returns>
	int evaluate(char ch, int depth, bool* pb_is_seddled);
	/// <summary>
	/// 盤面を作り出す関数。
	/// </summary>
	/// <param name="depth">読みの深さ。深いほどリターンの評価値は鈍くなる。</param>
	/// <param name="ch">次の手番</param>
	/// <returns>評価値</returns>
	int minimax(int depth, char ch);
	void make_computer_move();
	/// <summary>
	/// デバック出力にボードを表示。
	/// </summary>
	void dout_borad();
	/// <summary>
	/// デバック出力に文字を出力。
	/// </summary>
	/// <param name="str">出力する文字。</param>
	void dout(std::string str);
};

