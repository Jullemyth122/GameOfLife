#pragma once
#include "grid.hpp"

class Simulation
{
    public:
        Simulation(int width, int height, int cellSize)
        : grid(width,height,cellSize), tempGrid(width, height, cellSize), run(false) {
            // grid.FillRandom();
            };        
        void Draw();
        void SetCellValue(int row, int column, int value);

        // CountLiveNeighbor is what it is neighbors example at the certain point in coordinate
        // for example if the main cell is [3][4] then it should count all beside it.
        // direct above  cell[2][4], direct below cell[4][4], left cell[3][3]
        // and right cell[3][5] diagonal upper left [2][3] and etc
        // [2][4] ,[4][4], [3][3], [3][5], [2][3], [2][5],[4][3], [4][5]
        // =>>>>
        //    - - - - - - - - - - -
        //    ' ' '
        //    ' ' '
        //    ' ' '
        //    - - - - - - - - - - 
        // like this for example

        
        int CountLiveNeighbors(int row, int column);

        void Update();

        bool IsRunning() { return run; }

        void Start() { run = true; }

        void Stop() { run = false; }

        void ClearGrid();

        void CreateRandomState();

        void ToggleCell(int row, int column);
    private:
        Grid grid;
        Grid tempGrid;
        bool run;
};