#pragma once

struct RenderContext
{
    unsigned int shagerProgram;

    unsigned int modelLoc;
    unsigned int viewLoc;
    unsigned int projectionLoc;

    unsigned int colorLocation;

    unsigned int cubeVAO;
};