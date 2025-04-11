# Add source files
target_sources(Chess PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Chess.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/PieceFactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/Rook.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/King.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/Bishop.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/Queen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/Knight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/Pawn.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GameManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Piece/Piece.cpp
)

# Make headers in include/ visible to this target
target_include_directories(Chess PRIVATE ${PROJECT_SOURCE_DIR}/include)