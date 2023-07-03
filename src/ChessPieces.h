#pragma once

#include <stdint.h>
#include <map>
#include <string>

struct BoardPosition {
    char file;
    uint8_t rank; 

    BoardPosition()
        :rank(1), file('a') {}
    BoardPosition(char f, uint8_t r)
        :rank(r), file(f) {}

    bool operator<(const BoardPosition& position) { return rank < position.rank || file < position.file; }
};

enum class ChessPiece {
    WhitePawn    = 0b1001,
    WhiteKnight  = 0b1010,
    WhiteBishop  = 0b1011,
    WhiteRook    = 0b1100,
    WhiteQueen   = 0b1101,
    WhiteKing    = 0b1110,

    BlackPawn    = 0b0001,
    BlackKnight  = 0b0010,
    BlackBishop  = 0b0011,
    BlackRook    = 0b0100,
    BlackQueen   = 0b0101,
    BlackKing    = 0b0110,
};

class ChessPieces {
public:
    ChessPieces(const std::string& initialFEN);
    ~ChessPieces();

    void LoadFEN(const std::string& FEN);
    const std::string& GetCurrentFEN();

private:
    std::map<BoardPosition, ChessPiece> m_ChessPiecesMap;

    std::string m_InitialFEN;
    std::string m_CurrentFEN;
};