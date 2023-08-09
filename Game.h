/**
 * @file Game.h
 * @brief �Q�[���N���X�̐錾
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
	/// ���ۂ̃Q�[���X�^�[�g�B
	/// </summary>
	/// <param name="human_first">�l����U���B</param>
	/// <param name="two_player">2�v���[���[�ΐ킩�B</param>
	void play_game(bool human_first, bool two_player);
private:
	/// <summary>
	/// �����board_t�Ƃ����^��`�B
	/// </summary>
	typedef char board_t[N][N];
	board_t board;
	void display_board();
	void init_game();
	bool is_draw();
	bool is_win(char player);
	/// <summary>
	/// �]���֐�
	/// </summary>
	/// <param name="ch">�Ώۂ̎��</param>
	/// <param name="depth">�ǂݐ[��</param>
	/// <param name="pb_is_seddled">��������������
	/// �����ĂȂ����̌��ʂ��󂯎��|�C���^�B</param>
	/// <returns></returns>
	int evaluate(char ch, int depth, bool* pb_is_seddled);
	/// <summary>
	/// �Ֆʂ����o���֐��B
	/// </summary>
	/// <param name="depth">�ǂ݂̐[���B�[���قǃ��^�[���̕]���l�͓݂��Ȃ�B</param>
	/// <param name="ch">���̎��</param>
	/// <returns>�]���l</returns>
	int minimax(int depth, char ch);
	void make_computer_move();
	/// <summary>
	/// �f�o�b�N�o�͂Ƀ{�[�h��\���B
	/// </summary>
	void dout_borad();
	/// <summary>
	/// �f�o�b�N�o�͂ɕ������o�́B
	/// </summary>
	/// <param name="str">�o�͂��镶���B</param>
	void dout(std::string str);
};

