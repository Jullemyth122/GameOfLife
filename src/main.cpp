#include <raylib.h>
#include <iostream>
#include "simulation.hpp" 

int main()
{
    // The Rules 
    // underpopulation: A live cell with fewer than two live neighbors dies.
    // statis: a live cell with two or three live neighbors lives on to the next generation.
    // overpopulation: A live cell with more than three live neighbors dies.
    // reproduction: a dead cell with exactly three live neighvors become a live cell.

    // Rule #1: If a cell is a live it dies when it has fewer than 2 or more than 3 live neighbors,
    // else it stays alive.

    // Rule #2: If a cell is dead, it can come alive only if it has exactly 3 live neighbors,
    // else it stays dead.
    const int window_width = 1000;
    const int window_height = 1000;

    const int CELL_SIZE = 20 ;



    int FPS = 12;

    // Color color = { red, green, blue, alpha } range <=> range {255,255,255,255}
    Color grey = {29,29,29,255};

    InitWindow(window_width, window_height, "Game of Life");
    SetTargetFPS(FPS);
    Simulation simulation(window_width,window_height, CELL_SIZE);

    


    // simulation.SetCellValue(5,28,1);
    // simulation.SetCellValue(4,28,1);
    // simulation.SetCellValue(5,29,1);
    // simulation.SetCellValue(6,0,1);
    // simulation.SetCellValue(5,0,1);
    // simulation.SetCellValue(4,0,1);


    // std:: cout << simulation.CountLiveNeighbors(5,29) << std::endl;
    // std:: cout << simulation.CountLiveNeighbors(11,5) << std::endl;

    while(WindowShouldClose() == false) {
        // handling events 
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition(); 
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;

            simulation.ToggleCell(row, column);
            std::cout << row << " " << column << std::endl;
        }
        if(IsKeyPressed(KEY_ENTER)) {
            simulation.Start();
            SetWindowTitle("Game of Life is running ...") ;   
        } else if (IsKeyPressed(KEY_SPACE)) {
            simulation.Stop();
            SetWindowTitle("Game of Life is stopped ...");
        } else if (IsKeyPressed(KEY_F)) {
            FPS += 2;
            SetTargetFPS(FPS);
        } else if (IsKeyPressed(KEY_S)) {
            if (FPS > 5) {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        } else if (IsKeyPressed(KEY_C)) {
            simulation.ClearGrid();
        } else if (IsKeyPressed(KEY_R)) {
            simulation.CreateRandomState();
        }

        // updating state
        simulation.Update();

        // drawing 
        BeginDrawing();

        ClearBackground(grey);

        simulation.Draw();


        EndDrawing();

    }

    CloseWindow();
    return 0;
}