#include "modelshow.h"

int showModelProj(QGraphicsScene *const graphicsScene, modelProjT *const modelProj, const modelT *const model)
{
    int errorCode = 0;

    errorCode = modelProjFormation(modelProj, model);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }

    QPen outlinePen(Qt::black);

    double dX = SCENE_WIDTH / 2 - modelProj->center.x;
    double dZ = SCENE_HEIGHT / 2 - modelProj->center.z;

    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        for (int j = 0; j < modelProj->pointsProjNumber; j++)
        {
            if (modelProj->linksMatrix[i][j])
            {
                double xB = modelProj->pointsProjArray[i].x + dX;
                double xE = modelProj->pointsProjArray[j].x + dX;
                double zB = modelProj->pointsProjArray[i].z + dZ;
                double zE = modelProj->pointsProjArray[j].z + dZ;
                graphicsScene->addLine(xB, zB, xE, zE, outlinePen);;
            }
        }
    }

    return SUCCESS;
}
