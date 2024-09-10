#include <vector>
#include <utility>
#include "simulation.hpp"
using namespace std;

void Simulation::Draw()
{
    grid.Draw();

}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{

    int liveNeighbors = 0;
    vector<pair<int, int> > neighborOffsets = 
    {
        {-1,0}, // directly above 
        {1,0}, // directly below 
        {0,-1}, // to the left 
        {0,1}, // to the right
        {-1,-1}, // diagonal upper left
        {-1,1}, // diagonal upper right
        {1,-1}, // diagonal lower left
        {1,1}, // diagonal lower right <---- fucking error { supposed to be (1,1) not (-1,1)  } 
    };

    for(const auto& offset : neighborOffsets)
    {
        // int neighborRow = row + offset.first;
        // int neighborCol = column + offset.second;
        // Adding Toroidal Grid
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborCol = (column + offset.second + grid.GetColumns()) % grid.GetColumns();

        liveNeighbors += grid.GetValue(neighborRow, neighborCol);
    }
    return liveNeighbors;
    
}

void Simulation::Update()
{
    if(IsRunning()) {
        for(int row = 0; row < grid.GetRows(); row++) {
            for(int column = 0; column < grid.GetColumns(); column++) {
                int liveNeighbors = CountLiveNeighbors(row, column);
                int cellValue = grid.GetValue(row,column);

                if (cellValue == 1) {
                    if (liveNeighbors > 3 || liveNeighbors < 2) {
                        tempGrid.SetValue(row,column,0);
                    } else {
                        tempGrid.SetValue(row,column,1); 
                    }
                } else {
                    if(liveNeighbors == 3) {
                        tempGrid.SetValue(row,column,1);
                    } else {
                        tempGrid.SetValue(row,column,0);
                    }
                }

            }
        }
        grid = tempGrid;
        
    }
}

void Simulation::ClearGrid()
{
    if(!IsRunning() ) {
        grid.Clear();
    }
}

void Simulation::CreateRandomState()
{
    if(!IsRunning()) {
        grid.FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if(!IsRunning()) {
        grid.ToggleCell(row, column);
    }
}
