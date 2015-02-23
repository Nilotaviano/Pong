#pragma once

enum class GamePlayState{PLAYER1_WINS, PLAYER2_WINS, NOT_OVER };

#define PLAYER1_WINS GamePlayState::PLAYER1_WINS
#define PLAYER2_WINS GamePlayState::PLAYER2_WINS
#define NOT_OVER GamePlayState::NOT_OVER