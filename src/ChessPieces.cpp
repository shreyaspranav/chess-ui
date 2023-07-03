#include "ChessPieces.h"

ChessPieces::ChessPieces(const std::string &initialFEN)
{
    ChessPieces::LoadFEN(initialFEN);

    // Temporary:
    m_ChessPiecesMap.insert({{'a', 1}, ChessPiece::WhiteRook});
    m_ChessPiecesMap.insert({{'b', 1}, ChessPiece::WhiteKnight});
    m_ChessPiecesMap.insert({{'c', 1}, ChessPiece::WhiteBishop});
    m_ChessPiecesMap.insert({{'d', 1}, ChessPiece::WhiteQueen});
    m_ChessPiecesMap.insert({{'e', 1}, ChessPiece::WhiteKing});
    m_ChessPiecesMap.insert({{'f', 1}, ChessPiece::WhiteBishop});
    m_ChessPiecesMap.insert({{'g', 1}, ChessPiece::WhiteKnight});
    m_ChessPiecesMap.insert({{'h', 1}, ChessPiece::WhiteRook});

    m_ChessPiecesMap.insert({{'a', 8}, ChessPiece::BlackRook});
    m_ChessPiecesMap.insert({{'b', 8}, ChessPiece::BlackKnight});
    m_ChessPiecesMap.insert({{'c', 8}, ChessPiece::BlackBishop});
    m_ChessPiecesMap.insert({{'d', 8}, ChessPiece::BlackQueen});
    m_ChessPiecesMap.insert({{'e', 8}, ChessPiece::BlackKing});
    m_ChessPiecesMap.insert({{'f', 8}, ChessPiece::BlackBishop});
    m_ChessPiecesMap.insert({{'g', 8}, ChessPiece::BlackKnight});
    m_ChessPiecesMap.insert({{'h', 8}, ChessPiece::BlackRook});

    for(int i = 0; i < 8; i++)
    {
        m_ChessPiecesMap.insert({{'a' + (char)i, 2}, ChessPiece::WhitePawn});
        m_ChessPiecesMap.insert({{'a' + (char)i, 7}, ChessPiece::BlackPawn});
    }
}

ChessPieces::~ChessPieces()
{

}

void ChessPieces::LoadFEN(const std::string &FEN)
{

}
