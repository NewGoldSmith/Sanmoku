/**
 * @file Game.cpp
 * @brief ゲームクラスの実装
 * @author Gold Smith
 * @date 2023
 *
 * Released under the MIT license
 * https: //opensource.org/licenses/mit-license.php
 */
#include "Game.h"
using namespace std;

Game::Game()
	:
	board()
{
	init_game();
}

Game::~Game()
{
}

void Game::init_game()
{
	// 盤面の初期化
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			board[i][j] = ' ';
}

void Game::display_board()
{
	cout << " ";
	for (int row = 0; row < N; row++)
		cout << " " << row + 1;
	cout << endl;
	for (int row = 0; row < N; row++) {
		cout << row + 1;
		for (int col = 0; col < N; col++)
			cout << "|" << board[row][col];
		cout << "|" << endl;
		cout << " ";
		for (int col = 0; col < N; col++)
			cout << "--";
		cout << "-" << endl;
	}
}

void Game::play_game(bool human_first, bool two_player)
{
	char current_player = human_first ? 'X' : 'C';
	for (;;) {
		display_board();
		int row, col;
		if (current_player == 'C' && !two_player) {
			make_computer_move();
			cout << "コンピュータが指しました。" << endl;
		}
		else {
			for (;;) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "プレイヤー " << current_player << "、入力して下さい。(行 列): ";
				cin >> row >> col;
				if (cin.fail()) {
					cin.clear();
					cout << "無効な入力です。再度入力してください。" << endl;
					display_board();
					continue;
				}
				if (row < 1 || row > N || col < 1 || col > N) {
					cout << "無効な手です。再度入力してください。" << endl;
					display_board();
					continue;
				}
				if (board[row - 1][col - 1] != ' ') {
					cout << "そのマスは既に選択されています。" << endl;
					display_board();
					continue;
				}
				board[row - 1][col - 1] = current_player;
				break;
			}
		}
		if (is_win('X')) {
			display_board();
			cout << "Xの勝ち!" << endl;
			break;
		}
		else if (is_win('C')) {
			display_board();
			cout << "Cの勝ち!" << endl;
			break;
		}
		else if (is_draw()) {
			display_board();
			cout << "引き分けです!" << endl;
			break;
		}
		// switch player
		current_player = current_player == 'X' ? 'C' : 'X';
	}
}

bool Game::is_draw()
{
	for (int row = 0; row < N; row++)
		for (int col = 0; col < N; col++)
			if (board[row][col] == ' ')
				return false;
	return true;
}

bool Game::is_win(char player)
{
	for (int row = 0; row < N; row++) {
		bool win = true;
		for (int col = 0; col < N; col++)
			if (board[row][col] != player)
				win = false;
		if (win)
			return true;
	}
	for (int col = 0; col < N; col++) {
		bool win = true;
		for (int row = 0; row < N; row++)
			if (board[row][col] != player)
				win = false;
		if (win)
			return true;
	}
	bool win = true;
	for (int i = 0; i < N; i++)
		if (board[i][i] != player)
			win = false;
	if (win)
		return true;

	win = true;
	for (int i = 0; i < N; i++)
		if (board[i][N - i - 1] != player)
			win = false;
	if (win)
		return true;

	return false;
}

int Game::evaluate(char ch, int depth, bool* pb_is_settled)
{
	// 勝敗の評価
	if (is_win('X'))
	{
		*pb_is_settled = true;
		return ch == 'X' ? INF - depth : -INF + depth;
	}
	if (is_win('C'))
	{
		*pb_is_settled = true;
		return ch == 'C' ? INF - depth : -INF + depth;
	}
	// 引き分けの評価
	if (is_draw())
	{
		*pb_is_settled = true;
		return -depth;
	}
	return -depth;
}

int Game::minimax(int depth, char ch)
{
	bool b_settled(false);
	int score = evaluate(ch, depth, &b_settled);

	// 勝敗が決定した場合
	if (b_settled)
		return score;

	int best = -INF;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (board[row][col] == ' ') {
				board[row][col] = ch;
				best = std::max<int>(best, -minimax(depth + 1, ch == 'C' ? 'X' : 'C'));
				board[row][col] = ' ';
			}
		}
	}
	return best;
}

void Game::make_computer_move()
{
	int best_val = -INF;
	int best_row = -1;
	int best_col = -1;

	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (board[row][col] == ' ') {
				board[row][col] = 'C';
				int move_val = -minimax(0, 'X');
				board[row][col] = ' ';
				if (move_val > best_val) {
					best_row = row;
					best_col = col;
					best_val = move_val;
				}
			}
		}
	}
	board[best_row][best_col] = 'C';
}

void Game::dout_borad()
{
	stringstream ss;
	ss << " ";
	for (int row = 0; row < N; row++)
		ss << " " << row + 1;
	ss << endl;
	for (int row = 0; row < N; row++) {
		ss << row + 1;
		for (int col = 0; col < N; col++)
			ss << "|" << board[row][col];
		ss << "|" << endl;
		ss << " ";
		for (int col = 0; col < N; col++)
			ss << "--";
		ss << "-" << endl;
	}
	OutputDebugStringA(ss.str().c_str());
}

void Game::dout(std::string str)
{
	OutputDebugStringA((str + "\r\n").c_str());
}
